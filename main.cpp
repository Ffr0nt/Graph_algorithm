#include <iostream>
#include <graph.h>
#include <Matrix.h>
#include "Graph_Algoritms.h"

// +
// graph( matrix )
// dijkstra() - now const
// dijkstra() - can save your values of nodes
// optimization if there are only inf.-far points left
// dijkstra() for vector
// dijkstra() for all keys
// tests
// shell



const char * path_4 = "/Users/fedor/CLionProjects/Graph_algorithm/matrix_for_input_4"; // nice big matrix
const char * path_2 = "/Users/fedor/CLionProjects/Graph_algorithm/matrix_for_input_2"; // 3x4 matrix
const char * path_1 = "/Users/fedor/CLionProjects/Graph_algorithm/matrix_for_input_1"; // for tests of writing and reading

// appropriate running
void new_test_1(){

    auto gr = read_graph(path_4);
    print(gr);

    std::cout<< std::endl <<"--------------------|dijkstra(gr,1,4);|--------------------"<< std::endl;

    auto [w, r] = dijkstra(gr,1,4);
    std::cout << endl << "distance: "<< w << std::endl << "Root: ";
    for (auto it : r) std::cout  << (it) << " ";

    std::cout<< std::endl <<"---------------------|dijkstra(gr,1,{0,2,4});|-------------------"<< std::endl;

    auto answ = dijkstra(gr,1,{0,2,4});
    for (auto it : answ){
        std::cout << std::endl<< "distance: "<< it.first<< std::endl << "Root: ";
        for (auto it_2 : it.second) std::cout  << (it_2) << " ";
        std::cout << std::endl;
    }
    std::cout<< std::endl <<"---------------------|dijkstra(gr,0);|-------------------"<< std::endl;

    auto answ_1 = dijkstra(gr, 0);
    for (auto it : answ_1){
        std::cout << std::endl<< "distance: "<< it.first<< std::endl << "Root: ";
        for (auto it_2 : it.second) std::cout  << (it_2) << " ";
        std::cout << std::endl;
    }

}

// errors
void new_test_2(){
    try {
        read_graph<int, int, double>("/Users/fedor/CLionProjects/Graph_algorithm/matrix_for_input_333");
    }
    catch (std::runtime_error er) { std::cout << er.what(); }

    cout << endl;

    try {
        read_graph<int, int, double>("/Users/fedor/CLionProjects/Graph_algorithm/matrix_for_input_2");
    }
    catch (std::runtime_error er) { std::cout << er.what(); }

    cout << endl;

    Graph<int, double, double> g;
    g.insert_node(1, 1);
    g.insert_node(2, 2);
    g.insert_edge({1, 2}, -1);
    try { dijkstra(g, 1, 2); }
    catch (std::runtime_error er) { std::cout << er.what(); }

    auto gr = read_graph("/Users/fedor/CLionProjects/Graph_algorithm/matrix_for_input_4");

    cout << endl;
    try { dijkstra(gr, 1, 999); }
    catch (std::runtime_error er) { std::cout << er.what(); }

    cout << endl;
    try { dijkstra(gr, 999, 1); }
    catch (std::runtime_error er) { std::cout << er.what(); }

    cout << endl;

}

//  writing and reading tests for matrix
void new_test_3(){
    Matrix<double> mat = {{0.0, 2.4, 3.5},
                          {1.2, 0.0, 3.5},
                          {1.2, 2.4, 0.0}};
    std::cout<<"Matrix:"<< std::endl << mat;
    Graph<int,int,double> gr_0 = mat;

    std::cout<<"Graph constructed with Matrix:"<< std::endl;
    print(gr_0);

    std::cout<<"Let's write down Matrix in a"<< std::endl << "input_1 file, then read it in graph"<< std::endl;
    BinaryMode<double> BM;
    BM.write(path_1, mat);
    auto new_mat = BM.read(path_1);
    std::cout<< std::endl << new_mat;
    Graph<int,int,double> gr_1 = read_graph<int, int, double>(path_1);
    print(gr_1);

}


void test_switch(size_t num){
    switch (num) {
        case (1):
            new_test_1();
            break;
        case (2):
            new_test_2();
            break;
        case (3):
            new_test_3();
            break;
//        case (4):
//           new_test_4();
//            break;
        default:
            throw std::runtime_error("Invalid number of test");
    }
}

vector< int> get_noes_to(const char * t){
    string text = t;
    string temp;
    int postion = 0;
    vector< int> answ;
    while (text.find(",") != string::npos){
        temp = text[postion, text.find(",")-1];
        postion = text.find(",");
        text.erase(0, postion+1);
        answ.push_back(atoi(temp.c_str()));
    }
    answ.push_back(atoi(text.c_str()));
    return answ;
};

int main(int arg_count, char* arg_vars[]) {

    string st;
    stringstream oss;
    switch (arg_count)
    {
//        case (2):
//            oss << arg_vars[1];
//            if (oss.str() == "-help"){
//                std::cout << "Graph_algorithm ";
//            }
            break;
        case (3):
            oss << arg_vars[1];
            if (oss.str() == "-test")
            {
                oss.str("");
                oss << arg_vars[2];
                if ( atoi( oss.str().c_str() ) > 0 ){
                    test_switch(atoi( oss.str().c_str() ));
                }
            }
            break;

        case (5):
            if ( strcmp (arg_vars[1], "-file") == 0 ) {
                const char *path_to_file = arg_vars[2];

                if ( strcmp(arg_vars[3] , "-from") == 0 ) {
                    int node_from = atoi(arg_vars[4]);

                    if (node_from > 0) {
                        auto answ = dijkstra(read_graph(path_to_file),node_from);
                        for (auto it : answ){
                            std::cout << std::endl<< "distance: "<< it.first<< std::endl << "Root: ";
                            for (auto it_2 : it.second) std::cout  << (it_2) << " ";
                            std::cout << std::endl;
                        }
                    }
                }
            }
            break;

        case (7):

            if ( strcmp(arg_vars[1] ,"-file") ==0) {

                const char * path_to_file = arg_vars[2];

                if (strcmp(arg_vars[3],"-from") ==0) {
                    int node_from = atoi(arg_vars[4]);

                    if (strcmp(arg_vars[5], "-to") == 0) {

                         vector<int> nodes_to = get_noes_to( arg_vars[6] );

                        auto answ = dijkstra(read_graph(path_to_file),node_from,nodes_to);
                        for (auto it : answ){
                            std::cout << std::endl<< "distance: "<< it.first<< std::endl << "Root: ";
                            for (auto it_2 : it.second) std::cout  << (it_2) << " ";
                            std::cout << std::endl;
                        }
                    }
                }

                if (strcmp(arg_vars[3],"-to")==0) {
                    vector<int> nodes_to = get_noes_to( arg_vars[4] );
                    if (strcmp(arg_vars[5], "-from") == 0) {
                        int node_from = atoi(arg_vars[6]);

                        auto answ = dijkstra(read_graph(path_to_file),node_from,nodes_to);
                        for (auto it : answ){
                            std::cout << std::endl<< "distance: "<< it.first<< std::endl << "Root: ";
                            for (auto it_2 : it.second) std::cout  << (it_2) << " ";
                            std::cout << std::endl;
                        }
                    }
                }
            }
            break;

        default:

            throw std::runtime_error("Invalid arguments");
    }

    cout <<endl<< "Enter whatever to continue:";
    int a;
    cin >> a;
    return 0;
}
