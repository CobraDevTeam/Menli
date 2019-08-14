/**@file	/home/talos/Projets/Menli/sources/neurons.cpp
 * @author	talos
 * @version	801
 * @date
 * 	Created:	10th Aug 2019
 * 	Last Update:	10th Aug 2019
 */

#include <cassert>
#include <iostream>

#include "neurons.hpp"
#include "graph.hpp"

namespace cg
{

Group::Group(unsigned int nb_neurons, double init_pot, std::function<double(double, double)> df)
: m_potentials(nb_neurons, Potential(init_pot))
, m_diff([df] (Time t, Potential p) {return DPotDt(df(t.val, p.val));})
, m_threshold(1.0) // TODO hardcoded value
{}

Group::Group(unsigned int nb_neurons, double init_pot)
: Group(nb_neurons, init_pot, [] (double, double p) {return p * 1.0;})
{}

Group::Potential operator*(Group::Time lhs, Group::DPotDt rhs) {return Group::Potential(lhs.val * rhs.val);}

std::vector<bool> Group::step(double dt)
{
    std::vector<bool> fires(m_potentials.size(), false);
    for(size_t i = 0; i < m_potentials.size(); ++i) {
        // MOST BASIC implementation of Euler's algorithm
        // Given df/dt = g(t, f(t)), assumes that g(t,f(t)) = h(f(t)) (independent of time)
        m_potentials[i] += Time(dt) * m_diff(Time(0.0), m_potentials[i]);
        if (m_potentials[i].val > m_threshold) {
            m_potentials[i] = Potential(0.0);
            fires[i] = true;
        }
    }

    return fires;
}

void Group::integrate_spike(std::vector<bool> targets, double weight)
{
    assert(targets.size() == m_potentials.size());
    for (size_t i =0; i < m_potentials.size(); ++i) {
        if(targets[i]) {
            m_potentials[i] += Potential(weight);
        }
    }
}

unsigned int Group::count() const {
    return m_potentials.size();
}

}
// namespace cg
