% Check if point x0 is inside polyhedron P
function inside = isInside(P, x0)
    assert(isvector(x0));
    if (size(x0,1)==1)   % if it is row vector
        x = ppl_Polyhedron.from_VRep(x0, []);
    else                 % column vector gets transposed to row vector
        x = ppl_Polyhedron.from_VRep(x0', []);
    end
    inside = P.contains(x);
end