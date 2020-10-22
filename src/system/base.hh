#pragma once

#include <utilities/noncopyable.hh>

#include <parameter.hh>

namespace simc::system {

template <typename state_t, typename input_t, typename output_t, typename parameters_t>
struct Base : public utilities::noncopyable {
  virtual ~Base() = default;

  Parameter_vector getParameters() const                         = 0;
  void             setParameter(uint16_t i, const double& value) = 0;

  void setParameters(const parameters_t& p) { m_parameters = p; }

  virtual state_t  A(const state_t& x_k) = 0;
  virtual state_t  B(const state_t& x_k) = 0;
  virtual output_t C(const state_t& x_k) = 0;
  virtual output_t D(const state_t& x_k) = 0;

 protected:
  parameters_t m_parameters;
};

}  // namespace simc::system
