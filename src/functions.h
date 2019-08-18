#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <memory>

class ResponseFunction {
    public:
        virtual double operator()(int timeCounter) = 0;
};

class ExcitatoryLinear : public ResponseFunction {
    private:
        std::shared_ptr<double> m_weight;

    public:
        ExcitatoryLinear(std::shared_ptr<double> weight);
        double operator()(int timeCounter);

};

class InhibitorLinear : public ResponseFunction{
    private:
        std::shared_ptr<double> m_weight;

    public:
        InhibitorLinear(std::shared_ptr<double> weight);
        double operator()(int timeCounter);
};

#endif
