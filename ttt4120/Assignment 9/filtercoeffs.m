function B = filtercoeffs(fc, w)

n = 0:(size(w,2)-1);

h = 2*fc*sinc(2*pi*fc*n);

B = h .* w;
