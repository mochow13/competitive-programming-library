// Call with size of the grid
// Example: fenwick_tree_2d<int> Tree(n+1,m+1) for n x m grid indexed from 1

template <class T>
struct fenwick_tree_2d 
{
	vector<vector<T>> x;
	fenwick_tree_2d(int n, int m) : x(n, vector<T>(m)) { }
	void add(int k1, int k2, int a) { // x[k] += a
		for (; k1 < x.size(); k1 |= k1 + 1)
			for (int k = k2; k < x[k1].size(); k |= k + 1) x[k1][k] += a;
	}
	T sum(int k1, int k2) { // return x[0] + ... + x[k]
		T s = 0;
		for (; k1 >= 0; k1 = (k1 & (k1 + 1)) - 1)
			for (int k = k2; k >= 0; k = (k & (k + 1)) - 1) s += x[k1][k];
		return s;
	}
};