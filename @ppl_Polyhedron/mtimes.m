function R = mtimes(alpha, P)
    R = ppl_Polyhedron.from_VRep(alpha*P.V, P.R);
end