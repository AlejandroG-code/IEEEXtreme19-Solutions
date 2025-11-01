#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int64_t w;   // time
    int r;       // risk
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if (!(cin >> T)) return 0;

    const int INF_R = INT_MAX;
    const long long INF_T = (long long)4e18;

    while (T--) {
        int N, M; 
        cin >> N >> M;

        vector<vector<Edge>> g(N + 1);
        g.reserve(N + 1);

        for (int i = 0; i < M; ++i) {
            int u, v; long long W; int R;
            cin >> u >> v >> W >> R;
            g[u].push_back({v, W, R});
            g[v].push_back({u, W, R});
        }

        // -------- Pass 1: minimize maximum risk (minimax path) --------
        vector<int> minRisk(N + 1, INF_R);
        using P1 = pair<int,int>; // (current max risk, node)
        priority_queue<P1, vector<P1>, greater<P1>> pq1;

        minRisk[1] = 0;
        pq1.push({0,1});

        while (!pq1.empty()) {
            auto [cr, u] = pq1.top(); pq1.pop();
            if (cr != minRisk[u]) continue;
            if (u == N) break; // early exit ok
            for (const auto &e : g[u]) {
                int nr = max(cr, e.r);
                if (nr < minRisk[e.to]) {
                    minRisk[e.to] = nr;
                    pq1.push({nr, e.to});
                }
            }
        }

        if (minRisk[N] == INF_R) {
            cout << -1 << '\n';
            continue;
        }
        int bestR = minRisk[N];

        // -------- Pass 2: minimize total time with risk cap bestR --------
        vector<long long> dist(N + 1, INF_T);
        using P2 = pair<long long,int>; // (time, node)
        priority_queue<P2, vector<P2>, greater<P2>> pq2;

        dist[1] = 0;
        pq2.push({0,1});

        while (!pq2.empty()) {
            auto [ct, u] = pq2.top(); pq2.pop();
            if (ct != dist[u]) continue;
            if (u == N) break; // early exit ok
            for (const auto &e : g[u]) {
                if (e.r > bestR) continue; // respect risk cap
                long long nt = ct + e.w;
                if (nt < dist[e.to]) {
                    dist[e.to] = nt;
                    pq2.push({nt, e.to});
                }
            }
        }

        cout << bestR << ' ' << dist[N] << '\n';
    }
    return 0;
}
