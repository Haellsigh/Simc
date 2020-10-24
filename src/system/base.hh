#pragma once

#include <signal.hh>
#include <utilities/noncopyable.hh>

#include <vector>

namespace simc::system {

template <typename input_t, typename output_t>
struct Base : public utilities::noncopyable {
  virtual ~Base() = default;

  /*!
   * \brief Returns a description of all signals in the system.
   *
   * Lists inputs, outputs, parameters and setpoints.
   *
   * \return The description of all signals.
   */
  virtual std::vector<Signal> getSignalsDescription() const = 0;

  double getSignal(std::size_t i) { return signal_[i]; };
  void   setSignal(std::size_t i, double value) { signal_[i] = value; }

  /**
   * !brief f
   * !param x The last state of the system
   * !param u The input of the system
   * !param t The time in seconds
   * !return The drivative of the system state, \dot x
   */
  virtual output_t f(const output_t& x, const input_t& u, const double& t) = 0;

 protected:
  std::vector<double> signal_;
};

}  // namespace simc::system
