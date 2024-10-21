function empty = isEmptySet(P)
    coder.cinclude("ppl_matlab.hpp");
    empty = 0;
    empty = coder.ceval("ppl_matlab::Empty", coder.ref(P.instance));
end