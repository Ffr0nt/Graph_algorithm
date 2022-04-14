#include <iostream>
#include <graph.h>
#include <Matrix.h>
#include "Graph_Algoritms.h"

int main() {
    Matrix<double> mat = {{1.2,2.4,3.5},{1.2,2.4,3.5},{1.2,2.4,3.5}};
    std::cout << mat;
    BinaryMode<double> BM;
    BM.write("/Users/fedor/CLionProjects/Graph_algorithm/matrix_for_input_1", mat);
    auto new_mat = BM.read("/Users/fedor/CLionProjects/Graph_algorithm/matrix_for_input_1");
    std::cout << new_mat;
    return 0;
}
