//
// Created by Фёдор Захаров on 14.04.2022.
//

#ifndef GRAPH_ALGORITHM_GRAPH_ALGORITMS_HPP
#define GRAPH_ALGORITHM_GRAPH_ALGORITMS_HPP

#include "Fileswork.cpp"
#include "Graph_Algoritms.h"
#include <limits>

const int inf = std::numeric_limits<double>::infinity();

bool is_equal(double x, double y) {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

template<typename Key, typename Value, typename Weight>
Graph<Key, Value, Weight> read_graph(const char *file_name) {
    BinaryMode<weight_t> BM;
    matrix_t matrix = BM.read(file_name);

    fstream fileStream(file_name);
    if (fileStream.good() == 0)
        throw std::runtime_error("No file by such root.");

    if (matrix.get_rows() != matrix.get_columns())
        throw std::runtime_error("\nThat matrix is not square! \nSizes: " + to_string(matrix.get_rows()) + " x " \
 + to_string(matrix.get_columns()) + "\nNo point in converting to graph.");

    Graph<Key, Value, Weight> gr = matrix;
    return gr;
}

////--------------------------------|my personal hell -- recursive dijkstra|----------------------------
//std::pair<weight_t, route_t> recursive_dijkstra(
//        Graph<node_name_t, std::pair<bool, weight_t>, weight_t> &clone,\
//        route_t& act_root,\
//        route_t& answer,\
//       const  node_name_t& aim,\
//       const  node_name_t& key_from,\
//       weight_t& root_wight,\
//       weight_t& root_wight_to_answer\
//        ) {
//
//    if(clone[key_from].first == true){return {root_wight_to_answer, answer};}
//    else clone[key_from].first = true;
//
//    act_root.push_back(key_from);
//
//    // if new node is searched one
//    if (key_from == aim) {
//        if (root_wight <  root_wight_to_answer){
//            root_wight_to_answer = root_wight;
//            answer = act_root;
//        }
//    }
//
//    // for each node change value
//    for (auto&[edge_go_to_key, edge_w]: clone.get_con_nodes(key_from) ) {
//        if ( root_wight + edge_w < clone[edge_go_to_key].second) clone[edge_go_to_key].second = root_wight + edge_w;
//    }
//
//    // for each node do the same step
//    for (auto&[edge_go_to_key, edge_w]: clone.get_con_nodes(key_from)) {
//        auto w = root_wight + edge_w;
//        recursive_dijkstra(clone, act_root, answer, aim, edge_go_to_key, w, root_wight_to_answer);
//    }
//
//    return  {root_wight_to_answer, answer};
//}

////--------------------------------|dijkstra|----------------------------
std::pair<weight_t, route_t> dijkstra(const graph_t &graph, const node_name_t &key_from, const node_name_t &key_to) {

    //check if there are negative edges
    for (auto&[node_key, node]: graph) {
        for (auto&[edge_key, edge]: node) {
            if (edge < 0)
                throw std::runtime_error("\nNegative wight of edge: " + to_string(edge) + \
            " Between \"" + to_string(node_key) + "\" and \"" + to_string(edge_key) + "\" nodes.\nDijkstra algorithm" \
 + " can't be applied.");
        }
    }

    Graph <node_name_t,  weight_t, weight_t> clone (graph); // the one we will change throw algo

    for (auto&[node_key, node]: graph) {
        node.value() = inf;
    }

    route_t answer, act_root;
    double a_1 = 0;
    double a_2 = inf;


//    return recursive_dijkstra(clone, act_root, answer, key_to , key_from, a_1, a_2);
}



// check if there are negative edges +
// take out values of nodes + put in negative values in nodes (marked as non-visited)
//

#endif //GRAPH_ALGORITHM_GRAPH_ALGORITMS_HPP
