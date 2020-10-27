#pragma once

#include "controller/base.hh"

#include <algorithm>

namespace simc::controller {

struct PID : public Base<1, 1> {
  PID()
  {
    this->variable_description_ = {
        // Parameters
        {Variable::Parameter, "kP", "Proportional gain", "", 1, 4},
        {Variable::Parameter, "kI", "Integral gain", "", 0, 4},
        {Variable::Parameter, "kD", "Derivative gain", "", 0, 4},
        {Variable::Parameter, "low", "Saturation lower bound", "",
         std::numeric_limits<double>::min(), 3},
        {Variable::Parameter, "high", "Saturation upper bound", "",
         std::numeric_limits<double>::max(), 3},
        // Inputs
        {Variable::Input, "Error", "Error signal relative to a reference", ""},
        // Outputs
        {Variable::Output, "Input", "Input signal for a system", ""},
    };
  }

  input_t c(error_t const& e_k, const double& dt) final
  {
    const auto& kP       = variable_[0];
    const auto& kI       = variable_[1] * dt;
    const auto& kD       = variable_[2] / dt;
    const auto& sat_low  = variable_[3];
    const auto& sat_high = variable_[4];

    // Compute integral part
    error_sum_[0]  = std::clamp(error_sum_[0] + e_k[0], sat_low / kI, sat_high / kI);
    const auto e_i = kI * error_sum_[0];

    // Compute output
    const auto u = std::clamp(kP * e_k[0] + e_i + kD * (e_k[0] - e_km1_[0]), sat_low, sat_high);

    // Save current error as last error
    e_km1_ = e_k;

    return {u};
  }

 private:
  error_t e_km1_     = {};
  error_t error_sum_ = {};
};

}  // namespace simc::controller
