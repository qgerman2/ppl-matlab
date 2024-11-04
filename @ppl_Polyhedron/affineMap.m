function R = affineMap(P, M)
    coder.cinclude("ppl_matlab.hpp");
    R = ppl_Polyhedron();
    coder.ceval("ppl_matlab::AffineMap", ...
        coder.wref(R.instance), coder.ref(P.instance), coder.ref(M), size(M, 1));
    R.update_representation();
end