#ifndef INTEGRATE_HPP
#define INTEGRATE_HPP

#include <functional>

namespace num
{

struct Euler {
    double integrate(std::function<double(double, double)> rate_fct, double t0, double y0, double dt) {
        return y0 + dt*rate_fct(t0, y0);
    }
};

struct RungeKutta4 {
    double integrate(std::function<double(double, double)> rate_fct, double t0, double y0, double dt) {
        double k1 = dt*rate_fct(t0, y0);
        double k2 = dt*rate_fct(t0 + dt/2, y0 + k1/2);
        double k3 = dt*rate_fct(t0 + dt/2, y0 + k2/2);
        double k4 = dt*rate_fct(t0 + dt, y0 + k3);

        return y0 + (k1 + 2*k2 + 2*k3 + k4)/6;
    }
};

} // Namespace num

#endif // INTEGRATE_HPP
