classdef ppl < coder.ExternalDependency
    %#codegen
    methods (Static)
        function name = getDescriptiveName()
            name = "mi api";
        end
        function tf = isSupportedContext(buildContext)
            tf = true;
        end
        function updateBuildInfo(buildInfo, buildContext)
            % librerias
            libPath = fullfile(pwd,"lib/");
            libName = {'libppl.a','libgmpxx.a','libgmp.a'};
            buildInfo.addLinkObjects(libName, libPath, '', true, true);
            buildInfo.addIncludePaths(libPath);
            % fuentes
            buildInfo.addSourceFiles('ppl_matlab.cpp');
        end

        function P = Polyhedron(A, b)
            coder.cinclude("ppl_matlab.hpp");
            P = coder.opaque("Parma_Polyhedra_Library::C_Polyhedron");
            coder.ceval("ppl_matlab::Polyhedron", coder.wref(P), ...
                coder.ref(A), size(A, 1), size(A, 2), ...
                coder.ref(b));
        end

        function contained = Contains(A, B)
            coder.cinclude("ppl_matlab.hpp");
            contained = 0;
            contained = coder.ceval("ppl_matlab::Contains", ...
                coder.ref(A), coder.ref(B));
        end

        function R = Minus(P, S)
            coder.cinclude("ppl_matlab.hpp");
            R = coder.opaque("Parma_Polyhedra_Library::C_Polyhedron");
            coder.ceval("ppl_matlab::Minus", ...
                coder.wref(R), coder.ref(P), coder.ref(S));
        end

        function R = AffineMap(P, M)
            coder.cinclude("ppl_matlab.hpp");
            R = coder.opaque("Parma_Polyhedra_Library::C_Polyhedron");
            coder.ceval("ppl_matlab::AffineMap", ...
                coder.wref(R), coder.ref(P), coder.ref(M));
        end

        function [cs, dim] = Size(P)
            coder.cinclude("ppl_matlab.hpp");
            cs = -1;
            dim = -1;
            coder.ceval("ppl_matlab::Size", ...
                coder.ref(P), coder.wref(cs), coder.wref(dim));
        end

        function M = A(P)
            coder.cinclude("ppl_matlab.hpp");
            [rows, cols] = ppl.Size(P);
            M = zeros(rows, cols);
            coder.ceval("ppl_matlab::A", ...
                coder.ref(P), coder.wref(M));
        end

        function M = b(P)
            coder.cinclude("ppl_matlab.hpp");
            [rows, ~] = ppl.Size(P);
            M = zeros(rows, 1);
            coder.ceval("ppl_matlab::b", ...
                coder.ref(P), coder.wref(M));
        end
    end
end