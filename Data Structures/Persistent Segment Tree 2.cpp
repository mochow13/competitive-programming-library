const int MAXN = (1 << 20);

struct node
{
	int sum;
	node *l, *r;
	node() { l = nullptr; r = nullptr; sum = 0; }
	node(int x) { sum = x; l = nullptr; r = nullptr;	}
};

typedef node* pnode;

pnode merge(pnode l, pnode r)
{
	pnode ret = new node(0);
	ret->sum = l->sum + r->sum;
	ret->l = l;
	ret->r = r;
	return ret;
}

pnode init(int l, int r)
{
	if(l == r) { return (new node(0));}

	int mid = (l + r) >> 1;
	return merge(init(l, mid), init(mid + 1, r));
}

pnode update(int pos, int val, int l, int r, pnode nd)
{
	if(pos < l || pos > r) return nd;
	if(l == r) { return (new node(val)); }

	int mid = (l + r) >> 1;
	return merge(update(pos, val, l, mid, nd->l), update(pos, val, mid + 1, r, nd->r));
}

int query(int qL, int qR, int l, int r, pnode nd)
{
	if(qL <= l && r <= qR) return nd->sum;
	if(qL > r || qR < l) return 0;

	int mid = (l + r) >> 1;
    return query(qL, qR, l, mid, nd->l) + query(qL, qR, mid + 1, r, nd->r);
}

int get_kth(int k, int l, int r, pnode nd)
{
	if(l == r) return l;

	int mid = (l + r) >> 1;
	if(nd->l->sum < k) return get_kth(k - nd->l->sum, mid + 1, r, nd->r);
	else return get_kth(k, l, mid, nd->l);
}
