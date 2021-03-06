#include "hardware_board.hpp"
#include "simple_exec_unit.hpp"
#include "led_controller.hpp"
#include <forward_list>
#include <iostream>
#include "led.hpp"
#include <cassert>

namespace back_end
{

struct hardware_bord
{
  hardware_bord(std::shared_ptr<execution_unit::out_command_callback> c) : eu{c}
  {
      leds.push_front(std::make_unique<empty_led>(std::cout));

      for(int i = 0; i < exec_unit_register::length_in_bits; ++i)
      {
          leds.push_front(std::make_unique<blue_led>(std::cout));
      }
  }

  led_strip leds{};
  simple_execution_unit eu;
  led_controller led_c{leds, eu.get_bus_to_registers(), eu.get_bus_to_registers()};
};

serial_interface& operator>>(back_end::instructions_to_execute&& soi, serial_interface& si)
{
  std::move(soi) >> si.hw->eu;
  return si;
}

serial_interface::serial_interface(std::shared_ptr<hardware_bord> h) : hw(h)
{}

hardware_driver::hardware_driver()
{
   callbacks_set = std::make_shared<execution_unit::out_command_callback>();
   hw = std::make_shared<hardware_bord>(callbacks_set);
}

serial_interface& hardware_driver::get_serial_interface()
{
  static thread_local serial_interface s{hw};
  return s;
}

void hardware_driver::register_on_out_command(std::function<void()> f)
{
  callbacks_set->push_back(f);
}

} /* namespace back_end */
