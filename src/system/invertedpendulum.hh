#pragma once

#include "system/base.hh"

namespace simc::system {

/*!
 * \brief The InvertedPendulum class simulates an inverted pendulum on a cart.
 */
struct InvertedPendulum : public Base<1, 4, 2> {
  InvertedPendulum()
  {
    this->variable_description_ = {
        // Parameters
        {Variable::Parameter, "g", "Gravitational constant", "m.s^-2", 9.81, 2},
        {Variable::Parameter, "M", "Cart mass", "kg", 1, 3},
        {Variable::Parameter, "fc", "Cart friction", "N.m^-1.s", 100, 2},
        {Variable::Parameter, "m", "Pendulum mass", "kg", 0.15, 3},
        {Variable::Parameter, "l", "Pendulum length", "m", 0.5, 2},
        {Variable::Parameter, "fp", "Pendulum friction", "N.m^-1.s", 0.005, 4},
        // Inputs
        {Variable::Input, "F", "Force applied to the cart", "N"},
        // States
        {Variable::State, "Theta", "Angle of the pendulum", "rad", 0, 3},
        {Variable::State, "Theta_d", "Angular velocity of the pendulum", "rad.s^-1", 0, 3},
        {Variable::State, "X", "Position of the cart", "m", 0, 3},
        {Variable::State, "X_d", "Velocity of the cart", "m.s^-1", 0, 3},
        // Outputs
        {Variable::Output, "Theta", "Angle of the pendulum", "rad"},
        {Variable::Output, "X", "Position of the cart", "m"},
    };
  }

  state_t f(state_t const& x_k, input_t const& u_k) final
  {
    // Parameters
    auto const& g  = variable_[0];
    auto const& M  = variable_[1];
    auto const& fc = variable_[2];
    auto const& m  = variable_[3];
    auto const& l  = variable_[4];
    auto const& fp = variable_[5];
    // States
    auto const& theta   = x_k[0];
    auto const& theta_d = x_k[1];
    auto const& x_d     = x_k[3];
    // Inputs
    auto const& F = u_k[0];
    // Constants
    auto const ct = cos(theta);
    auto const st = sin(theta);

    // State equation
    auto const&& den     = 4. / 3. * (M + m) - m * ct * ct;
    auto const&& lmsttd2 = l * m * st * theta_d * theta_d;

    const auto&& Ffric_c = fc * x_d;
    const auto&& Ffric_p = fp * theta_d;

    const auto&& theta_dd =
        (g * (M + m) * st - ct * lmsttd2 + Ffric_c * ct - Ffric_p * (m + M) / (m * l)) / (l * den);

    const auto&& x_dd =
        (-m * g * ct * st + 4. / 3. * lmsttd2 - 4. / 3. * Ffric_c + Ffric_p * ct / l) / den;

    // Input equation
    const auto&& den2 = 4. * (M + m) - 3. * m * ct * ct;

    return {theta_d, theta_dd + F * 3. * ct / (l * den2), x_d, x_dd + F * 4. / den2};
  }

  output_t h(state_t const& x_k, input_t const&) final { return {x_k[0], x_k[2]}; };
};

}  // namespace simc::system
