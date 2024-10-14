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
    end
    properties (SetAccess = private)
        instance
        dimension = 0;
        constraints = 0;
        vertices = 0;
        rays = 0;
        A = [];
        b = [];
        H = [];
        V = [];
        R = [];
    end
    methods (Access = public)
        function P = ppl_Polyhedron(varargin)
            coder.cinclude("ppl_matlab.hpp");
            P.instance = coder.opaque("Parma_Polyhedra_Library::C_Polyhedron");
            if nargin == 2
                % A, b non strict inequality constructor
                A = varargin{1};
                b = varargin{2};
                coder.ceval("ppl_matlab::Polyhedron", coder.wref(P.instance), ...
                coder.ref(A), size(A, 1), size(A, 2), ...
                coder.ref(b));
                P.update_representation();
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
    end
    methods (Access = private)
        % update polyhedron properties after a change
        function update_representation(P)
            coder.cinclude("ppl_matlab.hpp");
            % get number of constraints and dimension
            coder.ceval("ppl_matlab::Size", ...
                coder.ref(P.instance), ...
                coder.wref(P.constraints), ...
                coder.wref(P.dimension), ...
                coder.wref(P.vertices), ...
                coder.wref(P.rays));
            % prepare empty A and b matrices
            P.A = zeros(P.constraints, P.dimension);
            P.b = zeros(P.constraints, 1);
            P.V = zeros(P.vertices, P.dimension);
            P.R = zeros(P.rays, P.dimension);
            % fill
            coder.ceval("ppl_matlab::A", coder.ref(P.instance), coder.wref(P.A));
            coder.ceval("ppl_matlab::b", coder.ref(P.instance), coder.wref(P.b));
            coder.ceval("ppl_matlab::V", coder.ref(P.instance), coder.wref(P.V), P.vertices);
            coder.ceval("ppl_matlab::R", coder.ref(P.instance), coder.wref(P.R), P.rays);
            % update H representation
            P.H = [P.A, P.b];
        end
    end
end