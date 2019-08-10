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

Group::Group(unsigned int nb_neurons, double init_pot)
: m_potentials(nb_neurons, init_pot)
, m_diff([] (double dt) {return 1.0 * dt;})
, m_threshold(1.0) // TODO hardcoded value
{}

std::vector<bool> Group::step(double dt)
{
    std::vector<bool> fires(m_potentials.size(), false);
    for(size_t i = 0; i < m_potentials.size(); ++i) {
        m_potentials[i] += m_diff(dt);
        if (m_potentials[i] > m_threshold) {
            m_potentials[i] = 0.0;
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
            m_potentials[i] += weight;
        }
    }
}

unsigned int Group::count() const {
    return m_potentials.size();
}

}
// namespace cg
