/**@file	/home/talos/Projets/Menli/sources/graph.hpp
 * @author	talos
 * @version	801
 * @date
 * 	Created:	10th Aug 2019
 * 	Last Update:	10th Aug 2019
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <memory>
#include <vector>
#include <unordered_map>

#include "neurons.hpp"
#include "synapses.hpp"

namespace cg
{

class Graph
{
    public:
        using Ptr = std::shared_ptr<Graph>;

        template <typename ...Args>
        Group::Ptr add_create_group(Args ...);
        void add_group(Group::Ptr group);

        template <typename ...Args>
        Synapses::Ptr add_create_synapse(Args...);
        void add_synapse(std::shared_ptr<Synapses> synapse);

        void run(double dt, unsigned int nb_step=1);
        void run(double dt, double runtime);

        friend std::ostream& operator<<(std::ostream& stream, Graph::Ptr g);

    private:
        void step(double dt);

    private:
        std::vector<std::shared_ptr<Group>>     m_groups;
        std::unordered_map<Group::Ptr, std::vector<Synapses::Ptr>> m_connections;
};

Graph::Ptr make_graph();

template <typename ...Args>
Group::Ptr  Graph::add_create_group(Args... args) {
    auto ptr = make_group(args...);
    add_group(ptr);
    return ptr;
}

template <typename ...Args>
Synapses::Ptr Graph::add_create_synapse(Args... args) {
    auto ptr = make_synapses(args...);
    add_synapse(ptr);
    return ptr;
}

}
// namespace cg

#endif // GRAPH_HPP
