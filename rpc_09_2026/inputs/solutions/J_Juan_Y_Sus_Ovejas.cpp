#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(int i=(int)(n) - 1; i>= 0; --i)
#define fored(i,l,r) for(int i=(int)r; i>= (int)l; --i)
#define pb push_back
#define el '\n'
#define d(x) cout<< #x<< " " << x<<el
#define ri(n) scanf("%d",&n)
#define sz(v) int(v.size())
#define all(v) v.begin(),v.end()

using namespace std;

typedef long long ll;
typedef double ld;
typedef pair<int,int> ii;
typedef pair<ll,ll> pll;
typedef tuple<int, int, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<ld> vd;


const int inf = 1e9;
const int nax = 1e5+200;
const ld pi = acos(-1);
const ld eps= 1e-9;

int dr[] = {1,-1,0, 0,1,-1,-1, 1};
int dc[] = {0, 0,1,-1,1, 1,-1,-1};

ostream& operator<<(ostream& os, const ii& pa) { // DEBUGGING
  return os << "("<< pa.fi << ", " << pa.se << ")";
}

vector<int> tam;
vector<int> dsu;
int total;
int max_tam = 1;

int find(int i){
    return (dsu[i]==i) ? i : dsu[i] = find(dsu[i]);
}

void unir(int i, int j){
    int p_i = find(i);
    int p_j = find(j);
    if(tam[p_i] < tam[p_j]) swap(p_i, p_j);
    if(p_i != p_j){
        dsu[p_j] = p_i;
        tam[p_i] += tam[p_j];
        if(tam[p_i]>max_tam){
            max_tam = tam[p_i];
        }
        total--;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n,p;
    while(cin>>n>>p && (n||p)){
        total = n;
        max_tam = 1;
        dsu.resize(n);
        tam.assign(n,1);
        iota(all(dsu), 0);
        forn(i,p){
            int a,b; cin>>a>>b;
            unir(a-1,b-1);
        }
        cout<<total<<" "<<max_tam<<el;
    }
}

