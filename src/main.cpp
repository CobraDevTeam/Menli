#include <vector>
#include <iostream>
#include "functions.h"
#include "neuron.h"
#include <memory>

int main(int argc, char** argv) {
    ExcitatoryLinear a = ExcitatoryLinear(std::shared_ptr<double>(new double(1.0)));
    InhibitorLinear b = InhibitorLinear(std::shared_ptr<double>(new double(1.0)));
    std::cout << b(argc);
    return 0;
}
