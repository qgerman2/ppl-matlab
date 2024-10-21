function R = projection(P, dims)
    R = ppl_Polyhedron.from_VRep(P.V(:, dims), P.R(:, dims));
end