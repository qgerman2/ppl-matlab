function res = project(P, x0)
    assert(isvector(x0));
    if (size(x0,1)==1)   % if it is row vector
        S = ppl_Polyhedron.from_VRep(x0, []);
    else                 % column vector gets transposed to row vector
        S = ppl_Polyhedron.from_VRep(x0', []);
    end
    res = P.distance(S);
end