#include <bits/stdc++.h>
using namespace std;

// -------- fast input --------
struct FastIn {
    static const int BUFSZ = 1 << 20;
    int i = 0, n = 0; char b[BUFSZ];
    inline char read() {
        if (i >= n) { n = (int)fread(b,1,BUFSZ,stdin); i = 0; if (!n) return 0; }
        return b[i++];
    }
    template<class T>
    bool nextInt(T& out) {
        char c; T sgn = 1, x = 0;
        c = read(); if (!c) return false;
        while (c!='-' && (c<'0'||c>'9')) { c = read(); if (!c) return false; }
        if (c=='-') { sgn = -1; c = read(); }
        for (; c>='0' && c<='9'; c = read()) x = x*10 + (c-'0');
        out = x*sgn; return true;
    }
} IN;

// two different 64-bit mixers (splitmix-like) with different salts
static inline uint64_t mixChild(uint64_t x) {
    x ^= 0x9E3779B97F4A7C15ull;           // salt C
    x ^= x >> 30; x *= 0xBF58476D1CE4E5B9ull;
    x ^= x >> 27; x *= 0x94D049BB133111EBull;
    x ^= x >> 31; return x;
}
static inline uint64_t mixParent(uint64_t x) {
    x ^= 0xC2B2AE3D27D4EB4Full;           // salt P
    x ^= x >> 30; x *= 0xD6E8FEB86659FD93ull;
    x ^= x >> 27; x *= 0xA5A3564E4F63C11Bull;
    x ^= x >> 31; return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; if (!IN.nextInt(N)) return 0;
    const int M = 2*(N-1);

    // CSR adjacency
    int *head = new int[N+1];
    int *to   = new int[M];
    int *nxt  = new int[M];
    for (int i=1;i<=N;++i) head[i] = -1;

    int e=0;
    for (int i=0;i<N-1;++i) {
        int u,v; IN.nextInt(u); IN.nextInt(v);
        to[e]=v; nxt[e]=head[u]; head[u]=e++;
        to[e]=u; nxt[e]=head[v]; head[v]=e++;
    }

    // parent & order (preorder), later reverse for postorder
    int *parent = new int[N+1];
    int *order  = new int[N];
    int *st     = new int[N];
    int top=0, ord=0;
    parent[1]=0; st[top++]=1;
    while(top){
        int u=st[--top];
        order[ord++]=u;
        int pu=parent[u];
        for(int ei=head[u]; ei!=-1; ei=nxt[ei]){
            int v=to[ei];
            if(v==pu) continue;
            parent[v]=u;
            st[top++]=v;
        }
    }

    // Downward: compute raw down[u] and cached tDown[u] = mixChild(down[u])
    const uint64_t SEED = 0xA24BAED4963EE407ull;
    uint64_t *down  = new uint64_t[N+1];
    uint64_t *tDown = new uint64_t[N+1];

    for (int i=ord-1;i>=0;--i){
        int u=order[i], pu=parent[u];
        uint64_t s = SEED;
        for(int ei=head[u]; ei!=-1; ei=nxt[ei]){
            int v=to[ei];
            if(v==pu) continue;
            s += tDown[v]; // child contributions already mixed (child-salt)
        }
        down[u] = s;            // keep raw node-hash
        tDown[u]= mixChild(s);  // cache child contribution once
    }

    // Upward + full hash
    uint64_t *up = new uint64_t[N+1];
    memset(up, 0, (N+1)*sizeof(uint64_t));
    vector<uint64_t> full; full.resize(N);
    int pos=0;

    for (int i=0;i<ord;++i){
        int u=order[i], pu=parent[u];

        // parent contribution distinguished
        uint64_t P = mixParent(up[u]);

        // sum of child contributions (child salt)
        uint64_t sumC = 0;
        for (int ei=head[u]; ei!=-1; ei=nxt[ei]){
            int v=to[ei];
            if(v==pu) continue;
            sumC += tDown[v];
        }

        uint64_t total = SEED + P + sumC;   // this is the rooted-at-u signature
        full[pos++] = total;

        // push up to children: remove that child’s (child-salt) contribution
        for (int ei=head[u]; ei!=-1; ei=nxt[ei]){
            int v=to[ei];
            if(v==pu) continue;
            up[v] = total - tDown[v];       // raw node-hash for the “rest”
        }
    }

    // count uniques by sorting
    sort(full.begin(), full.end());
    long long uniq=0;
    for(int i=0;i<N;){
        int j=i+1;
        while(j<N && full[j]==full[i]) ++j;
        if(j==i+1) ++uniq;
        i=j;
    }
    cout << uniq << '\n';

    // cleanup (optional)
    delete[] head; delete[] to; delete[] nxt;
    delete[] parent; delete[] order; delete[] st;
    delete[] down; delete[] tDown; delete[] up;
    return 0;
}
