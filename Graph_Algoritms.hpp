//
// Created by Фёдор Захаров on 14.04.2022.
//

#ifndef GRAPH_ALGORITHM_GRAPH_ALGORITMS_HPP
#define GRAPH_ALGORITHM_GRAPH_ALGORITMS_HPP
#include "Fileswork.cpp"

template<typename Key, typename Value, typename Weight>
Graph<Key, Value, Weight> read_graph(const char *file_name) {
    BinaryMode<weight_t> BM;
    matrix_t matrix = BM.read(file_name);

    return Graph<Key, Value, Weight>();
}

#endif //GRAPH_ALGORITHM_GRAPH_ALGORITMS_HPP
