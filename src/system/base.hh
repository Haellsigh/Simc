#pragma once

#include "utilities/noncopyable.hh"
#include "variable.hh"

#include <array>

namespace simc::system {

/*!
 * \brief Base class for a physical system.
 *
 * \tparam input_t The number of inputs, size(u)
 * \tparam state_t The number of states, size(x)
 * \tparam output_t The number of outputs, size(y)
 */
template <std::size_t input_size, std::size_t state_size, std::size_t output_size>
struct Base : public VariableBase {
  using input_t  = std::array<double, input_size>;
  using state_t  = std::array<double, state_size>;
  using output_t = std::array<double, output_size>;

  virtual ~Base() = default;

  /*!
   * \brief The state equation
   * \param x_k The last state of the system
   * \param u_k The current input of the system
   * \return The derivative of the system state at step k
   */
  virtual state_t f(state_t const& x_k, input_t const& u_k) = 0;

  /*!
   * \brief The output equation
   * \param x_k The current state of the system
   * \param u_k The current input of the system
   * \return The output of the system at step k
   */
  virtual output_t h(state_t const& x_k, input_t const& u_k) = 0;

 protected:
};

}  // namespace simc::system
