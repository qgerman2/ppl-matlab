function P = convexHull(S)
    coder.cinclude("ppl_matlab.hpp");
    P = S{1};
    for i = 2:numel(S)
        coder.ceval("ppl_matlab::ConvexHull", ...
            coder.wref(P.instance), coder.ref(P.instance), coder.ref(S{i}.instance));
    end
    P.update_representation();
end