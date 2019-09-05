#ifndef SYNAPSES_HPP
#define SYNAPSES_HPP

#include <functional>
#include <memory>
#include <vector>

namespace cg
{

class Neurons;

class Synapse {
public:
    using MatchFunction = std::function<bool(size_t, size_t)>;

    explicit Synapse(Neurons& m_dst, double weight, MatchFunction match_fct = [] (size_t i, size_t j) { return i == j;});

    void transmit_spike(std::vector<bool>&& spikes);

private:
    Neurons& m_dst;
    MatchFunction m_match_fct;
    double m_weight;
};

}  // namespace cg

#endif // SYNAPSES_HPP
