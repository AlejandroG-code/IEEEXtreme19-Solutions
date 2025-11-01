#include <bits/stdc++.h>
using namespace std;

int N;
string ans;

// Try to build an entire subtree of size S using the multiset "cnt".
// On success, appends "(()...)" to 'ans' and consumes counts.
// Full backtracking: we snapshot and restore on failure.
bool buildSubtree(int S, vector<int> &cnt);

// Choose and build children that sum exactly to `remaining`.
// We enumerate child sizes descending (<= prevMax) and backtrack.
bool buildChildren(int remaining, int prevMax, vector<int> &cnt) {
    if (remaining == 0) return true;

    for (int t = min(prevMax, remaining); t >= 1; --t) {
        if (cnt[t] == 0) continue;

        // Snapshot before trying a child of size t
        vector<int> backup = cnt;
        size_t mark = ans.size();

        if (buildSubtree(t, cnt)) {
            if (buildChildren(remaining - t, t, cnt)) return true;
        }

        // Revert and try a different choice
        cnt = backup;
        ans.resize(mark);
    }
    return false;
}

bool buildSubtree(int S, vector<int> &cnt) {
    if (S < 1 || S > N || cnt[S] == 0) return false;

    // Snapshot for this subtree in case its children fail
    vector<int> backup = cnt;
    size_t mark = ans.size();

    // Use this node as root
    cnt[S]--;
    ans.push_back('(');

    // Build children whose sizes add up to S-1
    if (!buildChildren(S - 1, N, cnt)) {
        // Backtrack
        cnt = backup;
        ans.resize(mark);
        return false;
    }

    ans.push_back(')');
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> N)) return 0;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    // Every distance must be even: Ai = 2 * (# enclosed pairs)
    for (int x : A) {
        if (x & 1) { cout << "No\n"; return 0; }
    }

    // s = Ai/2 + 1  (subtree size including the node)
    vector<int> cnt(N + 1, 0);
    for (int x : A) {
        int s = x / 2 + 1;
        if (s < 1 || s > N) { cout << "No\n"; return 0; }
        cnt[s]++;
    }

    // Build a forest: repeatedly take the largest remaining size as a tree root
    int left = N;
    while (left > 0) {
        int S = -1;
        for (int s = N; s >= 1; --s) if (cnt[s] > 0) { S = s; break; }
        if (S == -1) break;

        if (!buildSubtree(S, cnt)) { cout << "No\n"; return 0; }

        // Recount remaining nodes
        left = 0;
        for (int s = 1; s <= N; ++s) left += cnt[s];
    }

    if ((int)ans.size() != 2 * N) { cout << "No\n"; return 0; }

    cout << "Yes\n" << ans << "\n";
    return 0;
}
