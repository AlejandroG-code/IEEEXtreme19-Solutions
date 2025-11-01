#include <bits/stdc++.h>
using namespace std;

// pattern: 1,1,2,0,1,2
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if(!(cin >> T)) return 0;
    while (T--) {
        string s; 
        cin >> s;
        int n = (int)s.size();

        struct Chain { array<int,6> idx; int len = 0; };
        vector<Chain> chains; chains.reserve(n/6 + 4);
        vector<array<int,6>> done; done.reserve(n/6);

        // queues of ids per "next needed" state
        // state 0..5 -> need 1,1,2,0,1,2; state 6 = finished
        deque<int> wait[6];

        auto start_chain = [&](int pos){
            int id = (int)chains.size();
            chains.push_back({});
            chains[id].idx[chains[id].len++] = pos; // took first 1
            wait[1].push_back(id);                  // next need: 1
        };
        auto advance = [&](int id, int pos, int next){
            chains[id].idx[chains[id].len++] = pos;
            if(next < 6) wait[next].push_back(id);
            else done.push_back(chains[id]); // completed
        };

        for (int i = 0; i < n; ++i){
            int pos = i+1;
            char c = s[i];

            if (c == '1'){
                if (!wait[4].empty()){      // prefer most advanced: ...0 -> need 1
                    int id = wait[4].front(); wait[4].pop_front();
                    advance(id, pos, 5);     // next need: 2 (final)
                } else if (!wait[1].empty()){ // then: after first 1 -> need 1
                    int id = wait[1].front(); wait[1].pop_front();
                    advance(id, pos, 2);     // next need: 2
                } else {
                    start_chain(pos);        // start new subsequence
                }
            } else if (c == '2'){
                if (!wait[5].empty()){       // finish if possible
                    int id = wait[5].front(); wait[5].pop_front();
                    advance(id, pos, 6);     // done
                } else if (!wait[2].empty()){ // after 1,1 -> need 2
                    int id = wait[2].front(); wait[2].pop_front();
                    advance(id, pos, 3);     // next need: 0
                } else {
                    // input guaranteed fortunate; unreachable
                }
            } else { // c == '0'
                if (!wait[3].empty()){       // after 1,1,2 -> need 0
                    int id = wait[3].front(); wait[3].pop_front();
                    advance(id, pos, 4);     // next need: 1
                } else {
                    // unreachable for valid input
                }
            }
        }

        // Only print completed subsequences
        for (auto &ch : done){
            cout << ch.idx[0] << ' ' << ch.idx[1] << ' ' << ch.idx[2] << ' '
                 << ch.idx[3] << ' ' << ch.idx[4] << ' ' << ch.idx[5] << '\n';
        }
    }
    return 0;
}
