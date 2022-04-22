#include <iostream>
#include <graph.h>
#include <Matrix.h>
#include "Graph_Algoritms.h"
// dijkstra() - now const
// dijkstra() - can save your values of nodes
// optimization if there are only inf.-far points left



//template<typename Graph>
//void print(const Graph& graph) {
//    if (graph.empty()) {
//        std::cout << "> This graph is empty!" << std::endl;
//        return;
//    }
//    std::cout << "> Size of graph: " << graph.size() << std::endl;
//    for (const auto& [key, node] : graph) {
//        std::cout << '[' << key << "] stores: " << node.value()
//                  << " and matches with:" << std::endl;
//        for (const auto& [key, weight] : node)
//            std::cout << "\t[" << key << "]\t with weight: "
//                      << weight << std::endl;
//    }
//}
const char * path_1 = "/Users/fedor/CLionProjects/Graph_algorithm/matrix_for_input_1";
const char * path_2 = "/Users/fedor/CLionProjects/Graph_algorithm/matrix_for_input_2";

void new_test_1(){
    Matrix<double> mat = {{0.0, 2.4, 3.5, 5.0},
                          {1.2, 0.0, 3.5, 6.8},
                          {1.2, 2.4, 0.0, 7.4}};
    std::cout<< std::endl << mat;
    Graph<int,int,double> gr_0 = mat;
    print(gr_0);
    BinaryMode<double> BM;
    BM.write(path_2, mat);
    auto new_mat = BM.read(path_2);
    std::cout<< std::endl << new_mat;
    Graph<int,int,double> gr_1 = read_graph<int, int, double>(path_2);
    print(gr_1);

    read_graph<int, int, double>("/Users/fedor/CLionProjects/Graph_algorithm/matrix_for_input_333");
    return;
}

void new_test_2(){
//    Graph<int, double, double> gr;
//    gr.insert_node(1,1);
//    gr.insert_node(2,2);
//    gr.insert_edge({1,2}, -1);
//    try{dijkstra(gr, 1,2);}
//    catch (std::runtime_error er){std::cout << er.what();}

//    Graph<int, double, double> gr_1;
//    gr_1.insert_node(1,1);
//    gr_1.insert_node(2,2);
//    gr_1.insert_node(3,3);
//    gr_1.insert_node(4,4);
//    gr_1.insert_edge({1,2}, 12.6);
//    gr_1.insert_edge({2,3}, 12.6);
//    gr_1.insert_edge({3,2}, 32.6);
//    gr_1.insert_edge({1,4}, 14.6);
//    gr_1.insert_edge({4,3}, 4.6);

    Graph<int, double, double> gr_1;
    gr_1.insert_node(1,1);
    gr_1.insert_node(2,2);
    gr_1.insert_node(3,3);
    gr_1.insert_node(4,4);
    gr_1.insert_edge({1,2}, 12);
    gr_1.insert_edge({1,3}, 12);
    gr_1.insert_edge({1,4}, 14);
    gr_1.insert_edge({2,1}, 32);
    gr_1.insert_edge({2,3}, 4);
    gr_1.insert_edge({2,4}, 4);
    gr_1.insert_edge({3,1}, 32);
    gr_1.insert_edge({3,2}, 4);
    gr_1.insert_edge({3,4}, 4);
    gr_1.insert_edge({4,1}, 32);
    gr_1.insert_edge({4,3}, 4);
    gr_1.insert_edge({4,3}, 4);
//    print(gr_1);

    auto answ = dijkstra(gr_1, 1,3);
    std::cout << "distance: "<< answ.first<< std::endl << "Root: ";
    for (auto it : answ.second) std::cout  << (it) << " ";
}

void new_test_3(){

    Graph<int, double, double> gr_1;
    gr_1.insert_node(1,1);
    gr_1.insert_node(2,2);
    gr_1.insert_node(3,3);
    gr_1.insert_node(4,4);
    gr_1.insert_node(5,5);
    gr_1.insert_edge({1,2}, 12);
    gr_1.insert_edge({1,3}, 12);
    gr_1.insert_edge({1,4}, 14);
    gr_1.insert_edge({2,1}, 32);
    gr_1.insert_edge({2,3}, 4);
    gr_1.insert_edge({2,4}, 4);
    gr_1.insert_edge({3,1}, 32);
    gr_1.insert_edge({3,2}, 4);
    gr_1.insert_edge({3,4}, 4);
    gr_1.insert_edge({4,1}, 32);
    gr_1.insert_edge({4,3}, 4);
    gr_1.insert_edge({4,3}, 4);


//    auto answ = dijkstra(gr_1,2, {1,2,3,5});
//    for (auto it : answ){
//        std::cout << std::endl<< "distance: "<< it.first<< std::endl << "Root: ";
//        for (auto it_2 : it.second) std::cout  << (it_2) << " ";
//        std::cout << std::endl;
//    }

    auto an = dijkstra(gr_1,2);
    for (auto it : an){
        std::cout << std::endl<< "distance: "<< it.first<< std::endl << "Root: ";
        for (auto it_2 : it.second) std::cout  << (it_2) << " ";
        std::cout << std::endl;
    }

    auto answ = dijkstra(gr_1,2,{1,2,5});
    for (auto it : answ){
        std::cout << std::endl<< "distance: "<< it.first<< std::endl << "Root: ";
        for (auto it_2 : it.second) std::cout  << (it_2) << " ";
        std::cout << std::endl;
    }
}

int main() {
    new_test_3();
    return 0;
}
