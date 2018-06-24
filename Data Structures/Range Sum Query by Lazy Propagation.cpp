int a[MAX + 7], tree[4 * MAX + 7], lazy[4 * MAX + 7];
void build(int node, int l, int r)
{
	if (l == r)
	{
		tree[node] = a[l];
		return;
	}
	if (l >= r) return;
	int mid = (l + r) / 2;
	build(node * 2, l, mid);
	build(node * 2 + 1, mid + 1, r);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}
void upd(int node, int l, int r, int v)
{
	lazy[node] += v;
	tree[node] += (r - l + 1) * x;
}
void pushDown(int node, int l, int r) //passing update information to the children
{
	int mid = (l + r) / 2;
	upd(node * 2, l, mid, lazy[node]);
	upd(node * 2 + 1, mid + 1, r, lazy[node]);
	lazy[node] = 0;
}
void update(int node, int l, int r, int x, int y, int v)
{
	if (x > r || y < l) return;
	if (x >= l && r <= y)
	{
		upd(node, l, r, v);
		return;
	}
	pushDown(node, l, r);
	int mid = (l + r) / 2;
	update(node * 2, l, mid, x, y, v);
	update(node * 2 + 1, mid + 1, r, x, y, v);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}