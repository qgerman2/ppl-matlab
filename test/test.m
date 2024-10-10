clc;
clearvars;

A1 = [eye(2); -eye(2)];
b1 = [5; 5; 5; 5];

A = Polyhedron(A1, b1);

A2 = [eye(2); -eye(2)];
b2 = [1; 1; 1; 1];

B = Polyhedron(A2, b2);

A.minus(B).H