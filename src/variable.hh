#pragma once

#include "utilities/noncopyable.hh"

#include <numeric>
#include <string>
#include <vector>

namespace simc {

/*!
 * \brief The Variable class describes a variable's attributes.
 *
 * Attributes:
 *  - Name
 *  - Description
 *  - Unit
 *  - Minimum
 *  - Maximum
 *  - Digits (for display only)
 *  - Initial value
 */
struct Variable {
  enum Type { Input, State, Output, Parameter };

  Variable(Type               type,
           std::string const& name,
           std::string const& description,
           std::string const& unit          = {},
           double             initial_value = 0,
           double             digits        = 4,
           double             minimum       = std::numeric_limits<double>::min(),
           double             maximum       = std::numeric_limits<double>::max())
      : type_(type),
        name_(name),
        description_(description),
        unit_(unit),
        initial_value_(initial_value),
        digits_(digits),
        minimum_(minimum),
        maximum_(maximum)
  {}

  Type        type() { return type_; };
  std::string name() { return name_; };
  std::string description() { return description_; };
  std::string unit() { return unit_; };
  double      minimum() { return minimum_; };
  double      maximum() { return maximum_; };
  double      digits() { return digits_; };
  double      initial_value() { return initial_value_; };

  void set_name(std::string const& name) { name_ = name; }
  void set_description(std::string const& description) { description_ = description; }
  void set_unit(std::string const& unit) { unit_ = unit; }
  void set_minimum(double minimum) { minimum_ = minimum; }
  void set_maximum(double maximum) { maximum_ = maximum; }
  void set_digits(double precision) { digits_ = precision; }
  void set_initial_value(double initial_value) { initial_value_ = initial_value; }

 private:
  Type        type_;
  std::string name_, description_;
  std::string unit_;
  double      initial_value_, digits_, minimum_, maximum_;
};

/*!
 * \brief The VariableBase class is the base class used to describe the variables in a system,
 * sensor, observer or controller.
 *
 * Child classes must fill the variable_description_ member variable with the description
 * of each variable.
 *
 * The variables will then be available to the user interface and the modifiable values will be set
 * in the variable_ member variable.
 *
 * \note The child classes must call initialize_variables() after setting variable_description_.
 */
struct VariableBase : public utilities::noncopyable {
  /*!
   * \brief Returns a description of all variables.
   *
   * Lists parameters and setpoints, but not inputs and outputs.
   *
   * \return The description of all variables.
   */
  auto const& get_variable_descriptions() const { return variable_description_; };

  auto get_inputs() const {}
  auto get_states() const {}
  auto get_outputs() const {}
  auto get_parameters() const {}

  double get_variable(std::size_t i) { return variable_[i]; }
  void   set_variable(std::size_t i, double value) { variable_[i] = value; }

 protected:
  std::vector<Variable> variable_description_;
  std::vector<double>   variable_;
};

}  // namespace simc
