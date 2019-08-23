#include <cmath>

#include "../include/graph.hpp" // TODO Absolute path

namespace cg
{

void Graph::add_neurons(Neurons::Ptr&& ptr) {
    m_nodes.emplace_back(std::move(ptr));
}

void Graph::run(double dt, unsigned int nb_iterations) {
    for (unsigned int iter = 0; iter < nb_iterations; ++iter) {
        step(dt);
    }
}

void Graph::run(double dt, double runtime) {
    unsigned int nb_iterations = static_cast<unsigned int>(std::floor(runtime/dt));
    run(dt, nb_iterations);
}

void Graph::step(double dt) {
    // integrate the spikes from the previous iteration
    for(auto& neurons : m_nodes) {
        neurons->integrate_spikes();
    }

    // Solve diff. equa. to modify internal potential, fires if potential above threshold
    for(auto& neurons : m_nodes) {
        neurons->step(dt);
    }
}

}  // namespace cg


