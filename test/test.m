clc;
clearvars;

A = [eye(2);-eye(2)];
b = [5; 5; 5; 5];

P = Polyhedron('A', A, 'b', b);
P.plot