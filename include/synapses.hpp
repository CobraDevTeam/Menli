/**@file	/home/talos/Projets/Menli/sources/synapses.hpp
 * @author	talos
 * @version	801
 * @date
 * 	Created:	10th Aug 2019
 * 	Last Update:	10th Aug 2019
 */

#ifndef SYNAPSES_hPP
#define SYNAPSES_hPP

#include <memory>

#include "neurons.hpp"

namespace cg
{

class Graph;

class Synapses : public std::enable_shared_from_this<Synapses>
{
    public:
        using Ptr = std::shared_ptr<Synapses>;

        Synapses(Group::Ptr src, Group::Ptr dst);
        Synapses(Group::Ptr src, Group::Ptr dst, std::function<bool(size_t, size_t)> match_func);
        Group::Ptr src() const;
        Group::Ptr dst() const;

        void transmit(std::vector<bool> targets) const;

    private:
        Group::Ptr      m_src;
        Group::Ptr      m_dst;
        std::function<bool(size_t, size_t)> m_connect;
        double  m_weight;
};

template <typename ...Args>
Synapses::Ptr make_synapses(Args... args)
{
    return std::make_shared<Synapses>(args...);
}

}
// namespace cg

#endif // SYNAPSES_hPP
