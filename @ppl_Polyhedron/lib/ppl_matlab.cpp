#include "ppl_matlab.hpp"

using namespace Parma_Polyhedra_Library;

namespace ppl_matlab {
    void Polyhedron_HRep(C_Polyhedron *result,
        double *A, double *b, double *Ae, double *be,
        size_t inequalities, size_t equalities, size_t dimension) {

        C_Polyhedron new_poly(dimension);

        // set inequality constraints
        for (size_t row = 0; row < inequalities; row++) {
            FP_Linear_Form left;
            for (size_t col = 0; col < dimension; col++) {
                left += FP_Linear_Form(Variable(col)) * FP_Interval(A[inequalities * col + row]);
            }
            FP_Linear_Form right(FP_Interval(b[row]));
            new_poly.refine_with_linear_form_inequality(left, right);
        }

        // set equality constraints
        for (size_t row = 0; row < equalities; row++) {
            FP_Linear_Form left;
            for (size_t col = 0; col < dimension; col++) {
                left += FP_Linear_Form(Variable(col)) * FP_Interval(Ae[equalities * col + row]);
            }
            FP_Linear_Form right(FP_Interval(be[row]));
            new_poly.generalized_refine_with_linear_form_inequality(left, right, Relation_Symbol::EQUAL);
        }

        result->m_swap(new_poly);
    }

    void Polyhedron_VRep(C_Polyhedron *result,
        double *V, double *R,
        size_t dimension, size_t vertices, size_t rays) {
        Generator_System gs;
        // construct vertices
        for (size_t row = 0; row < vertices; row++) {
            // construct linear form from matrix
            FP_Linear_Form lf;
            for (size_t col = 0; col < dimension; col++) {
                lf += FP_Linear_Form(Variable(col)) * FP_Interval(V[vertices * col + row]);
            }
            // add constant to track lcm
            lf += FP_Interval(1);
            // convert linear form to linear expression
            Linear_Expression le;
            convert_to_integer_expression(lf, lf.space_dimension(), le);
            // extract constant
            Coefficient div = le.inhomogeneous_term();
            le.set_inhomogeneous_term(0);
            // create vertex
            gs.insert(Generator::point(le, div));
        }
        // construct rays
        for (size_t row = 0; row < rays; row++) {
            // construct linear form from matrix
            FP_Linear_Form lf;
            for (size_t col = 0; col < dimension; col++) {
                lf += FP_Linear_Form(Variable(col)) * FP_Interval(R[rays * col + row]);
            }
            // convert linear form to linear expression
            Linear_Expression le;
            convert_to_integer_expression(lf, lf.space_dimension(), le);
            // create vertex
            gs.insert(Generator::ray(le));
        }

        C_Polyhedron new_poly(gs);
        result->m_swap(new_poly);
    }

    void Polyhedron_Copy(C_Polyhedron *result, C_Polyhedron *source) {
        C_Polyhedron new_poly(*source);
        result->m_swap(new_poly);
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

    void Size(C_Polyhedron *P, double *inequalities, double *equalities, double *dimension, double *vertices, double *rays) {
        const Constraint_System &cs = P->minimized_constraints();
        const Generator_System &gs = P->minimized_generators();
        double ineq_count = 0;
        double eq_count = 0;
        double v_count = 0;
        double r_count = 0;
        for (Constraint_System::const_iterator i = cs.begin(); i != cs.end(); i++) {
            const Constraint &c = *i;
            if (c.is_inequality()) {
                ineq_count++;
            } else {
                eq_count++;
            }
        };
        for (Generator_System::const_iterator i = gs.begin(); i != gs.end(); i++) {
            const Generator &g = *i;
            if (g.is_point()) { v_count++; }
            if (g.is_ray()) { r_count++; }
        };
        *inequalities = ineq_count;
        *equalities = eq_count;
        *dimension = P->space_dimension();
        *vertices = v_count;
        *rays = r_count;
    }

    void ConvexHull(C_Polyhedron *R, C_Polyhedron *P, C_Polyhedron *S) {
        C_Polyhedron new_poly(*P);
        new_poly.poly_hull_assign(*S);
        R->m_swap(new_poly);
    }

    void Intersect(C_Polyhedron *R, C_Polyhedron *P, C_Polyhedron *S) {
        C_Polyhedron new_poly(*P);
        new_poly.intersection_assign(*S);
        R->m_swap(new_poly);
    }

    void A(C_Polyhedron *P, double *dest) {
        size_t i = 0;
        const Constraint_System &P_cs = P->minimized_constraints();
        for (size_t col = 0; col < P->space_dimension(); col++) {
            for (Constraint_System::const_iterator c = P_cs.begin(); c != P_cs.end(); c++) {
                if (c->is_inequality()) {
                    dest[i] = -c->coefficient(Variable(col)).get_d();
                    i++;
                }
            }
        }
    }

    void b(C_Polyhedron *P, double *dest) {
        size_t i = 0;
        const Constraint_System &P_cs = P->minimized_constraints();
        for (Constraint_System::const_iterator c = P_cs.begin(); c != P_cs.end(); c++) {
            if (c->is_inequality()) {
                dest[i] = c->inhomogeneous_term().get_d();
                i++;
            }
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

    void Ae(C_Polyhedron *P, double *dest) {
        size_t i = 0;
        const Constraint_System &P_cs = P->minimized_constraints();
        for (size_t col = 0; col < P->space_dimension(); col++) {
            for (Constraint_System::const_iterator c = P_cs.begin(); c != P_cs.end(); c++) {
                if (!c->is_inequality()) {
                    dest[i] = -c->coefficient(Variable(col)).get_d();
                    i++;
                }
            }
        }
    }

    void be(C_Polyhedron *P, double *dest) {
        size_t i = 0;
        const Constraint_System &P_cs = P->minimized_constraints();
        for (Constraint_System::const_iterator c = P_cs.begin(); c != P_cs.end(); c++) {
            if (!c->is_inequality()) {
                dest[i] = c->inhomogeneous_term().get_d();
                i++;
            }
        }
    }

};

