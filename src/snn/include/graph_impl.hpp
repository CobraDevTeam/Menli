#ifndef GRAPH_IMPL_HPP
#define GRAPH_IMPL_HPP

template <typename SIP>
void Graph::run(double dt, unsigned int nb_iterations) {
    for (unsigned int iter = 0; iter < nb_iterations; ++iter) {
        step<SIP>(dt);
    }
}

template <typename SIP>
void Graph::run(double dt, double runtime) {
    unsigned int nb_iterations = static_cast<unsigned int>(std::floor(runtime/dt));
    run<SIP>(dt, nb_iterations);
}

template <typename SIP>
void Graph::step(double dt) {
    // integrate the spikes from the previous iteration
    for(auto& neurons : m_nodes) {
        neurons->integrate_spikes();
    }

    // Solve diff. equa. to modify internal potentials, fires if potential above threshold
    for(auto& neurons : m_nodes) {
        // FIXME m_cumulated_runtime + dt/2 may be more accurate here ?
        neurons->step<SIP>(dt, m_cumulated_runtime);
    }

    m_cumulated_runtime += dt;
}
#endif // GRAPH_IMPL_HPP
