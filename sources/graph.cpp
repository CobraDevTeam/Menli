/**@file	/home/talos/Projets/Menli/sources/graph.cpp
 * @author	talos
 * @version	801
 * @date
 * 	Created:	10th Aug 2019
 * 	Last Update:	10th Aug 2019
 */

#include <cmath>
#include <cassert>
#include <iostream>

#include "graph.hpp"
#include "neurons.hpp"
#include "synapses.hpp"

namespace cg
{

Graph::Ptr make_graph()
{
    return std::make_shared<Graph>();
}

void Graph::add_group(Group::Ptr group) {
    m_groups.push_back(std::move(group));
}

void Graph::add_synapse(Synapses::Ptr synapse) {
    auto found = m_connections.find(synapse->src());
    if(found != m_connections.end()) {
        found->second.push_back(synapse);
    }
    else {
        m_connections[synapse->src()] = std::vector<Synapses::Ptr>(1, synapse);
    }
}

void Graph::run(double dt, unsigned int nb_steps) {
    for(unsigned int s=0; s < nb_steps; ++s) {
        std::cout << "Step " << s << "/" << nb_steps << '\n';
        step(dt);
    }
    std::cout << std::endl;
}

void Graph::run(double dt, double runtime) {
    unsigned int nb_steps = static_cast<unsigned int>(std::floor(runtime/dt));
    run(dt, nb_steps);
}

void Graph::step(double dt) {
   for (auto itr = m_groups.begin(), end=m_groups.end(); itr != end; ++itr){
        // TODO why itr->step(dt); does not work ?
        auto firing = (*itr)->step(dt);
        auto vect_synapse = m_connections[*itr];
        for (auto& synapse : vect_synapse) {
            synapse->transmit(firing);
        }
   }
}

std::ostream& operator<<(std::ostream& stream, Graph::Ptr g) {
    for(size_t i=0, size=g->m_groups.size(); i < size; ++i) {
        auto found = g->m_connections.find(g->m_groups[i]);
        stream  << "Group " << i
                << " - COnnections : "
                << ((found != g->m_connections.end()) ? found->second.size() : 0)
                << '\n';
    }
    return stream;
}

}
// namespace cg
