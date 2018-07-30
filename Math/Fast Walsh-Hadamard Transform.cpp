const int N = 1<<16;

template <typename T>
struct FWT {
	void fwt(T io[], int n) {
		for (int d = 1; d < n; d <<= 1) {
			for (int i = 0, m = d<<1; i < n; i += m) {
				for (int j = 0; j < d; j++) { /// Don't forget modulo if required
					T x = io[i+j], y = io[i+j+d];
					io[i+j] = (x+y), io[i+j+d] = (x-y);	// xor
					// io[i+j] = x+y; // and
					// io[i+j+d] = x+y; // or
				}
			}
		}
	}
	void ufwt(T io[], int n) {
		for (int d = 1; d < n; d <<= 1) {
			for (int i = 0, m = d<<1; i < n; i += m) {
				for (int j = 0; j < d; j++) { /// Don't forget modulo if required
					T x = io[i+j], y = io[i+j+d];
					 /// Modular inverse if required here
					io[i+j] = (x+y)>>1, io[i+j+d] = (x-y)>>1; // xor
					// io[i+j] = x-y; // and
					// io[i+j+d] = y-x; // or
				}
			}
		}
	}
	// a, b are two polynomials and n is size which is power of two
	void convolution(T a[], T b[], int n) {
		fwt(a, n);
		fwt(b, n);
		for (int i = 0; i < n; i++)
			a[i] = a[i]*b[i];
		ufwt(a, n);
	}
	// for a*a	
	void self_convolution(T a[], int n) {
		fwt(a, n);
		for (int i = 0; i < n; i++)
			a[i] = a[i]*a[i];
		ufwt(a, n);
	}
};
FWT<ll> fwt;