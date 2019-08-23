#ifndef NEURONS_HPP
#define NEURONS_HPP

#include <memory>
#include <vector>

#include "synapses.hpp"

namespace cg
{


class Neurons {
public:
    using Ptr = std::unique_ptr<Neurons>;
    friend class Synapse;

    explicit Neurons(
            unsigned int nb_neurons,
            double init_potential = 0.0,
            double threshold=1.0);

    // Neurons class is non-copyable
    Neurons(Neurons&) = delete;
    Neurons& operator=(Neurons&) = delete;

    void step(double dt);
    void integrate_spikes();

    size_t count() const;
    void connect(Neurons& dst, double synapse_weight);
    // Keras/Pytorch style connexion via operator()
    Neurons& operator()(Neurons& dst, double synapse_weight);

private:
    std::vector<double> m_potentials;
    const double m_threshold;
    std::vector<Synapse> m_connexions;
    std::vector<double> m_spike_buffer;
};


template <typename ...Args>
Neurons::Ptr make_neurons(Args... args) {
    return std::make_unique<Neurons>(args...);
}

}  // namespace cg

#endif // NEURONS_HPP
