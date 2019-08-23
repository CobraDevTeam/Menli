#include "../include/synapses.hpp"
#include "../include/neurons.hpp"

namespace cg
{

Synapse::Synapse(Neurons& dst, double weight, MatchFunction fct)
    : m_dst(dst)
    , m_match_fct(fct)
    , m_weight(weight)
    {}

void Synapse::transmit_spike(std::vector<bool>&& spikes) {
    for (size_t s = 0, nb_spikes = spikes.size(); s < nb_spikes; ++s) {
        // if source neuron s did not fire, then skip match_function call
        if (!spikes[s]) {
            continue;
        }

        // source neuron s did fire, so need to compute to which neurons it is connected
        for (size_t n = 0, n_neurons = m_dst.count(); n < n_neurons;  ++n) {
            if (m_match_fct(s,n)) {
                m_dst.m_spike_buffer[n] += m_weight;
            }
        }
    }

}

}  // namespace cg

