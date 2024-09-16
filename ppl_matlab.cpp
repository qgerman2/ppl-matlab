#include "ppl_matlab.hpp"

using namespace Parma_Polyhedra_Library;

namespace ppl_matlab {
    void Polyhedron(C_Polyhedron *result,
        double *A, unsigned long A_rows, unsigned long A_cols,
        double *b, unsigned long b_length) {

        C_Polyhedron new_poly(b_length);

        // set constraints
        for (unsigned long row = 0; row < b_length; row++) {
            FP_Linear_Form left;
            for (unsigned long col = 0; col < A_cols; col++) {
                left += FP_Linear_Form(Variable(col)) * FP_Interval(A[A_rows * col + row]);
            }
            FP_Linear_Form right(FP_Interval(b[row]));
            new_poly.refine_with_linear_form_inequality(left, right);
        }

        result->m_swap(new_poly);
    }

    bool Contains(C_Polyhedron *A, C_Polyhedron *B) {
        return A->contains(*B);
    }

    void Minus(C_Polyhedron *result, C_Polyhedron *P, C_Polyhedron *S) {
        const Constraint_System &P_cs = P->constraints();
        Constraint_System R_cs(P_cs);
        for (Constraint_System::const_iterator i = P_cs.begin(); i != P_cs.end(); ++i) {
            const Constraint &c = *i;
            Linear_Expression exp;
            for (size_t i = 0; i < P->space_dimension(); i++) {
                exp += Variable(i) * c.coefficient(Variable(i));
            }
            Coefficient num;
            Coefficient den;
            bool included;

            bool ok = S->maximize(exp, num, den, included);
            if (ok) {
                Linear_Expression exp(c.expression());
                exp -= num / den;
                R_cs.insert(exp <= 0);
            }
        }

        C_Polyhedron new_poly(R_cs);
        result->m_swap(new_poly);
    }
}


