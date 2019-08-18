#ifndef NEURON_H
#define NEURON_H

#include "functions.h"

#include <memory>
#include <vector>
#include <functional>

class Neuron {
    private:
        float m_threshold;
        float m_potential = 0.0;
        std::vector<std::pair<std::shared_ptr<Neuron>, float>> m_synapsesList;
        bool m_isExcitatory;



    public:
        Neuron(float threshold, bool isExcitatory);
        ~Neuron();
        float getOutput();
        float updatePotential();
        void fireNeuron();
        void addNeuron(float weight, std::shared_ptr<Neuron> neuronToConnect);
        void receiveSpike(std::unique_ptr<ResponseFunction>& responseFunction);

};


#endif
