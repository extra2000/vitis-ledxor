/*
 * engine.cpp
 */

#include <system_error>
#include <chrono>
#include <boost/format.hpp>
#include <engine.hpp>

myengine::MyEngine::MyEngine()
{
    log.init("engine");
    chip = NULL;
    is_shutdown = false;
    log.debug("Engine initialized without chipname");
}

myengine::MyEngine::MyEngine(const std::string& progname, const std::string& chipname)
{
    log.init("engine");

    sw0 = NULL;
    sw1 = NULL;
    led0 = NULL;

    this->progname = progname;
    this->chipname = chipname;
    chip = new gpiod::chip(chipname);

    log.debug(boost::format("Progname = '%1%', Engine initialized with chipname '%2%'") % this->progname % this->chipname);
}

myengine::MyEngine::~MyEngine()
{
    if (sw0 != NULL)
    {
        log.debug("SW0 line was initialized. Destroying SW0 line ...");
        delete sw0;
    }

    if (sw1 != NULL)
    {
        log.debug("SW1 line was initialized. Destroying SW1 line ...");
        delete sw1;
    }

    if (led0 != NULL)
    {
        log.debug("LED0 line was initialized. Destroying LED0 line ...");
        led0->set_value(0);
        delete led0;
    }

    if (chip != NULL)
    {
        log.debug("Chip was initialized. Destroying chip ...");
        delete chip;
    }
    log.debug("Engine destroyed");
}

void myengine::MyEngine::set_chipname(const std::string& chipname)
{
    this->chipname = chipname;
    log.debug(boost::format("Chipname set to '%1%'") % this->chipname);
}

void myengine::MyEngine::set_sw0(unsigned int line_number)
{
    log.debug(boost::format("Initializing SW0 with line number %1%") % line_number);
    sw0 = new gpiod::line(chip->get_line(line_number));

    log.debug("Setting SW0 as DIRECTION_INPUT and EVENT_BOTH_EDGES");
    sw0->request({progname, gpiod::line_request::DIRECTION_INPUT | gpiod::line_request::EVENT_BOTH_EDGES, 0});
}

void myengine::MyEngine::set_sw1(unsigned int line_number)
{
    log.debug(boost::format("Initializing SW1 with line number %1%") % line_number);
    sw1 = new gpiod::line(chip->get_line(line_number));

    log.debug("Setting SW1 as DIRECTION_INPUT and EVENT_BOTH_EDGES");
    sw1->request({progname, gpiod::line_request::DIRECTION_INPUT | gpiod::line_request::EVENT_BOTH_EDGES, 0});
}

void myengine::MyEngine::set_led0(unsigned int line_number)
{
    log.debug(boost::format("Initializing LED0 with line number %1%") % line_number);
    led0 = new gpiod::line(chip->get_line(line_number));

    log.debug("Setting LED0 as DIRECTION_OUTPUT");
    led0->request({progname, gpiod::line_request::DIRECTION_OUTPUT, 0});
}

void myengine::MyEngine::wait_for_switches(gpiod::line_bulk& switches, std::chrono::seconds timeout)
{
    gpiod::line_bulk sw_events;

    log.debug("Waiting for SW0 and SW1 events");
    while(is_shutdown == false)
    {
        sw_events = switches.event_wait(timeout);
        if(sw_events.empty() == false)
        {
            log.debug("Event detected");
            print_event_info(sw_events);
            break;
        }
    }
}

void myengine::MyEngine::print_event_info(gpiod::line_bulk& lines)
{
    log.debug("Reading event information");
    for (gpiod::line line : lines)
    {
        gpiod::line_event line_event = line.event_read();

        std::string event_type;
        if (line_event.event_type == gpiod::line_event::RISING_EDGE)
        {
            event_type = "RISING_EDGE";
        }
        else
        {
            event_type = "FALLING_EDGE";
        }

        log.debug("Dumping event information");
        log.debug(
            boost::format("Timestamp in nanoseconds = %1%, Event type = %2%, Value = %3%")
            % line_event.timestamp.count()
            % event_type
            % line_event.source.get_value()
        );
    }
}

void myengine::MyEngine::ledxor()
{
    log.debug("Performing LEDXOR operation");
    bool result = sw0->get_value() ^ sw1->get_value();
    led0->set_value(result);
}

void myengine::MyEngine::mainloop()
{
    gpiod::line_bulk switches;
    switches.append(*sw0);
    switches.append(*sw1);

    while (is_shutdown == false)
    {
        ledxor();
        wait_for_switches(switches, std::chrono::seconds(1));
    }
}

void myengine::MyEngine::shutdown()
{
    log.debug("Engine is set to shutdown");
    is_shutdown = true;
}
