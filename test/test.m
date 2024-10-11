clc;
clearvars;

A1 = [2*eye(2); -2*eye(2)];
b1 = [5; 5; 5; 5];

A = Polyhedron(A1, b1);

A2 = [3*eye(2); -5*eye(2)];
b2 = [2; 2; 2; 2];

B = Polyhedron(A2, b2);

A.minus(B).H