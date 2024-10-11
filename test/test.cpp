#include <iostream>
#include <format>
#include "ppl_matlab.hpp"

using namespace Parma_Polyhedra_Library;

int main() {
    C_Polyhedron P;
    double P_A[] = {
      1,  0, -1, 0,
      0, 1, 0, -1
    };
    double P_b[] = {
        4.5, 5, 5, 5
    };
    ppl_matlab::Polyhedron(&P, P_A, 4, 2, P_b);


    const Generator_System &gs = P.minimized_generators();
    for (Generator_System::const_iterator i = gs.begin(); i != gs.end(); i++) {
        const Generator &g = *i;
        if (g.is_point()) {
            std::cout << std::format("x: {} y: {} e:{}\n", g.coefficient(Variable(0)).get_d(), g.coefficient(Variable(1)).get_d(), g.divisor().get_d());
        }
    }
}