#ifndef EQUATION_HPP
#define EQUATION_HPP

#include <functional>

namespace num
{

/// Convenient alias for a function of time and potential (respectively)
/// which yield the derivative of the potential function of the Neurons
using DiffFct = std::function<double(double, double)>;

/// A struct encapsulating all common numerical data related to the internal
/// differential equation. A group a neurons is assumed to share one common such object
struct EquaDiff {
    /// Default Constructor
    EquaDiff() = default;
    /// FUll Constructor
    /// @params fct the derivative function on which the differential equation is based
    /// @params init_val initial potential value of the differential equation
    /// @params threshold potential above which the neurons will fire spikes
    EquaDiff(DiffFct fct, double init_value, double threshold);

    DiffFct diff_fct = [](double, double pot) { return pot; };
    double init_value = 1.0;
    double threshold = 10.0;
};

}
// namespace num

#endif // EQUATION_HPP
