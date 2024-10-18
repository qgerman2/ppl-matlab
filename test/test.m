clearvars;

P = Polyhedron([eye(2); -eye(2)], [5;4;3;2]);
S = Polyhedron("V", [10,10]);

A = blkdiag(P.A, S.A);
b = [P.b; S.b];

Ae = blkdiag(P.Ae, S.Ae);
be = [P.be; S.be];


fun = @(x) norm(x(1:P.Dim) - x(P.Dim+1:P.Dim*2));

[res, fval] = fmincon(fun, [0, 0, 0, 0], A, b, Ae, be);

plot(P)
hold on
plot(10,10,'Marker', 'o')
plot(res(1), res(2), 'Marker', 'x');
