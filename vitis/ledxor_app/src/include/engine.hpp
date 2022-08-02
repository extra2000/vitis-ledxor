/*
 * engine.hpp
 */

#ifndef INCLUDE_ENGINE_HPP_
#define INCLUDE_ENGINE_HPP_


#include <chrono>
#include <gpiod.hpp>
#include <logger.hpp>

namespace myengine
{

class MyEngine
{
protected:
    std::string progname;
    std::string chipname;
    gpiod::chip *chip;
    gpiod::line *sw0;
    gpiod::line *sw1;
    gpiod::line *led0;
    logger::Logger log;
    void wait_for_switches(gpiod::line_bulk& switches, std::chrono::seconds timeout);
    void ledxor();
public:
    MyEngine();
    MyEngine(const std::string& progname, const std::string& chipname);
    ~MyEngine();
    void set_chipname(const std::string& chipname);
    void set_sw0(unsigned int line_number);
    void set_sw1(unsigned int line_number);
    void set_led0(unsigned int line_number);
    void mainloop();
}; // class MyEngine

} // namespace myengine

#endif // INCLUDE_ENGINE_HPP_
