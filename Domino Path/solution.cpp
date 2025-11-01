#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // --- Precompute edges (domino types 1..7) ---
    vector<pair<int,int>> edges;
    for(int x=1;x<=6;++x)
        for(int y=x+1;y<=7;++y)
            edges.emplace_back(x,y);
    const int E = edges.size(); // 21

    // Map 2D (x,y) -> index
    int idxMap[8][8]; // 1..7
    memset(idxMap,-1,sizeof(idxMap));
    for(int i=0;i<E;++i){
        auto [x,y] = edges[i];
        idxMap[x][y] = i;
    }

    // Arrays de adyacencia por nodo
    int u[E],v[E],adjMask[8]={};
    for(int i=0;i<E;++i){
        u[i]=edges[i].first;
        v[i]=edges[i].second;
        adjMask[u[i]] |= 1<<i;
        adjMask[v[i]] |= 1<<i;
    }

    // --- Precompute all valid masks ---
    static uint8_t ok[1<<21]={};
    for(int mask=1; mask < (1<<E); ++mask){
        int deg[8]={};
        int used=0;
        for(int mm=mask; mm; mm &= mm-1){
            int e = __builtin_ctz(mm);
            int a=u[e],b=v[e];
            deg[a]++; deg[b]++;
            used |= (1<<a)|(1<<b);
        }
        if(!used) continue;

        // DFS sobre nodos usados
        int start = 1;
        while(!((used>>start)&1)) start++;
        int seen=0, stack[8], top=0;
        stack[top++]=start;
        while(top){
            int x=stack[--top];
            if((seen>>x)&1) continue;
            seen |= 1<<x;
            int m = adjMask[x] & mask;
            while(m){
                int e = __builtin_ctz(m);
                m &= m-1;
                int nxt = (u[e]==x? v[e]: u[e]);
                if(!((seen>>nxt)&1)) stack[top++] = nxt;
            }
        }
        if((seen & used) != used) continue;

        // Check degrees (Eulerian path)
        int odd=0;
        for(int i=1;i<=7;++i) odd += deg[i]&1;
        if(odd==0 || odd==2) ok[mask]=1;
    }

    // --- Precompute subset sums (Fast Zeta Transform) ---
    static int dp[1<<21];
    for(int mask=0; mask < (1<<E); ++mask)
        dp[mask] = ok[mask];

    for(int i=0;i<E;++i){
        for(int mask=0; mask < (1<<E); ++mask){
            if(mask & (1<<i))
                dp[mask] += dp[mask^(1<<i)];
        }
    }

    // --- Leer test cases ---
    int T; cin >> T;
    while(T--){
        int M; cin >> M;
        int mask=0;
        for(int i=0;i<M;++i){
            int x,y; cin >> x >> y;
            if(x>y) swap(x,y);
            mask |= 1<<idxMap[x][y];
        }
        cout << dp[mask] << '\n';
    }

    return 0;
}
