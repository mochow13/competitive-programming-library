// Solves SPOJ HORRIBLE. Range addition and range sum query.
struct node {
	int from, to;
	long long value, lazy;
	node *left, *right;
	node() {
		from = 1;
		to = 1e5;
		value = 0;
		lazy = 0;
		left = NULL;
		right = NULL;
	}
	void extend() {
		if (left == NULL) {
			left = new node();
			right = new node();
			left->from = from;
			left->to = (from + to) >> 1;
			right->from = ((from + to) >> 1) + 1;
			right->to = to;
		}
	}
};

node *root;
int tests, n, queries;
void update_tree(node *curr, int left, int right, long long value) {
	if (curr->lazy) {
		curr->value += (curr->to - curr->from + 1) * curr->lazy;
		if (curr->from != curr->to) {
			curr->extend();
			curr->left->lazy += curr->lazy;
			curr->right->lazy += curr->lazy;
		}
		curr->lazy = 0;
	}
	if ((curr->from) > (curr->to) || (curr->from) > right || (curr->to) < left) return;
	if (curr->from >= left && curr->to <= right) {
		curr->value += (curr->to - curr->from + 1) * value;
		if (curr->from != curr->to) {
			curr->extend();
			curr->left->lazy += value;
			curr->right->lazy += value;
		}
		return;
	}
	curr->extend();
	update_tree(curr->left, left, right, value);
	update_tree(curr->right, left, right, value);
	curr->value = curr->left->value + curr->right->value;
}
long long query_tree(node *curr, int left, int right) {
	if ((curr->from) > (curr->to) || (curr->from) > right || (curr->to) < left) return 0;
	if (curr->lazy) {
		curr->value += (curr->to - curr->from + 1) * curr->lazy;
		curr->extend();
		curr->left->lazy += curr->lazy;
		curr->right->lazy += curr->lazy;
		curr->lazy = 0;
	}
	if (curr->from >= left && curr->to <= right) return curr->value;
	long long q1, q2;
	curr->extend();
	q1 = query_tree(curr->left, left, right);
	q2 = query_tree(curr->right, left, right);
	return q1 + q2;
}

int main() {
	int type, p, q;
	long long v;
	int i;
	scanf("%d", &tests);
	while (tests--) {
		root = new node();
		scanf("%d %d", &n, &queries);
		for (i = 1; i <= queries; i++) {
			scanf("%d", &type);
			if (type == 0) {
				scanf("%d %d %lld", &p, &q, &v);
				if (p > q) swap(p, q);
				update_tree(root, p, q, v);
			}
			else {
				scanf("%d %d", &p, &q);
				if (p > q) swap(p, q);
				printf("%lld\n", query_tree(root, p, q));
			}
		}
	}
	return 0;
}