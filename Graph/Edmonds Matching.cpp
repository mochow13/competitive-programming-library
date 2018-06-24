/*
 * Algorithm: Edmonds Blossom Maximum Matching in Generel Graph
 * Order : O( N^4 )
 * Note : vertx must be  indexing based
 */

#include<stdio.h>
#include<string.h>
using namespace std;
#define MAX_V 103
#define MAX_E MAX_V*MAX_V

long nV,nE,Match[MAX_V];
long Last[MAX_V], Next[MAX_E], To[MAX_E];
long eI;
long q[MAX_V], Pre[MAX_V], Base[MAX_V];
bool Hash[MAX_V], Blossom[MAX_V], Path[MAX_V];

void Insert(long u, long v) {
    To[eI] = v, Next[eI] = Last[u], Last[u] = eI++;
    To[eI] = u, Next[eI] = Last[v], Last[v] = eI++;
}

long Find_Base(long u, long v) {
    memset( Path,0,sizeof(Path));
    for (;;) {
        Path[u] = 1;
        if (Match[u] == -1) break;
        u = Base[Pre[Match[u]]];
    }
    while (Path[v] == 0) v = Base[Pre[Match[v]]];
    return v;
}

void Change_Blossom(long b, long u) {
    while (Base[u] != b) {
        long v = Match[u];
        Blossom[Base[u]] = Blossom[Base[v]] = 1;
        u = Pre[v];
        if (Base[u] != b) Pre[u] = v;
    }
}

long Contract(long u, long v) {
    memset( Blossom,0,sizeof(Blossom));
    long b = Find_Base(Base[u], Base[v]);
    Change_Blossom(b, u);
    Change_Blossom(b, v);
    if (Base[u] != b) Pre[u] = v;
    if (Base[v] != b) Pre[v] = u;
    return b;
}

void Augment(long u) {
    while (u != -1) {
        long v = Pre[u];
        long k = Match[v];
        Match[u] = v;
        Match[v] = u;
        u = k;
    }
}

long Bfs( long p ){
    memset( Pre,-1,sizeof(Pre));
    memset( Hash,0,sizeof(Hash));
    long i;
    for( i=1;i<=nV;i++ ) Base[i] = i;
    q[1] = p, Hash[p] = 1;
    for (long head=1, rear=1; head<=rear; head++) {
        long u = q[head];
        for (long e=Last[u]; e!=-1; e=Next[e]) {
            long v = To[e];
            if (Base[u]!=Base[v] and v!=Match[u]) {
                if (v==p or (Match[v]!=-1 and Pre[Match[v]]!=-1)) {
                    long b = Contract(u, v);
                    for( i=1;i<=nV;i++ ) if (Blossom[Base[i]]==1) {
                        Base[i] = b;
                        if (!Hash[i]) {
                            Hash[i] = 1;
                            q[++rear] = i;
                        }
                    }
                } else if (Pre[v]==-1) {
                    Pre[v] = u;
                    if (Match[v]==-1) {
                        Augment(v);
                        return 1;
                    }
                    else {
                        q[++rear] = Match[v];
                        Hash[Match[v]] = 1;
                    }
                }
            }
        }
    }
    return 0;
}

long Edmonds_Blossom( void ){
    long i,Ans = 0;
    memset( Match,-1,sizeof(Match));
    for( i=1;i<=nV;i++ ) if (Match[i] == -1) Ans += Bfs(i);
    return Ans;
}


int main( void ){
    eI = 0;
    memset( Last,-1,sizeof(Last));

}
