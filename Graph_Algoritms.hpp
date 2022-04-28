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
    fstream fileStream(file_name);
    if (fileStream.good() == 0)
        throw std::runtime_error("No file by such root.");

    BinaryMode<weight_t> BM;
    matrix_t matrix = BM.read(file_name);


    if (matrix.get_rows() != matrix.get_columns())
        throw std::runtime_error("\nThat matrix is not square! \nSizes: " + to_string(matrix.get_rows()) + " x " \
 + to_string(matrix.get_columns()) + "\nNo point in converting to graph.");

    Graph<Key, Value, Weight> gr = matrix;
    return gr;
}


// finds the shortest way from  key_from to key_to in graph
// if there is a way returns a pair of resulting weight and vector with rout of node names
// if there is no way returns a pair of -1 weight and vector with key_to
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
    if (graph.find(key_from) == graph.end()){throw std::runtime_error("\n There is no such a node: " \
    + to_string(key_from)  + ", change key_from parameter." );}

    if (graph.find(key_to) == graph.end()){throw std::runtime_error("\n There is no such a node: " \
    + to_string(key_to)  + ", change key_to parameter." );}


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

//    for every node
    node_name_t processed_key;
    for (size_t i = 0; i < clone.size(); ++i) {
//        sorting each time will give us the smallest number
        non_vis.sort([](const std::pair<node_name_t, weight_t>& x, const std::pair<node_name_t, weight_t>& y) {
            return (x.second) < (y.second);
        });
//  delete from non_vis list
        processed_key = non_vis.front().first;
        non_vis.pop_front();

        // if that node wasn't neighbour before it won't be in future
        if( is_equal( clone[processed_key].first, inf) ){continue;}

// for each nebear node recalculate smallest way to
        for (auto&[key_node_to, w_edge]: clone.get_con_nodes(processed_key)) {

            if (is_not_in(non_vis, key_node_to) ) { continue; }//if was visited

            if (clone[key_node_to].first > clone[processed_key].first + w_edge) { // if closer way was found

                //  rewrite new distance to non_vis list
                non_vis.remove({key_node_to,clone[key_node_to].first});
                non_vis.push_front({key_node_to,clone[processed_key].first + w_edge});

                //  rewrite new distance and root to node
                clone[key_node_to].first = clone[processed_key].first + w_edge;
                clone[key_node_to].second =  clone[processed_key].second;
                (clone[key_node_to].second).push_back(key_node_to);
            }

        }

    }

//    in a case there were no way between
    if ( is_equal( clone[key_to].first, inf) ){
//        throw std::runtime_error("\n There is no way between: " + to_string(key_from)  + " and "  + to_string(key_to));
        std::cout << "\nThere is no way between: " + to_string(key_from)  + " and "  + to_string(key_to) << ". Be careful!"<<std::endl;
        return {-1,{key_to}};
        }

    return clone[key_to];
}


// finds the shortest way from  key_from to every key in end_vec in graph
// if there is a way adds a pair of resulting weight and vector with rout of node names to answer
// if there is no way adds a pair of -1 weight and vector with key_to to answer
// return answer - vector with all pairs
std::vector<std::pair<weight_t, route_t> >
dijkstra(const graph_t &graph, const node_name_t &key_from, const  vector<const node_name_t> &end_vec) {
    for (auto&[node_key, node]: graph) {
        for (auto&[edge_key, edge]: node) {
            if (edge < 0)
                throw std::runtime_error("\nNegative wight of edge: " + to_string(edge) + \
            " Between \"" + to_string(node_key) + "\" and \"" + to_string(edge_key) + "\" nodes.\nDijkstra algorithm" \
 + " can't be applied.");
        }
    }
    if (graph.find(key_from) == graph.end()){throw std::runtime_error("\n There is no such a node: " \
    + to_string(key_from)  + ", change key_from parameter." );}

//    check every key to existence
    for (auto& end_key: end_vec) {
        if (graph.find(end_key) == graph.end()){throw std::runtime_error("\n There is no such a node: " \
            + to_string(end_key)  + ", change key_to parameter." );}
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

//    for every node
    node_name_t processed_key;
    for (size_t i = 0; i < clone.size(); ++i) {
//        sorting each time will give us the smallest number
        non_vis.sort([](const std::pair<node_name_t, weight_t>& x, const std::pair<node_name_t, weight_t>& y) {
            return (x.second) < (y.second);
        });
//  delete from non_vis list
        processed_key = non_vis.front().first;
        non_vis.pop_front();

        // if that node wasn't neighbour before it won't be in future
        if( is_equal( clone[processed_key].first, inf) ){continue;}

// for each nebear node recalculate smallest way to
        for (auto&[key_node_to, w_edge]: clone.get_con_nodes(processed_key)) {

            if (is_not_in(non_vis, key_node_to) ) { continue; }//if was visited

            if (clone[key_node_to].first > clone[processed_key].first + w_edge) { // if closer way was found

                //  rewrite new distance to non_vis list
                non_vis.remove({key_node_to,clone[key_node_to].first});
                non_vis.push_front({key_node_to,clone[processed_key].first + w_edge});

                //  rewrite new distance and root to node
                clone[key_node_to].first = clone[processed_key].first + w_edge;
                clone[key_node_to].second =  clone[processed_key].second;
                (clone[key_node_to].second).push_back(key_node_to);
            }

        }

    }

    std::vector<std::pair<weight_t, route_t> > answer;
    for (auto& key_to: end_vec) {
        if ( is_equal( clone[key_to].first, inf) ){
    //        throw std::runtime_error("\n There is no way between: " + to_string(key_from)  + " and "  + to_string(key_to));
            std::cout << "\nThere is no way between: " + to_string(key_from)  + " and "  + to_string(key_to) << ". Be careful!"<<std::endl;
            answer.push_back( {-1,{key_to}});
        }
        else answer.push_back(clone[key_to]);
    }

    return answer;
}


// finds the shortest way from  key_from to every key in the graph
// if there is a way adds a pair of resulting weight and vector with rout of node names to answer
// if there is no way adds a pair of -1 weight and vector with key_to to answer
// return answer - vector with all pairs
std::vector<std::pair<weight_t, route_t> >
dijkstra(const graph_t &graph, const node_name_t &key_from) {
    for (auto&[node_key, node]: graph) {
        for (auto&[edge_key, edge]: node) {
            if (edge < 0)
                throw std::runtime_error("\nNegative wight of edge: " + to_string(edge) + \
            " Between \"" + to_string(node_key) + "\" and \"" + to_string(edge_key) + "\" nodes.\nDijkstra algorithm" \
 + " can't be applied.");
        }
    }
    if (graph.find(key_from) == graph.end()){throw std::runtime_error("\n There is no such a node: " \
    + to_string(key_from)  + ", change key_from parameter." );}



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

//    for every node
    node_name_t processed_key;
    for (size_t i = 0; i < clone.size(); ++i) {
//        sorting each time will give us the smallest number
        non_vis.sort([](const std::pair<node_name_t, weight_t>& x, const std::pair<node_name_t, weight_t>& y) {
            return (x.second) < (y.second);
        });
//  delete from non_vis list
        processed_key = non_vis.front().first;
        non_vis.pop_front();

        // if that node wasn't neighbour before it won't be in future
        if( is_equal( clone[processed_key].first, inf) ){continue;}

// for each nebear node recalculate smallest way to
        for (auto&[key_node_to, w_edge]: clone.get_con_nodes(processed_key)) {

            if (is_not_in(non_vis, key_node_to) ) { continue; }//if was visited

            if (clone[key_node_to].first > clone[processed_key].first + w_edge) { // if closer way was found

                //  rewrite new distance to non_vis list
                non_vis.remove({key_node_to,clone[key_node_to].first});
                non_vis.push_front({key_node_to,clone[processed_key].first + w_edge});

                //  rewrite new distance and root to node
                clone[key_node_to].first = clone[processed_key].first + w_edge;
                clone[key_node_to].second =  clone[processed_key].second;
                (clone[key_node_to].second).push_back(key_node_to);
            }

        }

    }

    std::vector<std::pair<weight_t, route_t> > answer;
    for (auto& [key,node]: clone) {
        if ( is_equal( clone[key].first, inf) ){
            //        throw std::runtime_error("\n There is no way between: " + to_string(key_from)  + " and "  + to_string(key_to));
            std::cout << "\nThere is no way between: " + to_string(key_from)  + " and "  + to_string(key) << ". Be careful!"<<std::endl;
            answer.push_back( {-1,{key}});
        }
        else answer.push_back(clone[key]);
    }

    return answer;
}


#endif //GRAPH_ALGORITHM_GRAPH_ALGORITMS_HPP
