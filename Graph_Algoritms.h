//
// Created by Фёдор Захаров on 14.04.2022.
//
#include "vector"

#ifndef GRAPH_ALGORITHM_GRAPH_ALGORITMS_H
#define GRAPH_ALGORITHM_GRAPH_ALGORITMS_H

using node_name_t = int;
using weight_t = double;

using route_t = std::vector<node_name_t>;
using matrix_t = Matrix<weight_t>;
using graph_t = Graph<node_name_t,weight_t,weight_t>;

template<typename Key = node_name_t,
        typename Value = weight_t,
        typename Weight = weight_t>
Graph<Key,Value,Weight> read_graph(const char* file_name);

std::pair<weight_t, route_t> dijkstra(const graph_t &graph, const node_name_t &key_from, const node_name_t &key_to);

#endif //GRAPH_ALGORITHM_GRAPH_ALGORITMS_H
#include "Graph_Algoritms.hpp"