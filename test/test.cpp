#include <iostream>
#include "ppl_matlab.hpp"

using namespace Parma_Polyhedra_Library;

int main() {
    C_Polyhedron P;
    double P_A[] = {
      1,  0, -1, 0,
      0, 1, 0, -1
    };
    double P_b[] = {
        5, 5, 5, 5
    };
    ppl_matlab::Polyhedron(&P, P_A, 4, 2, P_b);

    // ppl_matlab::FP_Linear_Form eq = Variable(0) * 2 + Variable(1) * 2;
    // P.affine_form_image(Variable(0), eq);

    P.constraints().print();
}