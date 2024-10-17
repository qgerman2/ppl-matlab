clearvars;
clf;

x = sdpvar(2, 1);
A = [-0.46 -0.03; 0.08 -1.23; -0.92 -1.9; -1.92  2.37];
b = [1.72; 3.84; 3.05; 0.03];
constraints = [ 0.2*x'*x-[2.1 0.8]*x<=2; A*x<=b ];
S = YSet(x, constraints);

S.plot

x2 = [15; 0];

res = S.project(x2)
res2 = S.distance(x2)