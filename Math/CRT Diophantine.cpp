// Chinese remainder theorem (special case): find z such that
// z % x = a, z % y = b. Here, z is unique modulo M = lcm(x,y).
// Return (z,M). On failure, M = -1.
PII chinese_remainder_theorem(int x, int a, int y, int b) {
	int s, t;
	int d = extended_euclid(x, y, s, t);
	if (a % d != b % d) return make_pair(0, -1);
	return make_pair(mod(s * b * x + t * a * y, x * y) / d, x * y / d);
}

// Chinese remainder theorem: find z such that
// z % x[i] = a[i] for all i. Note that the solution is
// unique modulo M = lcm_i (x[i]). Return (z,M). On
// failure, M = -1. Note that we do not require the a[i]'s
// to be relatively prime.

PII chinese_remainder_theorem(const VI &x, const VI &a) {
	PII ret = make_pair(a[0], x[0]);
	for (int i = 1; i < x.size(); i++) {
		ret = chinese_remainder_theorem(ret.second, ret.first, x[i], a[i]);
		if (ret.second == -1) break;
	}
	return ret;
}

// computes x and y such that ax + by = c; on failure, x = y =-1
void linear_diophantine(int a, int b, int c, int &x, int &y) {
	int d = gcd(a, b);
	if (c % d) {
		x = y = -1;
	} else {
		x = c / d * mod_inverse(a / d, b / d);
		y = (c - a * x) / b;
	}
}