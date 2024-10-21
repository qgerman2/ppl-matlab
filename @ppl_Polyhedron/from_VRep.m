function P = from_VRep(V, R)
    % V, R vertices and rays constructor
    coder.cinclude("ppl_matlab.hpp");
    P = ppl_Polyhedron();
    coder.ceval("ppl_matlab::Polyhedron_VRep", coder.wref(P.instance), ...
        coder.ref(V), coder.ref(R), ...
        size(V, 2), size(V, 1), size(R, 1));
    P.update_representation();
end