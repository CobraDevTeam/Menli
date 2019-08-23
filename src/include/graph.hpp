#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <memory>
#include <vector>
#include <unordered_map>

#include "neurons.hpp"

namespace cg
{

class Graph {
public:
    Graph(Graph&&) = default;
    Graph& operator=(Graph&&) = default;

    void add_neurons(Neurons::Ptr&& ptr);
    template<typename ...Args>
        Neurons& add_create_neurons(Args... args);

    /// Runs the computations for a given number of iterations
    void run(double dt, unsigned int nb_iterations);
    /// Runs the computations for a given amount of simulation time (not real-time)
    void run(double dt, double runtime);

private:
    /// Performs one simulation iteration
    void step(double dt);

    /// All the neurons group that belong to this computational graph
    std::vector<Neurons::Ptr> m_nodes;
};

template<typename ...Args>
Neurons& add_create_neurons(Args... args) {
    // Create unique_ptr on Neurons
    auto neurons_ptr = make_neurons(args...);
    // Access underlying raw pointer
    Neurons* u_ptr = neurons_ptr.get();

    add_neurons(std::move(neurons_ptr));
    return *u_ptr;
}

} //namespace cg

#endif  // GRAPH_HPP
