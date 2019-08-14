/**@file	/home/talos/Projets/Menli/sources/neurons.hpp
 * @author	talos
 * @version	801
 * @date
 * 	Created:	10th Aug 2019
 * 	Last Update:	10th Aug 2019
 */

#ifndef NEURONS_HPP
#define NEURONS_HPP

#include <memory>
#include <vector>
#include <functional>

namespace cg
{

class Graph;

class Group
{
    public:
        // Numerical stuff
        // Should really be put in its own file and namespace
        // Is a really lazy and basic implementation of homogeneity enforcing
        template <typename Phantom>
        struct Named {
            explicit Named(double v): val(v) {}
            Named& operator=(const Named& x) {val = x.val; return *this;}
            void   operator+=(const Named& x) {val += x.val;}
            double val;
        };

        using Potential = Named<struct PotParam>;
        using Time      = Named<struct TParam>;
        using DPotDt    = Named<struct DPotDtParam>;


        using Ptr = std::shared_ptr<Group>;
        using DfType = std::function<DPotDt(Time, Potential)>;

    public:
        Group(unsigned int nb_neurons, double init_pot);
        Group(  unsigned int nb_neurons,
                double init_pot,
                std::function<double(double, double)>);

        std::vector<bool>   step(double dt);
        void                integrate_spike(std::vector<bool> targets, double weight);
        unsigned int        count() const;

    private:
        std::vector<Potential>  m_potentials;
        const DfType            m_diff;
        const double            m_threshold;
};
template <typename ...Args>
Group::Ptr make_group(Args... args)
{
    return std::make_shared<Group>(args...);
}

}
// namespace cg

#endif // NEURONS_HPP
