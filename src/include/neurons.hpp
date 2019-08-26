#ifndef NEURONS_HPP
#define NEURONS_HPP

#include <memory>
#include <vector>

#include "synapses.hpp"

namespace cg
{


class Neurons {
public:
    /// Alias for a smart pointer on Neurons
    using Ptr = std::unique_ptr<Neurons>;
    // Synapse is friend to access the internal potential of Neurons
    friend class Synapse;

    /// Constructor
    /// @param nb_neurons the number of neurons grouped in this instance
    /// @param init_potential the initial potiential of all neurons in this instance
    /// @param threshold when the potential of a neuron reaches threshold, a spike is fired
    explicit Neurons(
            unsigned int nb_neurons,
            double init_potential = 0.0,
            double threshold=1.0);

    // Neurons class is non-copyable
    Neurons(Neurons&) = delete;
    Neurons& operator=(Neurons&) = delete;

    /// Performs one integration step, according to the inner integration method
    void step(double dt);
    /// Adds the spike_buffer to the actual internal potentials
    void integrate_spikes();

    /// A method to access the number of neurons grouped in an instance of Neurons
    /// @returns the number of neurons
    size_t count() const;
    /// Creates a synapse from the current instance toward dst
    /// @param dst the group of neurons that will receive the spikes from the instance
    /// @param synapse_weight the weight applied to the synapse connecting this instance to dst
    void connect(Neurons& dst, double synapse_weight);
    /// Similar to Neurons::connect, Keras/pytorch connection style
    /// Internally calls Neurons::connect
    Neurons& operator()(Neurons& dst, double synapse_weight);

private:
    std::vector<double> m_potentials;
    const double m_threshold;
    std::vector<Synapse> m_connexions;
    std::vector<double> m_spike_buffer;
};


/// Helper function to create a smart pointer on Neurons
/// @params Args... the arguments with which to call the constructor of Neurons
/// @returns a Neurons::Ptr pointer on a dynamically created instance of Neurons
template <typename ...Args>
Neurons::Ptr make_neurons(Args... args) {
    return std::make_unique<Neurons>(args...);
}

}  // namespace cg

#endif // NEURONS_HPP
