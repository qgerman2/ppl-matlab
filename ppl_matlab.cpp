#include "ppl_matlab.hpp"

using namespace Parma_Polyhedra_Library;

namespace ppl_matlab {
    void Polyhedron(C_Polyhedron *result,
        double *A, size_t A_rows, size_t A_cols,
        double *b) {

        C_Polyhedron new_poly(A_cols);

        // set constraints
        for (size_t row = 0; row < A_rows; row++) {
            FP_Linear_Form left;
            for (size_t col = 0; col < A_cols; col++) {
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
                exp += Variable(i) * -c.coefficient(Variable(i));
            }
            Coefficient num;
            Coefficient den;
            bool included;

            bool ok = S->maximize(exp, num, den, included);
            if (ok) {
                Linear_Expression exp(c.expression());
                R_cs.insert(exp * den >= num);
            }
        }

        C_Polyhedron new_poly(R_cs);
        result->m_swap(new_poly);
    }

    void AffineMap(C_Polyhedron *result, C_Polyhedron *P, double *M) {
        C_Polyhedron new_poly(*P);
        size_t dim = P->space_dimension();
        for (size_t row = 0; row < dim; row++) {
            FP_Linear_Form eq;
            for (size_t col = 0; col < dim; col++) {
                eq += FP_Linear_Form(Variable(col)) * FP_Interval(M[dim * col + row]);
            }
            new_poly.affine_form_image(Variable(row), eq);
        }
        result->m_swap(new_poly);
    }

    void Size(C_Polyhedron *P, double *constraints, double *dimension) {
        const Constraint_System &P_cs = P->constraints();
        double count = 0;
        for (Constraint_System::const_iterator i = P_cs.begin(); i != P_cs.end(); i++) {
            count++;
        }
        *constraints = count;
        *dimension = P->space_dimension();
    };

    void A(C_Polyhedron *P, double *dest) {
        size_t i = 0;
        const Constraint_System &P_cs = P->constraints();
        for (size_t col = 0; col < P->space_dimension(); col++) {
            for (Constraint_System::const_iterator c = P_cs.begin(); c != P_cs.end(); c++) {
                dest[i] = -c->coefficient(Variable(col)).get_d();
                i++;
            }
        }
    }

    void b(C_Polyhedron *P, double *dest) {
        size_t i = 0;
        const Constraint_System &P_cs = P->constraints();
        for (Constraint_System::const_iterator c = P_cs.begin(); c != P_cs.end(); c++) {
            dest[i] = c->inhomogeneous_term().get_d();
            i++;
        }
    }
}


