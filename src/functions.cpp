#include "functions.h"

ExcitatoryLinear::ExcitatoryLinear(std::shared_ptr<double> weight){
    m_weight=weight;
}

double ExcitatoryLinear::operator()(int timeCounter){
    if (timeCounter < 2 || timeCounter > 12){
        return 0.0;
    }
    else {
        return *m_weight * (1.0 - ((double) timeCounter - 2)/10.0);
    }
}

InhibitorLinear::InhibitorLinear(std::shared_ptr<double> weight){
    m_weight=weight;
}

double InhibitorLinear::operator()(int timeCounter){
    if (timeCounter < 2 || timeCounter > 12){
        return 0.0;
    }
    else {
        return *m_weight * (-0.5 + ((double) timeCounter - 2)/20.0);
    }
}
