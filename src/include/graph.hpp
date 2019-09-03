#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <memory>
#include <unordered_map>
#include <vector>
#include <cmath>

#include "integrate.hpp"
#include "neurons.hpp"

namespace cg {

class Graph {
public:
    Graph() = default;
    Graph(Graph&&) = default;
    Graph& operator=(Graph&&) = default;

    void add_neurons(Neurons::Ptr&& ptr);

    template <typename... Args>
        Neurons& add_create_neurons(Args... args);

    /// Runs the computations for a given number of iterations
    template <typename StaticIntegrationPolicy = num::RK4>
        void run(double dt, unsigned int nb_iterations);
    /// Runs the computations for a given amount of simulation time (not real-time)
    template <typename StaticIntegrationPolicy = num::RK4>
        void run(double dt, double runtime);

private:
    /// Performs one simulation iteration
    template <typename StaticIntegrationPolicy>
        void step(double dt);

private:
    /// All the neurons group that belong to this computational graph
    std::vector<Neurons::Ptr> m_nodes;

    /// Cumulated runtime of the experiment
    double m_cumulated_runtime;
};

template <typename... Args>
Neurons& Graph::add_create_neurons(Args... args)
{
    // Create unique_ptr on Neurons
    auto neurons_ptr = make_neurons(args...);
    // Access underlying raw pointer
    Neurons* u_ptr = neurons_ptr.get();

    add_neurons(std::move(neurons_ptr));
    return *u_ptr;
}

#include "graph_impl.hpp"

} //namespace cg

#endif // GRAPH_HPP
