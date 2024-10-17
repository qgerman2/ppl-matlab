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

    template <typename FP_Format, typename Interval_Info>
    void
        convert_to_integer_expression(
            const Linear_Form<Interval <FP_Format, Interval_Info> > &lf,
            const dimension_type lf_dimension,
            Linear_Expression &result) {
        result = Linear_Expression();

        typedef Interval<FP_Format, Interval_Info> FP_Interval_Type;
        std::vector<Coefficient> numerators(lf_dimension + 1);
        std::vector<Coefficient> denominators(lf_dimension + 1);

        // Convert each floating point number to a pair <numerator, denominator>
        // and compute the lcm of all denominators.
        PPL_DIRTY_TEMP_COEFFICIENT(lcm);
        lcm = 1;
        const FP_Interval_Type &b = lf.inhomogeneous_term();
        // FIXME: are these checks numerator[i] != 0 really necessary?
        numer_denom(b.lower(), numerators[lf_dimension],
            denominators[lf_dimension]);
        if (numerators[lf_dimension] != 0) {
            lcm_assign(lcm, lcm, denominators[lf_dimension]);
        }

        for (dimension_type i = 0; i < lf_dimension; ++i) {
            const FP_Interval_Type &curr_int = lf.coefficient(Variable(i));
            numer_denom(curr_int.lower(), numerators[i], denominators[i]);
            if (numerators[i] != 0) {
                lcm_assign(lcm, lcm, denominators[i]);
            }
        }

        for (dimension_type i = 0; i < lf_dimension; ++i) {
            if (numerators[i] != 0) {
                exact_div_assign(denominators[i], lcm, denominators[i]);
                numerators[i] *= denominators[i];
                result += numerators[i] * Variable(i);
            }
        }

        if (numerators[lf_dimension] != 0) {
            exact_div_assign(denominators[lf_dimension],
                lcm, denominators[lf_dimension]);
            numerators[lf_dimension] *= denominators[lf_dimension];
            result += numerators[lf_dimension];
        }
    }

    void Polyhedron_HRep(C_Polyhedron *result,
        double *A, size_t inequalities, size_t dimension,
        double *b);
    void Polyhedron_VRep(C_Polyhedron *result,
        double *V, double *R, size_t dimension, size_t vertices, size_t rays
    );
    inline bool Contains(C_Polyhedron *A, C_Polyhedron *B) { return A->contains(*B); };
    void Minus(C_Polyhedron *result, C_Polyhedron *P, C_Polyhedron *S);
    void AffineMap(C_Polyhedron *result, C_Polyhedron *P, double *M);
    void Size(C_Polyhedron *P, double *inequalities, double *equalities, double *dimension, double *vertices, double *rays);
    void ConvexHull(C_Polyhedron *R, C_Polyhedron *P, C_Polyhedron *S);
    inline bool Empty(C_Polyhedron *P) { return P->is_empty(); };
    void A(C_Polyhedron *P, double *dest);
    void b(C_Polyhedron *P, double *dest);
    void V(C_Polyhedron *P, double *dest, size_t vertices);
    void R(C_Polyhedron *P, double *dest, size_t rays);
    void Ae(C_Polyhedron *P, double *dest);
    void be(C_Polyhedron *P, double *dest);
}
