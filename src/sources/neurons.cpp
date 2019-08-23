#include "../include/neurons.hpp"

namespace cg
{

Neurons::Neurons(unsigned int nb_neurons, double init_potential, double threshold)
    : m_potentials(nb_neurons, init_potential)
    , m_threshold(threshold)
    //, m_connexions()
    , m_spike_buffer(count(), 0.0)
    {}

void Neurons::step(double dt) {
    std::vector<bool> spikes(count(), false);
    for(size_t n = 0, nb_neurons = count(); n < nb_neurons; ++n) {
        // Linear diffential increase of the potential
        m_potentials[n] += + 1.0 * dt;

        spikes[n] = (m_potentials[n] > m_threshold);
    }

    for(auto& synapse : m_connexions) {
        synapse.transmit_spike(std::move(spikes));
    }
}

void Neurons::integrate_spikes() {
    for (size_t p = 0, nb_potentials = count(); p < nb_potentials; ++p) {
        m_potentials[p] += m_spike_buffer[p];
    }
}

size_t Neurons::count() const {
    return m_potentials.size();
}

void Neurons::connect(Neurons& dst, double synapse_weight) {
    m_connexions.emplace_back(dst, synapse_weight);
}

Neurons& Neurons::operator()(Neurons& dst, double synapse_weight) {
    connect(dst, synapse_weight);
    return *this;
}

}  // namespace cg

