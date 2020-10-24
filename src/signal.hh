#pragma once

#include <numeric>
#include <string_view>

namespace simc {

/*!
 * \brief The Signal class describes a signal's attributes.
 *
 * Properties:
 *  - Name
 *  - Type
 *  - Unit
 *  - Minimum
 *  - Maximum
 *  - Precision (for UI)
 *  - Initial value
 */
struct Signal {
  enum class Type { Input, Output, Parameter, Setpoint };

  Signal(std::string const& name,
         Type               type,
         std::string const& unit          = {},
         double             minimum       = std::numeric_limits<double>::min(),
         double             maximum       = std::numeric_limits<double>::max(),
         double             precision     = 0.0001,
         double             initial_value = 0)
      : name_(name),
        type_(type),
        unit_(unit),
        minimum_(minimum),
        maximum_(maximum),
        precision_(precision),
        initial_value_(initial_value)
  {}

  std::string name() { return name_; };
  Type        type() { return type_; };
  std::string unit() { return unit_; };
  double      minimum() { return minimum_; };
  double      maximum() { return maximum_; };
  double      precision() { return precision_; };
  double      initial_value() { return initial_value_; };

  void set_name(std::string const& name) { name_ = name; }
  void set_type(Type type) { type_ = type; }
  void set_unit(std::string const& unit) { unit_ = unit; }
  void set_minimum(double minimum) { minimum_ = minimum; }
  void set_maximum(double maximum) { maximum_ = maximum; }
  void set_precision(double precision) { precision_ = precision; }
  void set_initial_value(double initial_value) { initial_value_ = initial_value; }

 private:
  std::string name_;
  Type        type_;
  std::string unit_;
  double      minimum_, maximum_, precision_, initial_value_;
};

}  // namespace simc
