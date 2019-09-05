#ifndef NEURONS_HPP
#define NEURONS_HPP

#include <functional>
#include <memory>
#include <vector>

#include "synapses.hpp"
#include "equation.hpp"

namespace cg {

class Neurons {
public:
    /// Alias for a smart pointer on Neurons
    using Ptr = std::unique_ptr<Neurons>;
    // Synapse is friend to access the internal potential of Neurons
    friend class Synapse;

    /// Constructor
    /// @param nb_neurons the number of neurons grouped in this instance
    explicit Neurons(unsigned int nb_neurons);
    /// FUll Constructor
    /// @param nb_neurons the number of neurons grouped in this instance
    /// @param init_potential the initial potiential of all neurons in this instance
    /// @param threshold when the potential of a neuron reaches threshold, a spike is fired
    explicit Neurons(
            unsigned int nb_neurons,
            num::EquaDiff common_equation);

    // Neurons class is non-copyable
    Neurons(Neurons&)
        = delete;
    Neurons& operator=(Neurons&) = delete;

    /// Performs one integration step, according to the integration functor
    /// @param dt the time step to make the integration
    /// @param curr_time the cumulated running time of the current experiment
    template <typename IntegrationPolicy>
        void step(double dt, double curr_time, IntegrationPolicy integration_method);

    /// Performs one integration step, according to static integration method
    /// @param StaticIntegrationPolicy a type providing a static integration method
    /// @param dt the time step to make the integration
    /// @param curr_time the cumulated running time of the current experiment
    template <typename StaticIntegrationPolicy>
        void step(double dt, double curr_time);

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
    /// @param dst the group of neurons that will receive the spikes from the instance
    /// @param synapse_weight the weight applied to the synapse connecting this instance to dst
    Neurons& operator()(Neurons& dst, double synapse_weight);

private:
    std::vector<double> m_potentials;
    const num::EquaDiff m_common_equation;
    std::vector<double> m_spike_buffer;
    std::vector<Synapse> m_connexions;
};

/// Helper function to create a smart pointer on Neurons
/// @params Args... the arguments with which to call the constructor of Neurons
/// @returns a Neurons::Ptr pointer on a dynamically created instance of Neurons
template <typename... Args>
Neurons::Ptr make_neurons(Args... args)
{
    return std::make_unique<Neurons>(args...);
}

template <typename IntegrationPolicy>
void Neurons::step(double dt, double curr_time, IntegrationPolicy method)
{
    std::vector<bool> spikes(count(), false);
    for (size_t n = 0, nb_neurons = count(); n < nb_neurons; ++n) {
        // Applying integration method
        m_potentials[n] += method.integrate(m_common_equation.diff_fct, curr_time, dt, m_potentials[n]);

        // Spike iff the potential is above the threshold
        spikes[n] = (m_potentials[n] > m_common_equation.threshold);
    }

    for (auto& synapse : m_connexions) {
        synapse.transmit_spike(std::move(spikes));
    }
}

template <typename StaticIntegrationPolicy>
void Neurons::step(double dt, double curr_time)
{
    std::vector<bool> spikes(count(), false);
    for (size_t n = 0, nb_neurons = count(); n < nb_neurons; ++n) {
        // Applying integration method
        m_potentials[n] += StaticIntegrationPolicy::integrate(m_common_equation.diff_fct, curr_time, dt, m_potentials[n]);

        // Spike iff the potential is above the threshold
        spikes[n] = (m_potentials[n] > m_common_equation.threshold);
    }

    for (auto& synapse : m_connexions) {
        synapse.transmit_spike(std::move(spikes));
    }
}

} // namespace cg

#endif // NEURONS_HPP
