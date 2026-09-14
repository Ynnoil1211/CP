#include <bits/stdc++.h>
#include <unordered_map>

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
void solve(){
   int a,b,c; cin>>a>>b>>c;
   unordered_map<int, int> mp;
   unordered_set<int> st;
   int cnt=0;
   vector<pair<int,int>> vt(a);
   for(int i = 0; i<a; i++){
    if(sz(st)==b) break;
    int t,s; cin>>t>>s;
    vt[i]={t,s};
    mp[s]++;
    if(mp[s]<=c){
      st.insert(t);
    }
   }
   int re = b - sz(st);
   for(int i = 0; i<a; i++){
    if (re<1) break;
    if(st.find(vt[i].first) != st.end()) continue;
    st.insert(vt[i].first);
    re--;
   }

   for(int i = 0; i<a; i++){
    if(st.find(vt[i].first)!=st.end()) cout<<vt[i].first<<endl;
   }


}
int main(){
    int t; t=1;
    while(t--){
        solve();
    }
}