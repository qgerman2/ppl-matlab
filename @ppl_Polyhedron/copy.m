function R = copy(P)
    R = ppl_Polyhedron();
    coder.ceval("ppl_matlab::Polyhedron_Copy", coder.wref(R.instance), coder.ref(P.instance));
    R.update_representation();
end

