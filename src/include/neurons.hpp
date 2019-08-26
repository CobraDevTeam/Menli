#ifndef NEURONS_HPP
#define NEURONS_HPP

#include <memory>
#include <vector>
#include <functional>

#include "synapses.hpp"

namespace cg
{


class Neurons {
public:
    /// Alias for a smart pointer on Neurons
    using Ptr = std::unique_ptr<Neurons>;
    // Synapse is friend to access the internal potential of Neurons
    friend class Synapse;

    /// A struct encapsulating all common numerical data related to the internal
    /// differential equation. A group a neurons is assumed to share one common such object
    struct EquaDiff {
        /// Convenient alias for a function of time and potential (respectively)
        /// which yield the derivative of the potential function of the Neurons
        using DiffFct = std::function<double(double, double)>;

        /// Constructor
        /// @params fct the derivative function on which the differential equation is based
        /// @params init_val initial potential value of the differential equation
        /// @params threshold potential above which the neurons will fire spikes
        EquaDiff(DiffFct fct, double init_value, double threshold);
        std::function<double(double, double)> diff_fct;
        double init_value;
        double threshold;
    };

    /// Constructor
    /// @param nb_neurons the number of neurons grouped in this instance
    /// @param init_potential the initial potiential of all neurons in this instance
    /// @param threshold when the potential of a neuron reaches threshold, a spike is fired
    explicit Neurons(
            unsigned int nb_neurons,
            EquaDiff common_equation);

    // Neurons class is non-copyable
    Neurons(Neurons&) = delete;
    Neurons& operator=(Neurons&) = delete;

    /// Performs one integration step, according to the inner integration method
    /// @param dt the time step to make the integration
    /// @param curr_time the cumulated running time of the current experiment
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
    Neurons& operator()(Neurons& dst, double synapse_weight);

private:
    std::vector<double> m_potentials;
    const EquaDiff m_common_equation;
    std::vector<double> m_spike_buffer;
    std::vector<Synapse> m_connexions;
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
