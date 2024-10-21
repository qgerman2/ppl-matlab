function P = from_HRep(A, b, Ae, be)
    % A, b non strict inequality constructor
    coder.cinclude("ppl_matlab.hpp");
    P = ppl_Polyhedron();
    coder.ceval("ppl_matlab::Polyhedron_HRep", coder.wref(P.instance), ...
    coder.ref(A), coder.ref(b), coder.ref(Ae), coder.ref(be), ...
    size(A, 1), size(Ae, 1), size(A, 2));
    P.update_representation();
end