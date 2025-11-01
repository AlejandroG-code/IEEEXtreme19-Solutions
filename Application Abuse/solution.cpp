#include <bits/stdc++.h>
using namespace std;

struct Rules { int agent=-1, ip=-1, pdf=-1, session=-1, crawl=-1; };

static inline string trim(string s){
    size_t i = s.find_first_not_of(" \t\r\n");
    if(i==string::npos) return "";
    size_t j = s.find_last_not_of(" \t\r\n");
    return s.substr(i, j-i+1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string settings; if(!getline(cin, settings)) return 0;
    Rules R;
    {
        stringstream ss(settings); string tok;
        while(getline(ss, tok, ',')){
            tok = trim(tok); if(tok.empty()) continue;
            auto p = tok.find('='); if(p==string::npos) continue;
            string k = trim(tok.substr(0,p));
            int v = stoi(trim(tok.substr(p+1)));
            if(k=="agent") R.agent=v;
            else if(k=="ip") R.ip=v;
            else if(k=="pdf") R.pdf=v;
            else if(k=="session") R.session=v;
            else if(k=="crawl") R.crawl=v;
        }
    }

    string header; getline(cin, header);
    vector<string> order;
    { string cur; for(char c: header){ if(c==','){ order.push_back(trim(cur)); cur.clear(); } else cur.push_back(c);} order.push_back(trim(cur)); }

    struct DayStat {
        unordered_set<string> agents, ips, sessions;
        int pdfCount = 0;
        vector<long long> pdfSeq;
    };
    unordered_map<string, unordered_map<string, DayStat>> mp;

    auto parse_line = [&](const string& line){
        vector<string> vals; vals.reserve(order.size());
        size_t i=0, n=line.size();
        for(const string& f: order){
            while(i<n && line[i]==' ') ++i;
            if(i>=n){ vals.push_back(""); continue; }
            if(f=="Date"){
                if(line[i]=='['){ size_t j=line.find(']',i+1); vals.push_back(j==string::npos? "" : line.substr(i+1,j-(i+1))); i=(j==string::npos? n:j+1); }
                else { size_t j=i; while(j<n && line[j]!=' ') ++j; vals.push_back(line.substr(i,j-i)); i=j; }
            }else if(f=="Request" || f=="User Agent" || f=="Session Cookie"){
                if(line[i]=='"'){ size_t j=line.find('"',i+1); vals.push_back(j==string::npos? "" : line.substr(i+1,j-(i+1))); i=(j==string::npos? n:j+1); }
                else { size_t j=i; while(j<n && line[j]!=' ') ++j; vals.push_back(line.substr(i,j-i)); i=j; }
            }else{
                size_t j=i; while(j<n && line[j]!=' ') ++j; vals.push_back(line.substr(i,j-i)); i=j;
            }
            while(i<n && line[i]==' ') ++i;
        }
        return vals;
    };

    string line;
    while(getline(cin,line)){
        if(trim(line).empty()) continue;
        auto vals = parse_line(line);

        string host, ip, id, date, req, ua, cookie; int status=0;
        for(size_t k=0;k<order.size();++k){
            const string& f=order[k]; const string& v=vals[k];
            if(f=="Host") host=v;
            else if(f=="Client IP") ip=v;
            else if(f=="Id") id=v;
            else if(f=="Date") date=v;
            else if(f=="Request") req=v;
            else if(f=="HTTP Status") status = v.empty()?0:stoi(v);
            else if(f=="User Agent") ua=v;
            else if(f=="Session Cookie") cookie=v;
        }
        if(status!=200) continue;
        if(id=="-" || id.empty()) continue;

        string day = date; auto p = day.find(':'); if(p!=string::npos) day = day.substr(0,p);
        auto &st = mp[id][day];
        if(!ua.empty()) st.agents.insert(ua);
        if(!ip.empty() && ip!="-") st.ips.insert(ip);
        if(!cookie.empty() && cookie!="-") st.sessions.insert(cookie);

        size_t pos = req.find("GET ");
        if(pos!=string::npos){
            size_t sp = req.find(' ', pos+4);
            string path = (sp==string::npos? string(): req.substr(pos+4, sp-(pos+4)));
            const string pref="/document/";
            if(path.compare(0,pref.size(),pref)==0){
                size_t q=pref.size(), dot=path.find('.',q);
                if(dot!=string::npos && path.substr(dot)==".pdf"){
                    string num=path.substr(q,dot-q); bool ok=!num.empty();
                    for(char c: num) if(!isdigit((unsigned char)c)){ ok=false; break; }
                    if(ok){ st.pdfCount++; st.pdfSeq.push_back(stoll(num)); }
                }
            }
        }
    }

    struct Vi{ string id,type; int val; };
    vector<Vi> out;

    for(auto &p1: mp){
        const string &id = p1.first;
        int bestAgent=0,bestIp=0,bestPdf=0,bestSession=0,bestCrawl=0;
        for(auto &p2: p1.second){
            const auto &st = p2.second;
            bestAgent = max(bestAgent, (int)st.agents.size());
            bestIp    = max(bestIp,    (int)st.ips.size());
            bestPdf   = max(bestPdf,   st.pdfCount);
            bestSession = max(bestSession, (int)st.sessions.size());
            int best=0, cur=0; long long prev = LLONG_MIN/4;
            for(long long x: st.pdfSeq){
                if(cur==0) cur=1;
                else if(x==prev+1) ++cur;
                else cur=1;
                best = max(best, cur);
                prev = x;
            }
            bestCrawl = max(bestCrawl, best);
        }
        if(R.agent!=-1   && bestAgent  >= R.agent)   out.push_back({id,"agent",  bestAgent});
        if(R.crawl!=-1   && bestCrawl  >= R.crawl)   out.push_back({id,"crawl",  bestCrawl});
        if(R.ip!=-1      && bestIp     >= R.ip)      out.push_back({id,"ip",     bestIp});
        if(R.pdf!=-1     && bestPdf    >= R.pdf)     out.push_back({id,"pdf",    bestPdf});
        if(R.session!=-1 && bestSession>= R.session) out.push_back({id,"session",bestSession});
    }

    if(out.empty()){ cout<<"N/A\n"; return 0; }

    sort(out.begin(), out.end(), [](const Vi&a,const Vi&b){
        if(a.id!=b.id) return a.id<b.id;
        return a.type<b.type;
    });
    for(auto &v: out) cout<<v.id<<' '<<v.type<<'='<<v.val<<"\n";
    return 0;
}