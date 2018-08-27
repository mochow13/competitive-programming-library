int dist[MAX], inq[MAX];
void spfa(int source)
{
	FOR(i,1,n+1) inq[i]=false, dist[i]=inf; // or INF
	dist[source]=0;
	queue<int> Q; 
	Q.push(source);
	inq[source]=true;

	while(!Q.empty())
	{
		int u=Q.front();
		Q.pop();
		FOR(j,0,graph[u].size())
		{
			int v=graph[u][j];

			if(dist[u]+cost[u][j]<dist[v])
			{
				dist[v]=dist[u]+cost[u][j];
				if(!inq[v])
				{
					Q.push(v);
					inq[v]=true;
				}
			}
		}
		inq[u]=false;
	}
}