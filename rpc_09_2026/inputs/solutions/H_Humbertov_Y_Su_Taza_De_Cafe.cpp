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
double obj;
double r,R,h; 
//retorna el volument
double bs(double mid){
    double newR = ((R-r) * mid/h + r);
    return mid * (newR*newR + r*r + newR*r);
}
//R = (R-r) * x/h + r
void solve() {
    cin>>r>>R>>h;
    obj = h*(R*R + r*r + R*r)/2;
    double l=0,r=h;
    double res=0;
    for(int i = 0; i<100; i++){
        double mid = (l+r)/2;
        if(bs(mid)>obj){
            r = mid;
        } else{
            l=mid;
            res=mid;
        }
    }
    cout<<fixed<<setprecision(9)<<res<<endl;
}

// --- Main ---
int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   
    int t = 1;
    // Read number of test cases
    cin >> t;
   
    for(int i = 0; i<t; i++){
        solve();
    }
   
    return 0;
}

