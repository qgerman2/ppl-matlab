function contained = contains(P, B)
    contained = 0;
    coder.cinclude("ppl_matlab.hpp");
    if isa(B, "ppl_Polyhedron")
        contained = coder.ceval("ppl_matlab::Contains", ...
            coder.ref(P.instance), coder.ref(B.instance));
    elseif iscolumn(B)
        poly = ppl_Polyhedron.from_VRep(B', []);
        coder.ceval("ppl_matlab::Contains", ...
            coder.ref(P.instance), coder.ref(poly.instance));
    end
end