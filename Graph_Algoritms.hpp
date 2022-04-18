//
// Created by Фёдор Захаров on 14.04.2022.
//

#ifndef GRAPH_ALGORITHM_GRAPH_ALGORITMS_HPP
#define GRAPH_ALGORITHM_GRAPH_ALGORITMS_HPP

#include "Fileswork.cpp"
#include "Graph_Algoritms.h"
#include <limits>
#include <list>

template<typename Key ,
        typename Value ,
        typename Weight >
void print(const Graph<Key ,Value ,Weight> &graph) {
    if (graph.empty()) {
        std::cout << "> This graph is empty!" << std::endl;
        return;
    }
    std::cout << "> Size of graph: " << graph.size() << std::endl;
    for (const auto&[key, node]: graph) {
        std::cout << '[' << key << "] stores: " << //double( graph[key] ) <<
                  " and matches with:" << std::endl;
        for (const auto&[key, weight]: node)
            std::cout << "\t[" << key << "]\t with weight: "
                      << weight << std::endl;
    }
}

const int inf = std::numeric_limits<double>::infinity();

bool is_equal(double x, double y) {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

bool is_not_in(list<std::pair<node_name_t, weight_t> > list,node_name_t key ){
    for (auto& it: list) {
        if (it.first == key) return false;
    }
    return true;
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
//  the one we will change throw algo
    Graph<node_name_t, std::pair<weight_t, route_t>, weight_t> clone;

//  set up values and weights
    for (auto&[node_key, node]: graph) {
        clone.insert_node(node_key, {inf, route_t()});
    }
    clone[key_from].first = 0;
    clone[key_from].second.push_back(key_from);
    for (auto&[node_key, node]: graph) {
        for (auto&[key_node_to, edge]: node) {
            clone.insert_edge({node_key, key_node_to}, edge);
        }
    }

//  create list to find the smallest wight
    list<std::pair<node_name_t, weight_t> > non_vis;

    for (auto[node_key, node]: clone) {
        non_vis.push_back({node_key, node.value().first});
    }

    node_name_t processed_key;
    for (size_t i = 0; i < clone.size(); ++i) {
        non_vis.sort([](std::pair<node_name_t, weight_t> x, std::pair<node_name_t, weight_t> y) {
            return x.second < y.second;
        });
        for (auto it : non_vis) std::cout  << (it).first << " ";

        processed_key = non_vis.front().first;
        non_vis.pop_front();

        std::cout <<  " processed_key: " << processed_key  << "--"<<std::endl;

        for (auto&[key_node_to, w_edge]: clone.get_con_nodes(processed_key)) {

            if (is_not_in(non_vis, key_node_to) ) { continue; }//if was visited

            std::cout<< key_node_to  <<std::endl;
//            std::cout << clone[key_node_to].first << " " << clone[processed_key].first << " " << w_edge;
            if ((i == 3)&&(processed_key == 4)){
                volatile int a =3;
                std::cout << " ! ";
            }

            if (clone[key_node_to].first > clone[processed_key].first + w_edge) {
                clone[key_node_to].first = clone[processed_key].first + w_edge;
                clone[key_node_to].second =  clone[processed_key].second;
                (clone[key_node_to].second).push_back(key_node_to);
            }

        }

    }

//print(clone);
//    for (auto&[key, w]: clone) {
//        std::cout << clone[key].first << std::endl;
//    }
    return clone[key_to];
}



// check if there are negative edges +
// take out values of nodes + put in negative values in nodes (marked as non-visited)
//

#endif //GRAPH_ALGORITHM_GRAPH_ALGORITMS_HPP
