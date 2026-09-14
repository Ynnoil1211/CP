#include <bits/stdc++.h>
#include <unordered_set>
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
void solve() {
    string s; cin>>s;
    const string vowels = "aeiouAEIOU";
    int res = 0, res1 = 0;
    for(int i = 0; i<s.length(); i++){
        if(vowels.find(s[i])!=string::npos) {
            res++;
            res1++;
         }
        if(s[i]=='y') res1++;
    }
    cout<<res<<" "<<res1<<endl;
}

// --- Main ---
int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   
    int t = 1;
    // Read number of test cases
    //cin >> t;
   
    while (t--) {
        solve();
    }
   
    return 0;
}// Source: https://usaco.guide/general/io
