classdef ppl_Polyhedron < coder.ExternalDependency & handle
    %#codegen
    methods (Static)
        % coder.ExternalDependency required static methods
        % for code generation
        function name = getDescriptiveName()
            name = "MPT like Polyhedron class built on Parma Polyhedra";
        end
        function tf = isSupportedContext(buildContext)
            tf = true;
        end
        function updateBuildInfo(buildInfo, buildContext)
            % External libraries
            libPath = fullfile(pwd,"lib/");
            libName = {'libppl.a','libgmpxx.a','libgmp.a'};
            buildInfo.addLinkObjects(libName, libPath, '', true, true);
            buildInfo.addIncludePaths(libPath);
            % Binding source code
            buildInfo.addSourceFiles('ppl_matlab.cpp');
        end
        % constructors
        function P = from_HRep(A, b)
            % A, b non strict inequality constructor
            coder.cinclude("ppl_matlab.hpp");
            P = ppl_Polyhedron();
            coder.ceval("ppl_matlab::Polyhedron_HRep", coder.wref(P.instance), ...
            coder.ref(A), size(A, 1), size(A, 2), ...
            coder.ref(b));
            P.update_representation();
        end
        function P = from_VRep(V, R)
            % V, R vertices and rays constructor
            coder.cinclude("ppl_matlab.hpp");
            P = ppl_Polyhedron();
            coder.ceval("ppl_matlab::Polyhedron_VRep", coder.wref(P.instance), ...
                coder.ref(V), coder.ref(R), ...
                size(V, 2), size(V, 1), size(R, 1));
            P.update_representation();
        end
        % convex hull
        function P = convexHull(S)
            coder.cinclude("ppl_matlab.hpp");
            P = S{1};
            for i = 2:numel(S)
                coder.ceval("ppl_matlab::ConvexHull", ...
                    coder.wref(P.instance), coder.ref(P.instance), coder.ref(S{i}.instance));
            end
            P.update_representation();
        end
    end
    properties (SetAccess = private)
        instance
        Dim  = 0;
        inequalities = 0;
        equalities = 0;
        vertices = 0;
        rays = 0;
        A = [];
        b = [];
        H = [];
        V = [];
        R = [];
        Ae = [];
        be = [];
        He = [];
    end
    methods (Access = public)
        function P = ppl_Polyhedron(varargin)
            coder.cinclude("ppl_matlab.hpp");
            if (nargin == 2)
                % call H rep constructor
                P = ppl_Polyhedron.from_HRep(varargin{1}, varargin{2});
            else 
                P.instance = coder.opaque("Parma_Polyhedra_Library::C_Polyhedron");
            end
        end
        function contained = contains(P, B)
            coder.cinclude("ppl_matlab.hpp");
            contained = 0;
            contained = coder.ceval("ppl_matlab::Contains", ...
                coder.ref(P.instance), coder.ref(B.instance));
        end
        function R = minus(P, S)
            coder.cinclude("ppl_matlab.hpp");
            R = ppl_Polyhedron();
            coder.ceval("ppl_matlab::Minus", ...
                coder.wref(R.instance), coder.ref(P.instance), coder.ref(S.instance));
            R.update_representation();
        end
        function R = affineMap(P, M)
            coder.cinclude("ppl_matlab.hpp");
            R = ppl_Polyhedron();
            coder.ceval("ppl_matlab::AffineMap", ...
                coder.wref(R.instance), coder.ref(P.instance), coder.ref(M));
            R.update_representation();
        end
        % minkowski sum from mpt3 source
        % https://github.com/kvasnica/mpt3/blob/master/source/mpt/modules/geometry/sets/%40Polyhedron/plus.m
        function R = plus(P, S)
            Vp = P.V; Vs = S.V;
            Rp = P.R; Rs = S.R;
            if size(Vp, 1)==0
				newV = Vs;
			elseif size(Vs, 1)==0
				newV = Vp;
			else
				newV = zeros(size(Vp,1)*size(Vs,1), P.Dim);
				for i = 1:size(Vs, 1)
					newV((i-1)*size(Vp, 1)+1:i*size(Vp, 1), :) = bsxfun(@plus, Vp, Vs(i, :));
				end
            end
            if size(Rp, 1)==0
				newR = Rs;
			elseif size(Rs, 1)==0
				newR = Rp;
			else
				newR = zeros(size(Rp,1)*size(Rs,1), P.Dim);
				for i = 1:size(Rs, 1)
					newR((i-1)*size(Rp, 1)+1:i*size(Rp, 1), :) = bsxfun(@plus, Rp, Rs(i, :));
				end
            end
            R = ppl_Polyhedron.from_VRep(newV, newR);
        end
        function empty = isEmptySet(P)
            coder.cinclude("ppl_matlab.hpp");
            empty = 0;
            empty = coder.ceval("ppl_matlab::Empty", coder.ref(P.instance));
        end
        % Check if point x0 is inside polyhedron P
        function inside = isInside(P, x0)
            assert(isvector(x0));
            if (size(x0,1)==1)   % if it is row vector
                x = ppl_Polyhedron.from_VRep(x0, []);
            else                 % column vector gets transposed to row vector
                x = ppl_Polyhedron.from_VRep(x0', []);
            end
            coder.cinclude("ppl_matlab.hpp");
            inside = P.contains(x);
        end
        function equal = eq(P, S)
            coder.cinclude("ppl_matlab.hpp");
            equal = 0;
            equal = coder.ceval("ppl_matlab::Equal", ...
                coder.ref(P.instance), coder.ref(S.instance));
        end
        function R = intersect(P, S)
            coder.cinclude("ppl_matlab.hpp");
            R = ppl_Polyhedron();
            coder.ceval("ppl_matlab::Intersect", ...
                coder.wref(R.instance), coder.ref(P.instance), coder.ref(S.instance));
            R.update_representation();
        end
        function res = distance(P, S)
            assert(P.Dim == S.Dim);
            opt_A = blkdiag(P.A, S.A);
            opt_b = [P.b; S.b];
            opt_Ae = blkdiag(P.Ae, S.Ae);
            opt_be = [P.be; S.be];
            fun = @(x) norm(x(1:P.Dim) - x(P.Dim+1:end));
            options = optimoptions('fmincon','Algorithm','sqp');
            [opt, fval] = fmincon(fun, ...
                zeros(1, P.Dim*2), ...
                opt_A, opt_b, opt_Ae, opt_be, ...
                [], [], [], options);
            res.x = opt(P.Dim+1:end);
            res.y = opt(1:P.Dim);
            res.dist = fval;
        end
        function res = project(P, x0)
            assert(isvector(x0));
            if (size(x0,1)==1)   % if it is row vector
                S = ppl_Polyhedron.from_VRep(x0, []);
            else                 % column vector gets transposed to row vector
                S = ppl_Polyhedron.from_VRep(x0', []);
            end
            res = P.distance(S);
        end
        function R = projection(P, dims)
            R = ppl_Polyhedron.from_VRep(P.V(:, dims), P.R(:, dims));
        end
    end
    methods (Access = private)
        % update polyhedron properties after a change
        function update_representation(P)
            coder.cinclude("ppl_matlab.hpp");
            % get number of constraints and dimension
            coder.ceval("ppl_matlab::Size", ...
                coder.ref(P.instance), ...
                coder.wref(P.inequalities), ...
                coder.wref(P.equalities), ...
                coder.wref(P.Dim), ...
                coder.wref(P.vertices), ...
                coder.wref(P.rays));
            % prepare empty A and b matrices
            P.A = zeros(P.inequalities, P.Dim);
            P.b = zeros(P.inequalities, 1);
            P.V = zeros(P.vertices, P.Dim);
            P.R = zeros(P.rays, P.Dim);
            P.Ae = zeros(P.equalities, P.Dim);
            P.be = zeros(P.equalities, 1);
            % fill
            coder.ceval("ppl_matlab::A", coder.ref(P.instance), coder.wref(P.A));
            coder.ceval("ppl_matlab::b", coder.ref(P.instance), coder.wref(P.b));
            coder.ceval("ppl_matlab::V", coder.ref(P.instance), coder.wref(P.V), P.vertices);
            coder.ceval("ppl_matlab::R", coder.ref(P.instance), coder.wref(P.R), P.rays);
            coder.ceval("ppl_matlab::Ae", coder.ref(P.instance), coder.wref(P.Ae));
            coder.ceval("ppl_matlab::be", coder.ref(P.instance), coder.wref(P.be));
            % update H representation
            P.H = [P.A, P.b];
            P.He = [P.Ae, P.be];
        end
    end
end