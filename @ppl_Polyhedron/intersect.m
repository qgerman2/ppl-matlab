function R = intersect(P, S)
    coder.cinclude("ppl_matlab.hpp");
    R = ppl_Polyhedron();
    coder.ceval("ppl_matlab::Intersect", ...
        coder.wref(R.instance), coder.ref(P.instance), coder.ref(S.instance));
    R.update_representation();
end