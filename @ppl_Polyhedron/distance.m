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