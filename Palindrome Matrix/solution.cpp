#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> padre, tam;
    DSU(int n=0): n(n), padre(n), tam(n,1){ iota(padre.begin(), padre.end(), 0); }
    int find(int x){ return padre[x]==x? x : padre[x]=find(padre[x]); }
    void unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return;
        if(tam[a]<tam[b]) swap(a,b);
        padre[b]=a; tam[a]+=tam[b];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int filas,columnas;
    if(!(cin>>filas>>columnas)) return 0;
    vector<string> matriz(filas);
    for(int i=0;i<filas;++i) cin>>matriz[i];

    const int F = filas, COL = columnas;
    auto id = [&](int f,int c){ return f*COL + c; };
    DSU conjuntos(F*COL);

    for(int f=0;f<F;++f){
        int c=0;
        while(c<COL){
            if(matriz[f][c]=='.'){ ++c; continue; }
            int izq=c;
            while(c<COL && matriz[f][c]!='.') ++c;
            int der=c-1;
            int largo = der-izq+1;
            for(int k=0;k<largo/2;++k){
                conjuntos.unite(id(f,izq+k), id(f,der-k));
            }
        }
    }
    
    for(int c=0;c<COL;++c){
        int f=0;
        while(f<F){
            if(matriz[f][c]=='.'){ ++f; continue; }
            int arriba=f;
            while(f<F && matriz[f][c]!='.') ++f;
            int abajo=f-1;
            int alto = abajo-arriba+1;
            for(int k=0;k<alto/2;++k){
                conjuntos.unite(id(arriba+k,c), id(abajo-k,c));
            }
        }
    }

    vector<pair<int,int>> grupos;
    grupos.reserve(F*COL);
    for(int f=0;f<F;++f)
        for(int c=0;c<COL;++c)
            if(matriz[f][c]!='.')
                grupos.emplace_back(conjuntos.find(id(f,c)), matriz[f][c]-'0');

    sort(grupos.begin(), grupos.end(),
         [](const auto& a, const auto& b){
             return a.first<b.first || (a.first==b.first && a.second<b.second);
         });

    vector<int> valor(F*COL, -1);
    int conteo[10];
    for(size_t i=0;i<grupos.size();){
        size_t j=i;
        int raiz = grupos[i].first;
        memset(conteo, 0, sizeof conteo);
        while(j<grupos.size() && grupos[j].first==raiz){
            ++conteo[grupos[j].second];
            ++j;
        }
        int total = int(j-i);
        int mitad = (total+1)/2, acumulado=0, elegido=0;
        for(int d=0; d<=9; ++d){ acumulado += conteo[d]; if(acumulado>=mitad){ elegido=d; break; } }
        valor[raiz] = elegido;
        i=j;
    }
    for(int f=0;f<F;++f){
        for(int c=0;c<COL;++c){
            if(matriz[f][c]=='.') cout<<'.';
            else cout<< char('0' + valor[conjuntos.find(id(f,c))]);
        }
        cout<<"\n";
    }
    return 0;
}