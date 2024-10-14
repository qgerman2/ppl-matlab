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
        const Constraint_System &P_cs = P->minimized_constraints();
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

    void Size(C_Polyhedron *P, double *constraints, double *dimension, double *vertices, double *rays) {
        const Constraint_System &cs = P->minimized_constraints();
        const Generator_System &gs = P->minimized_generators();
        double cs_count = 0;
        double v_count = 0;
        double r_count = 0;
        for (Constraint_System::const_iterator i = cs.begin(); i != cs.end(); i++) {
            cs_count++;
        };
        for (Generator_System::const_iterator i = gs.begin(); i != gs.end(); i++) {
            const Generator &g = *i;
            if (g.is_point()) { v_count++; }
            if (g.is_ray()) { r_count++; }
        };
        *constraints = cs_count;
        *dimension = P->space_dimension();
        *vertices = v_count;
        *rays = r_count;
    }

    void A(C_Polyhedron *P, double *dest) {
        size_t i = 0;
        const Constraint_System &P_cs = P->minimized_constraints();
        for (size_t col = 0; col < P->space_dimension(); col++) {
            for (Constraint_System::const_iterator c = P_cs.begin(); c != P_cs.end(); c++) {
                dest[i] = -c->coefficient(Variable(col)).get_d();
                i++;
            }
        }
    }

    void b(C_Polyhedron *P, double *dest) {
        size_t i = 0;
        const Constraint_System &P_cs = P->minimized_constraints();
        for (Constraint_System::const_iterator c = P_cs.begin(); c != P_cs.end(); c++) {
            dest[i] = c->inhomogeneous_term().get_d();
            i++;
        }
    }

    void V(C_Polyhedron *P, double *dest, size_t vertices) {
        const Generator_System &gs = P->minimized_generators();
        for (size_t var = 0; var < P->space_dimension(); var++) {
            size_t vertex = 0;
            for (Generator_System::const_iterator g = gs.begin(); g != gs.end(); g++) {
                if (!g->is_point()) { continue; }
                dest[var * vertices + vertex] = g->coefficient(Variable(var)).get_d() / g->divisor().get_d();
                vertex++;
            };
        }
    }

    void R(C_Polyhedron *P, double *dest, size_t rays) {
        const Generator_System &gs = P->minimized_generators();
        for (size_t var = 0; var < P->space_dimension(); var++) {
            size_t ray = 0;
            for (Generator_System::const_iterator g = gs.begin(); g != gs.end(); g++) {
                if (!g->is_ray()) { continue; }
                dest[var * rays + ray] = g->coefficient(Variable(var)).get_d();
                ray++;
            };
        }
    }
};

