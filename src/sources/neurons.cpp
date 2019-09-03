#include "../include/neurons.hpp"

namespace cg {

Neurons::EquaDiff::EquaDiff(EquaDiff::DiffFct fct, double init_value, double threshold)
    : diff_fct(fct)
    , init_value(init_value)
    , threshold(threshold)
{
}

Neurons::Neurons(unsigned int nb_neurons)
    : Neurons(nb_neurons, EquaDiff())
{
}

Neurons::Neurons(unsigned int nb_neurons, EquaDiff common_eq)
    : m_potentials(nb_neurons, common_eq.init_value)
    , m_common_equation(std::move(common_eq))
    , m_spike_buffer(count(), 0.0)
{
}

void Neurons::integrate_spikes()
{
    for (size_t p = 0, nb_potentials = count(); p < nb_potentials; ++p) {
        m_potentials[p] += m_spike_buffer[p];
    }
}

size_t Neurons::count() const
{
    return m_potentials.size();
}

void Neurons::connect(Neurons& dst, double synapse_weight)
{
    m_connexions.emplace_back(dst, synapse_weight);
}

Neurons& Neurons::operator()(Neurons& dst, double synapse_weight)
{
    connect(dst, synapse_weight);
    return *this;
}

} // namespace cg
