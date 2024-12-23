classdef ppl_Polyhedron < coder.ExternalDependency & handle
    %#codegen
     properties (SetAccess = private)
        instance
        Dim =  0;
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
            % Library path and source
            libPath = fullfile(pwd,"@ppl_Polyhedron/lib");
            libName = {'libppl.a','libgmpxx.a','libgmp.a'};
            buildInfo.addLinkObjects(libName, libPath, '', true, true);
            buildInfo.addIncludePaths(libPath);
            % Binding source code
            buildInfo.addSourceFiles('ppl_matlab.cpp', libPath, '');
        end
        % static constructors
        P = from_HRep(A, b, Ae, be)
        P = from_VRep(V, R)
        P = convexHull(S)
        P = copy(S)
    end
    methods (Access = public)
        function P = ppl_Polyhedron(varargin)
            coder.cinclude("ppl_matlab.hpp");
            if (nargin == 1)
                % copy constructor
                P = ppl_Polyhedron.copy(varargin{1});
            elseif (nargin == 2)
                % call H rep constructor
                P = ppl_Polyhedron.from_HRep(varargin{1}, varargin{2}, [], []);
            else 
                P.instance = coder.opaque("Parma_Polyhedra_Library::C_Polyhedron");
            end
        end
        % stubs
        function minHRep(P)

        end
        function minVRep(P)

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