#pragma once

#include <type_traits>
#include <unordered_map>
#include "exec_unit_register.hpp"

namespace back_end
{
namespace instructions
{
  struct djnz;
  struct out_register;
  struct rrca;
  struct lrca;
  struct load;
  struct no_operation;
  struct repeat;
  struct add;
  struct mul;
}

class execution_unit
{
public:
  using exec_unit_reg_descriptor = std::unordered_map<exec_unit_register::label_type, exec_unit_register*>;

  virtual void execute(const instructions::djnz&) = 0;
  virtual void execute(const instructions::out_register&) = 0;
  virtual void execute(const instructions::rrca&) = 0;
  virtual void execute(const instructions::lrca&) = 0;
  virtual void execute(const instructions::load&) = 0;
  virtual void execute(const instructions::no_operation&) = 0;
  virtual void execute(const instructions::repeat&) = 0;
  virtual void execute(const instructions::add&) = 0;
  virtual void execute(const instructions::mul&) = 0;

  virtual ~execution_unit() = default;
};

}

