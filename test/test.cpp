#include <iostream>
#include <format>
#include "ppl_matlab.hpp"

using namespace Parma_Polyhedra_Library;

int main() {
    C_Polyhedron P;
    double P_A[] = {
      1,  0,
      0, 1,
    };
    double P_b[] = {
       1.2, 1.3,
    };
    ppl_matlab::Polyhedron(&P, P_A, 2, 2, P_b);


    const Generator_System &gs = P.minimized_generators();
    for (Generator_System::const_iterator i = gs.begin(); i != gs.end(); i++) {
        const Generator &g = *i;
        if (g.is_point()) {
            std::cout << std::format("p x: {} y: {} e:{}\n", g.coefficient(Variable(0)).get_d(), g.coefficient(Variable(1)).get_d(), g.divisor().get_d());
        }
        if (g.is_ray()) {
            std::cout << std::format("ray x: {} y: {}\n", g.coefficient(Variable(0)).get_d(), g.coefficient(Variable(1)).get_d());
        }
    }
}