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
        4.5, 5, 5, 5
    };
    ppl_matlab::Polyhedron_HRep(&P, P_A, 4, 2, P_b);


    const Generator_System &gs = P.minimized_generators();
    for (Generator_System::const_iterator i = gs.begin(); i != gs.end(); i++) {
        const Generator &g = *i;
        if (g.is_point()) {
            //std::cout << std::format("x: {} y: {} e:{}\n", g.coefficient(Variable(0)).get_d(), g.coefficient(Variable(1)).get_d(), g.divisor().get_d());
        }
    }

    double P_V[] = {
        0, 0, 1.5, 2.5,
        0, 1, 4, 3
    };
    double P_R[] = {
        1, 1.5
    };

    C_Polyhedron HH;
    Polyhedron_VRep(&HH, P_V, P_R, 2, 4, 1);
    HH.minimized_generators().print();
}