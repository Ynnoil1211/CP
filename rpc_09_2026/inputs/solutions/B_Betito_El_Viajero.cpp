#include <bits/stdc++.h>
using namespace std;
// --- Type Aliases ---
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

// --- Constants ---
const int MOD = 1e9 + 7;
const ll INF = 1e18;
// --- Solution ---
int fi, cl; 
int dfs(vector<string> &vt, int bx, int by){
    if(bx>=fi || by>=cl || bx<0 || by<0 || vt[bx][by]=='#') {
        return 0;
    }
    vt[bx][by]='#';
    return 1 + dfs(vt, bx+1, by) + dfs(vt, bx, by+1) + dfs(vt, bx-1, by) + dfs(vt,bx, by-1);
}

void solve() {
    while (cin >> fi >> cl && (fi != 0 || cl != 0)) {
        vector<string> vt(fi);
        ll res = 0;
        int bx, by;
        for(int i = 0; i<fi; i++){
            cin>>vt[i];
            for(int j = 0; j<cl; j++){
                if(vt[i][j]=='*'){
                    bx=i;
                    by=j;
                }
            }
       }
       cout<<dfs(vt,bx,by)<<endl;
    }
}

// --- Main ---
int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   
    int t = 1;
    // Read number of test cases
    //cin >> t;
   
    for(int i = 0; i<t; i++){
        solve();
    }
   
    return 0;
}

