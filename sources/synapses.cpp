/**@file	/home/talos/Projets/Menli/sources/synapses.cpp
 * @author	talos
 * @version	801
 * @date
 * 	Created:	10th Aug 2019
 * 	Last Update:	10th Aug 2019
 */

#include "synapses.hpp"
#include "neurons.hpp"

namespace cg
{

Synapses::Synapses(Group::Ptr src, Group::Ptr dst)
: m_src(src)
, m_dst(dst)
, m_connect([] (size_t i, size_t j) {return i == j;})
{}

Synapses::Synapses( Group::Ptr src, Group::Ptr dst,
                    std::function<bool(size_t, size_t)> match_func)
: m_src(src)
, m_dst(dst)
, m_connect(match_func)
{}

Group::Ptr Synapses::src() const {
    return m_src;
}

Group::Ptr Synapses::dst() const {
    return m_dst;
}

void Synapses::transmit(std::vector<bool> firing) const {
    std::vector<bool> spikes(m_dst->count(), true);
    for(size_t dst_i = 0, dst_size = m_dst->count(); dst_i < dst_size; ++dst_i) {
        for(size_t src_i = 0, src_size = m_src->count(); src_i < src_size; ++src_i) {
            // spike iff neuron src_i fires && neuron src_i connected to neuron dst_i
            spikes[dst_i] = firing[src_i] && m_connect(src_i, dst_i);
        }
    }

    m_dst->integrate_spike(spikes, m_weight);
}

}
// namespace cg
