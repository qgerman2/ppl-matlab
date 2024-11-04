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

    double M[] = {
        1, 0, 0, 0, 1, 0, 0, 0, 0
    };

    C_Polyhedron R;
    ppl_matlab::AffineMap(&R, &P, M, 3);

    std::cout << "\n";
    R.constraints().print();
}