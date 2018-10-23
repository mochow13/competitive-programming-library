// Useful when the graph only has weights 0 or 1.
// Complexity becomes O(V+E)

for all v in vertices:
	dist[v] = inf
dist[source] = 0;
deque d
d.push_front(source)
while d.empty() == false:
	vertex = get front element and pop_front
	// Go to all edges
	for all edges e of form (vertex , u):
		// consider relaxing with 0 or 1 weight edges
		if travelling e relaxes distance to u:
			relax dist[u]
			if e.weight = 1:
				d.push_back(u)
			else:
				d.push_front(u)