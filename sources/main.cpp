/**@file	/home/talos/Projets/Menli/sources/main.cpp
 * @author	talos
 * @version	801
 * @date
 * 	Created:	29th Jul 2019
 * 	Last Update:	29th Jul 2019
 */

#include <iostream>

#include "graph.hpp"
#include "neurons.hpp"

int main()
{
    auto graph = cg::make_graph();
    auto g1 = cg::make_group(10, 0.0);

    graph->add_group(g1);
    auto g2 = graph->add_create_group(15, 1.0);

    graph->add_create_synapse(g1, g2);
    //graph->add_synapse(g2, g1, [] (size_t i, size_t j) {return i+j == 10;});
    graph->run(0.01, 1.0);

    std::cout << graph << std::endl;

    return 0;
}
