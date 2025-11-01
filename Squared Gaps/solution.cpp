#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ll128 = __int128_t;

struct LinearFunction {
    ll slope, intercept;             
    inline ll evaluate(ll x) const { return (ll)((ll128)slope * x + intercept); }
};

struct ConvexHullTrick {
    deque<LinearFunction> functions;
    static bool shouldRemove(const LinearFunction& f1, const LinearFunction& f2, const LinearFunction& f3){
        ll128 numerator = (ll128)(f3.intercept - f1.intercept) * (f1.slope - f2.slope);
        ll128 denominator = (ll128)(f2.intercept - f1.intercept) * (f1.slope - f3.slope);
        return numerator <= denominator;
    }
    inline void insert(LinearFunction func){
        while(functions.size() >= 2 && shouldRemove(functions[functions.size()-2], functions.back(), func)) 
            functions.pop_back();
        functions.push_back(func);
    }
    inline ll getMax(ll x){
        while(functions.size() >= 2 && functions[0].evaluate(x) <= functions[1].evaluate(x)) 
            functions.pop_front();
        return functions.front().evaluate(x);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int len1, len2;
    if(!(cin >> len1)) return 0;
    string sequence1, sequence2;
    cin >> sequence1 >> len2 >> sequence2;
    ll match_score, mismatch_score, gap_penalty;
    cin >> match_score >> mismatch_score >> gap_penalty; 

    string str1 = sequence1, str2 = sequence2;
    int rows = len1, cols = len2;
    if(rows < cols){ swap(str1,str2); swap(rows,cols); }

    auto score = [&](char c1, char c2)->ll{ return c1==c2 ? match_score : mismatch_score; };

    const ll NEG_INF = (ll)-4e18;

    vector<ll> align_prev(cols+1, NEG_INF), gapX_prev(cols+1, NEG_INF), gapY_prev(cols+1, NEG_INF);
    vector<ll> align_curr (cols+1, NEG_INF), gapX_curr (cols+1, NEG_INF), gapY_curr (cols+1, NEG_INF);

    align_prev[0] = 0;
    gapX_prev[0] = gapY_prev[0] = NEG_INF;
    for(int j=1;j<=cols;++j){
        align_prev[j] = gapY_prev[j] = NEG_INF;
        gapX_prev[j] = (ll)j*j*gap_penalty;          
    }

    vector<ConvexHullTrick> column_ch(cols+1);
    for(int j=0;j<=cols;++j){
        ll max_val = max(align_prev[j], gapX_prev[j]);         
        column_ch[j].insert({0, max_val});                       
    }

    for(int i=1;i<=rows;++i){
        align_curr[0] = gapX_curr[0] = NEG_INF;
        gapY_curr[0] = (ll)i*i*gap_penalty;

        ConvexHullTrick row_ch;                                
        ll row_max = max(align_curr[0], gapY_curr[0]);         
        row_ch.insert({0, row_max});                          

        for(int j=1;j<=cols;++j){
            ll best_previous = max({align_prev[j-1], gapX_prev[j-1], gapY_prev[j-1]});
            align_curr[j] = best_previous + score(str1[i-1], str2[j-1]);

            ll gapX_value = gap_penalty*(ll)j*j + row_ch.getMax(j);
            ll gapY_value = gap_penalty*(ll)i*i + column_ch[j].getMax(i);

            gapX_curr[j] = gapX_value;
            gapY_curr[j] = gapY_value;

            ll max_row = max(align_curr[j], gapY_curr[j]);
            row_ch.insert({ -2*gap_penalty*(ll)j, max_row + gap_penalty*(ll)j*j });

            ll max_col = max(align_curr[j], gapX_curr[j]);
            column_ch[j].insert({ -2*gap_penalty*(ll)i, max_col + gap_penalty*(ll)i*i });
        }
        align_prev.swap(align_curr);
        gapX_prev.swap(gapX_curr);
        gapY_prev.swap(gapY_curr);
        fill(align_curr.begin(), align_curr.end(), NEG_INF);
        fill(gapX_curr.begin(), gapX_curr.end(), NEG_INF);
        fill(gapY_curr.begin(), gapY_curr.end(), NEG_INF);
    }

    cout << max({align_prev[cols], gapX_prev[cols], gapY_prev[cols]}) << '\n';
    return 0;
}