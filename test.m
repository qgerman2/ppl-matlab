clearvars;

P = Polyhedron([eye(2); -eye(2)], [1;1;1;1]);

R = P.affineMap([1, 0; 1, 1; 0, 0; 0, 0])
R.H
R.Dim