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
    // Create computational graph
    auto graph = cg::make_graph();

    // Create a group with 10 neurons and an initial potential of 0.0V
    auto g1 = cg::make_group(10, 0.0);
    // Add the group to the graph
    graph->add_group(g1);

    // Create a neuron group of 15 neurons and initial potential 1.0V,
    // and add it to the graph
    auto g2 = graph->add_create_group(15, 1.0);

    // Create a synapse connecting g1 to g2 with default (dumb) connection
    // i.e neuron src_i and dst_j are connect iff src_i == src_j
    auto s1 = cg::make_synapses(g1, g2);
    // Then add it to the graph
    graph->add_synapse(s1);

    // Create a new group and connect it to g3. We don't manage it but the graph does
    graph->add_create_synapse(g2, graph->add_create_group(10, 0.5));

    // Create a simple feedback : g1 connected to g1
    // The connection function is slightly more complicated
    graph->add_create_synapse(g1, g1, [] (size_t i, size_t j) {return (i+j)%2 == 1;});

    // Run graph for 0.1 second, with an integration step dt = 0.02s
    graph->run(/*dt=*/0.02, /*runtime=*/0.1);
    // Or run graph for 15 iterations, with an integration step dt= 0.03s
    // Notice cast, necessary because of implicit conversion to double. TODO: solve this
    graph->run(/*dt=*/0.03, /*nb_iter=*/uint(15));

    // Now, we have the following graph:
    // g1 <- g1 -> g2 -> g3
    // This function only displays the number of synapses per group
    std::cout << graph << std::endl;

    return 0;
}
