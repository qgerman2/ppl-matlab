function R = affineMap(P, M)
    R = ppl_Polyhedron.from_VRep(P.V*M', P.R*M');
end