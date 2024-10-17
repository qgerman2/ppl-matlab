clc;
clearvars;
clf;

V = [0, 0];
R = [1, 1];

A = Polyhedron('V', V, 'R', R);

A.plot

%%
clc;
clearvars;
clf;

A = eye(2);
b = [1; 1];

P = Polyhedron(A, b)
P.V
P.R

xlim([-3,3]);
ylim([-3,3]);

%% 
clc;
clearvars;

nargin = 4;

a = {'A', 1, 'V', 4};

for i = 1:nargin
    if class(a{i}) ~= "char" 
        continue;
    end
    if ismember(a{i}, {'A', 'b', 'V', 'H'})
        a{i}
    end
end

%%
clearvars;

P(1) = Polyhedron('V', [0, 0; -1, -1; 0, -1; -1, 0]);

P(2) = Polyhedron('V', [0, 0; 1, 1; 0, 1; 1, 0]);

P = PolyUnion(P)

%%
clearvars;

H = [1,     0,     1;
    -3,     1,     3;
     1,    -5,     6;
    -1,     1,     1;
     0,     1,     1];

P = Polyhedron('H', H);
clf;
P.plot
