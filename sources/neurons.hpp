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
        using Ptr = std::shared_ptr<Group>;

    public:
        Group(unsigned int nb_neurons, double init_pot);

        std::vector<bool>   step(double dt);
        void                integrate_spike(std::vector<bool> targets, double weight);
        unsigned int        count() const;

    private:
        std::vector<double>     m_potentials;
        std::function<double(double)> m_diff;
        double                          m_threshold;
};

template <typename ...Args>
Group::Ptr make_group(Args... args)
{
    return std::make_shared<Group>(args...);
}

}
// namespace cg

#endif // NEURONS_HPP
