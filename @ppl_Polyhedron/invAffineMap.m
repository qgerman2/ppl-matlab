function R = invAffineMap(P, T, t)
    R = ppl_Polyhedron.from_HRep( ...
        P.A*T, P.b-P.A*t, ... % inequalities
		P.Ae*T, P.be - P.Ae*t); % equalities
end