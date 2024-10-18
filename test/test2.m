clearvars;

P = Polyhedron([eye(2); -eye(2)], [5;4;3;2]);
S = Polyhedron("V", [10,10]);

res = P.distance(S)
