#ifndef INTEGRATE_HPP
#define INTEGRATE_HPP

#include <functional>

namespace num
{

struct Euler {
    double integrate(std::function<double(double, double)> rate_fct, double t0, double y0, double dt);
};

struct RungeKutta4 {
    double integrate(std::function<double(double, double)> rate_fct, double t0, double y0, double dt);
};

using RK4 = RungeKutta4;

} // Namespace num

#endif // INTEGRATE_HPP
