clearvars;

P = Polyhedron([eye(2); -eye(2)], [1;1;1;1]);

R = P.affineMap([1, 1.5])
R.H
R.Dim