function equal = eq(P, S)
    coder.cinclude("ppl_matlab.hpp");
    equal = 0;
    equal = coder.ceval("ppl_matlab::Equal", ...
        coder.ref(P.instance), coder.ref(S.instance));
end