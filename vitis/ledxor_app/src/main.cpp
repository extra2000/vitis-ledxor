#include <string>
#include <boost/asio.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/thread.hpp>
#include <boost/format.hpp>
#include <boost/bind/bind.hpp>
#include <logger.hpp>
#include <engine.hpp>

void handler(const boost::system::error_code& error, int signal_number, logger::Logger& log)
{
    if (!error)
    {
        log.info(boost::format("Received signal number %1%") % signal_number);
    }
}

int main(int argc, char* argv[])
{
    logger::LoggerConfig logcfg;
    logger::Logger log("main");
    logcfg.set_min_severity("main", logger::severity_level::debug);
    logcfg.set_min_severity("engine", logger::severity_level::debug);

    boost::asio::io_context io;

    boost::asio::signal_set signals(io, SIGINT, SIGTERM);
    signals.async_wait(
        boost::bind(
            handler,
            boost::asio::placeholders::error,
            boost::asio::placeholders::signal_number,
            log
        )
    );

    std::string chipname = "gpiochip0";
    myengine::MyEngine *engine = new myengine::MyEngine(argv[0], chipname);
    engine->set_sw0(54);
    engine->set_sw1(55);
    engine->set_led0(56);

    log.debug("Spawning mainloop thread");
    boost::thread mainloop(boost::bind(&myengine::MyEngine::mainloop, engine));

    log.debug("Program will keep running until SIGINT or SIGTERM");
    io.run();

    log.debug("Shutting down engine");
    engine->shutdown();

    log.debug("Waiting for the mainloop thread to exit");
    mainloop.join();

    log.debug("Destroying engine");
    delete engine;

    return 0;
}
