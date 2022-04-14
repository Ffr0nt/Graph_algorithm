//
// Created by Фёдор Захаров on 14.04.2022.
//

#ifndef GRAPH_ALGORITHM_GRAPH_ALGORITMS_H
#define GRAPH_ALGORITHM_GRAPH_ALGORITMS_H

using node_name_t = int;
using weight_t = double;
using route_t = std::vector< node_name_t, Allocator<node_name_t> >;
using matrix_t = Matrix<weight_t>;

template<typename Key = int,
        typename Value,
        typename Weight = double>
Graph<Key,Value,Weight> read_graph(const char* file_name);


#include "Graph_Algoritms.hpp"
#endif //GRAPH_ALGORITHM_GRAPH_ALGORITMS_H
