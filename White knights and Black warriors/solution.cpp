#include <bits/stdc++.h>
using namespace std;

static const int _BUF = 1 << 20;
static char _ibuf[_BUF], *_iS, *_iE;
#define gc() (_iS == _iE ? (_iE = _ibuf + fread(_iS = _ibuf, 1, _BUF, stdin), _iS == _iE ? EOF : *_iS++) : *_iS++)
inline int read() {
    int x = 0, f = 1; char c = gc();
    while (c < '0' || c > '9') { if (c == '-') f = -1; c = gc(); }
    while (c >= '0' && c <= '9') x = x * 10 + (c & 15), c = gc();
    return x * f;
}
static char _obuf[_BUF], *_oS = _obuf, *_oE = _obuf + _BUF;
#define pc(x) (_oS == _oE ? fwrite(_obuf, 1, _oS - _obuf, stdout), _oS = _obuf : 0, *_oS++ = (x))
inline void flush() { fwrite(_obuf, 1, _oS - _obuf, stdout); _oS = _obuf; }
inline void print(int x) {
    if (x < 0) pc('-'), x = -x;
    if (x > 9) print(x / 10);
    pc(x % 10 + '0');
}

const int MAXN = 1e6 + 10;
const int INF  = 0x3f3f3f3f;

int N, Q;
int white[MAXN];
vector<int> adj[MAXN];

int distWhite[MAXN];
int q[MAXN], qL, qR;
void multiSourceBFS() {
    qL = qR = 0;
    for (int i = 1; i <= N; ++i)
        if (white[i]) distWhite[i] = 0, q[qR++] = i;
        else          distWhite[i] = INF;
    while (qL < qR) {
        int u = q[qL++];
        for (int v : adj[u])
            if (distWhite[v] == INF) {
                distWhite[v] = distWhite[u] + 1;
                q[qR++] = v;
            }
    }
}

int par[MAXN], sz[MAXN], dep[MAXN], heavy[MAXN], top[MAXN], dfn[MAXN], tick;
void dfs1(int u, int p) {
    par[u] = p; dep[u] = dep[p] + 1; sz[u] = 1; heavy[u] = -1;
    for (int v : adj[u]) if (v != p) {
        dfs1(v, u);
        sz[u] += sz[v];
        if (heavy[u] == -1 || sz[v] > sz[heavy[u]]) heavy[u] = v;
    }
}
void dfs2(int u, int tp) {
    top[u] = tp; dfn[u] = ++tick;
    if (heavy[u] != -1) dfs2(heavy[u], tp);
    for (int v : adj[u])
        if (v != par[u] && v != heavy[u]) dfs2(v, v);
}

int st[1 << 21], baseVal[MAXN];
inline int  idx(int l, int r) { return (l + r) | (l != r); }
void build(int l, int r) {
    int id = idx(l, r);
    if (l == r) { st[id] = baseVal[l]; return; }
    int m = (l + r) >> 1;
    build(l, m); build(m + 1, r);
    st[id] = min(st[idx(l, m)], st[idx(m + 1, r)]);
}
int query(int l, int r, int ql, int qr) {
    if (qr < l || ql > r) return INF;
    if (ql <= l && qr >= r) return st[idx(l, r)];
    int m = (l + r) >> 1;
    return min(query(l, m, ql, qr), query(m + 1, r, ql, qr));
}

int pathMin(int u, int v) {
    int res = INF;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res = min(res, query(1, N, dfn[top[u]], dfn[u]));
        u = par[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    res = min(res, query(1, N, dfn[u], dfn[v]));
    return res;
}

int main() {
    N = read(); Q = read();
    for (int i = 1; i <= N; ++i) white[i] = read();
    for (int i = 1, a, b; i < N; ++i) {
        a = read(); b = read();
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    multiSourceBFS();

    dfs1(1, 0);
    dfs2(1, 1);

    for (int u = 1; u <= N; ++u) baseVal[dfn[u]] = distWhite[u];
    build(1, N);

    while (Q--) {
        int u = read(), v = read();
        int ans = pathMin(u, v);
        if (white[u] || white[v]) ans = 0;
        print(ans); pc('\n');
    }
    flush();
    return 0;
}