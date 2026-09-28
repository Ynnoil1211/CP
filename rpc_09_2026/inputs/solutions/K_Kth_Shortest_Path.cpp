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

vector <ii> g[nax];
int d[nax], p[nax];
void dijkstra(int s, int n){
  forn(i, n) d[i] = inf, p[i] = -1;
  d[s] = 0;
  priority_queue <ii, vector <ii>,greater<ii> > q;
  q.push({0, s});
  while(sz(q)){
    auto [dist, u] = q.top();  q.pop();
    if(dist > d[u]) continue;
    for(auto& [v, w]: g[u]){
      if (d[u] + w < d[v]){
        d[v] = d[u] + w;
        p[v] = u;
        q.push(ii(d[v], v));
      }
    }
  }
}
vi find_path(int t){
  vi path;
  int cur = t;
  while(cur != -1){
    path.pb(cur);
    cur = p[cur];
  }
  reverse(all(path));
  return path;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    ll n,m,k,s,dv;
    cin>>n>>m>>k>>s>>dv;
    forn(i,m){
        ll u,v,w; cin>>u>>v>>w;
        g[u-1].pb({v-1,w});
        g[v-1].pb({u-1,w});

    }
    forn(x,k-1){
        dijkstra(s-1,n);
        auto path = find_path(dv-1);
        int size = sz(path)-1;
        for(int j = 0; j < size; j++){
            int u = path[j];
            int v = path[j+1];
            auto it_u = find_if(all(g[u]), [&](ii e){
                return e.fi==v;
            });
            auto it_v = find_if(all(g[v]), [&](ii e){
                return e.fi==u;
            });
            it_u->se = inf;
            it_v->se = inf;
        }
    }
    dijkstra(s-1,n);
    auto path = find_path(dv-1);
    int size = sz(path)-1;
    cout<<d[dv-1]<<el;
    forn(i, size) cout<<path[i]+1<<" - ";
        cout<<path[size]+1<<el;
    
    
    
}

