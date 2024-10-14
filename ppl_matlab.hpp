#include "lib/ppl.hh"

namespace ppl_matlab {
    using namespace Parma_Polyhedra_Library;
    struct Floating_Real_Open_Interval_Info_Policy {
        const_bool_nodef(store_special, false);
        const_bool_nodef(store_open, true);
        const_bool_nodef(cache_empty, true);
        const_bool_nodef(cache_singleton, true);
        const_bool_nodef(cache_normalized, false);
        const_int_nodef(next_bit, 0);
        const_bool_nodef(may_be_empty, true);
        const_bool_nodef(may_contain_infinity, false);
        const_bool_nodef(check_empty_result, false);
        const_bool_nodef(check_inexact, false);
    };
    typedef Interval_Info_Bitset<unsigned int,
        Floating_Real_Open_Interval_Info_Policy> Floating_Real_Open_Interval_Info;

    typedef Interval<double,
        Floating_Real_Open_Interval_Info> FP_Interval;
    typedef Linear_Form<FP_Interval> FP_Linear_Form;

    void Polyhedron(C_Polyhedron *result,
        double *A, size_t A_rows, size_t A_cols,
        double *b);
    bool Contains(C_Polyhedron *A, C_Polyhedron *B);
    void Minus(C_Polyhedron *result, C_Polyhedron *P, C_Polyhedron *S);
    void AffineMap(C_Polyhedron *result, C_Polyhedron *P, double *M);
    void Size(C_Polyhedron *P, double *constraints, double *dimension, double *vertices, double *rays);
    void A(C_Polyhedron *P, double *dest);
    void b(C_Polyhedron *P, double *dest);
    void V(C_Polyhedron *P, double *dest, size_t vertices);
    void R(C_Polyhedron *P, double *dest, size_t rays);
}
