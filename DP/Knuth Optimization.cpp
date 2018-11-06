/*This trick works only for optimization DP over substrings for which optimal
middle point depends monotonously on the end points. Let mid[L,R] be the first
middle point for (L,R) substring which gives optimal result. It can be proven
that mid[L,R-1] <= mid[L,R] <= mid[L+1,R] - this means monotonicity of mid by
L and R. Applying this optimization reduces time complexity from O(k^3) to O(k^2)
 because with fixed s (substring length) we have m_right(L) = mid[L+1][R] = m_left(L+1).
 That's why nested L and M loops require not more than 2k iterations overall.*/

for (int s = 0; s <= k; s++) //s - length(size) of substring
	for (int L = 0; L + s <= k; L++) { //L - left point
		int R = L + s; //R - right point
		if (s < 2) {
			res[L][R] = 0; //DP base - nothing to break
			mid[L][R] = l; //mid is equal to left border
			continue;
		}
		int mleft = mid[L][R - 1]; //Knuth's trick: getting bounds on M
		int mright = mid[L + 1][R];
		res[L][R] = 1000000000000000000LL;
		for (int M = mleft; M <= mright; M++) { //iterating for M in the bounds only
			ll tres = res[L][M] + res[M][R] + (x[R] - x[L]);
			if (res[L][R] > tres) {  //relax current solution
				res[L][R] = tres;
				mid[L][R] = M;
			}
		}
	}
ll answer = res[0][k];
