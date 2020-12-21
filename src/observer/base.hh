#pragma once

#include "variable.hh"

namespace simc::observer {

template <std::size_t input_size,
          std::size_t sensor_output_size,
          std::size_t observer_state_size,
          std::size_t system_state_size>
struct Base : public VariableBase {
  using input_t          = std::array<double, input_size>;
  using sensor_output_t  = std::array<double, sensor_output_size>;
  using observer_state_t = std::array<double, observer_state_size>;
  using system_state_t   = std::array<double, system_state_size>;

  virtual ~Base() = default;

  virtual observer_state_t F(sensor_output_t const&  z_k,
                             observer_state_t const& xi_k,
                             input_t const&          u_k) = 0;

  virtual system_state_t H(sensor_output_t const&  z_k,
                           observer_state_t const& xi_k,
                           input_t const&          u_k) = 0;
};

}  // namespace simc::observer
