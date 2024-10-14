clc;
clearvars;
clf;

A1 = [eye(2); -eye(2)];
b1 = [1;1;1;1];

A = Polyhedron(A1, b1);

V2 = [0, 0; 0, 1; 1, 1; 1, 0];

B = Polyhedron('V', V2);

S = A.plus(B);

S.minHRep;S.minVRep;

S.H
S.V

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