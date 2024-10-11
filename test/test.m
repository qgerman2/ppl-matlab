clc;
clearvars;

A1 = [2*eye(2); -2*eye(2)];
b1 = [1; 2; 3; 4];

A = Polyhedron(A1, b1);

A2 = [3*eye(2); -5*eye(2)];
b2 = [2; 2; 2; 2];

B = Polyhedron(A2, b2);

S = A.minus(B);

S.minHRep;S.minVRep;

S.H
S.V

