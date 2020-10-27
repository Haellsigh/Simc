#pragma once

#include "variable.hh"

#include <array>

namespace simc::controller {

/*!
 * \brief Base class for a controller.
 *
 * \tparam error_size The number of states, size(e)
 * \tparam input_size The number of inputs, size(u)
 */
template <std::size_t error_size, std::size_t input_size>
struct Base : public VariableBase {
  using error_t = std::array<double, error_size>;
  using input_t = std::array<double, input_size>;

  virtual ~Base() = default;

  /*!
   * \brief The control equation
   * \param e_k The error at step k
   * \param dt The time delta
   * \return The control signal u at step k
   */
  virtual input_t c(error_t const& e_k, const double& dt) = 0;
};

}  // namespace simc::controller
