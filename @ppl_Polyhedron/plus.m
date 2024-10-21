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