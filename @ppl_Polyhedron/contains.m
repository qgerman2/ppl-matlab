function contained = contains(P, B)
    coder.cinclude("ppl_matlab.hpp");
    contained = 0;
    contained = coder.ceval("ppl_matlab::Contains", ...
        coder.ref(P.instance), coder.ref(B.instance));
end