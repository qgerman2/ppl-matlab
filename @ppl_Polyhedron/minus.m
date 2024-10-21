function R = minus(P, S)
    coder.cinclude("ppl_matlab.hpp");
    R = ppl_Polyhedron();
    coder.ceval("ppl_matlab::Minus", ...
        coder.wref(R.instance), coder.ref(P.instance), coder.ref(S.instance));
    R.update_representation();
end