clearvars;

P = Polyhedron([eye(2); -eye(2)], [5;4;3;2]);

res = P.projection(1);

P.V
res.V