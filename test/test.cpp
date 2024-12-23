#include <iostream>
#include <format>
#include "ppl_matlab.hpp"

using namespace Parma_Polyhedra_Library;
using namespace ppl_matlab;

int main() {
    C_Polyhedron P;
    double P_A[] = {
      1,  0, -1, 0,
      0, 1, 0, -1
    };
    double P_b[] = {
        1, 1, 1, 1
    };
    ppl_matlab::Polyhedron_HRep(&P, P_A, P_b, NULL, NULL, 4, 0, 2);

    std::cout << "\n";
    P.constraints().print();
}