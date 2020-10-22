#pragma once

#include <string>
#include <tuple>
#include <vector>

namespace simc {

/**
 * Elements of the tuple:
 * - Name
 * - Unit
 * - Min
 * - Max
 * - Precision
 */
using Parameter = std::tuple<std::string, std::string, double, double, double>;

using Parameter_vector = std::vector<parameter_t>;

}  // namespace simc
