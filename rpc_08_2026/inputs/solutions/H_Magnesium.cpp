#include <bits/stdc++.h>
#include <unordered_map>

#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(ll i=(ll)(n) - 1; i>= 0; --i)
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
void solve(){
    ll n,y,z; cin>>n>>y>>z;
    vll vt;
    for(ll i = 1; i*i<=n; i++){
        if(n%i==0){
            ll d2 = n/i;
            if(n/i <= z && i<=y) vt.push_back(i);
            if(d2!=i && n/d2 <= z && d2<=y) vt.push_back(d2);
        }
    }
    sort(vt.begin(), vt.end());
    cout<<vt.size()<<endl;
    for(int i = 0; i<vt.size();i++){
        cout<<vt[i]<<endl;
    }
}
int main(){
    int t; t=1;
    while(t--){
        solve();
    }
}