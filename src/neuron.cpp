#include "neuron.h"

#include <iterator>
#include <algorithm>


Neuron::Neuron(float threshold, bool isExcitatory){
    m_threshold = threshold;
    m_synapsesList = std::vector<std::pair<std::shared_ptr<Neuron>,float>>();
    m_isExcitatory = isExcitatory;
}

Neuron::~Neuron(){

}

void Neuron::addNeuron(float weight, std::shared_ptr<Neuron> neuronToConnect){
    m_synapsesList.push_back(std::make_pair(neuronToConnect, weight));
}

void Neuron::fireNeuron(){
    std::for_each(m_synapsesList.begin(),m_synapsesList.end(), [&](std::pair<std::shared_ptr<Neuron>, float> currentSynapse){
        std::unique_ptr<ResponseFunction> responseFunction = m_isExcitatory
            ? std::unique_ptr<ResponseFunction>(new ExcitatoryLinear(std::shared_ptr<double>(new double(currentSynapse.second))))
            : std::unique_ptr<ResponseFunction>(new InhibitorLinear(std::shared_ptr<double>(new double(currentSynapse.second))));

        currentSynapse.first->receiveSpike(responseFunction);
    });
}


void receiveSpike(std::shared_ptr<ResponseFunction>& responseFunction){

}
