#include <cmath>

#include "../include/graph.hpp" // TODO Absolute path

namespace cg
{

void Graph::add_neurons(Neurons::Ptr&& ptr) {
    m_nodes.emplace_back(std::move(ptr));
}

}  // namespace cg


