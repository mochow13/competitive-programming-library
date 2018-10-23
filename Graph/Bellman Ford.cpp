// Is there a negative cycle in the graph?
bool bellman(int src)
{
    // Nodes are indexed from 1
	for (int i = 1; i <= n; i++) 
		dist[i] = INF; 
	dist[src] = 0; 
    for(int i = 2; i <= n; i++) 
    { 
        for (int j = 0; j < edges.size(); j++) 
        { 
            int u = edges[j].first; 
            int v = edges[j].second; 
            ll weight = adj[u][v]; 
            if (dist[u]!=INF && dist[u] + weight < dist[v]) 
                dist[v] = dist[u] + weight;
        } 
    }
	for (int i = 0; i < edges.size(); i++) 
    { 
		int u = edges[i].first; 
		int v = edges[i].second; 
		ll weight = adj[u][v];
        // True if neg-cylce exists
		if (dist[u]!=INF && dist[u] + weight < dist[v]) 
			return true;
    }
	return false;
}