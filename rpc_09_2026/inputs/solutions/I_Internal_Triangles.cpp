// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1000000007;
long long solve(){
    long long n; cin>>n;
    long long a = n;
    long long b = n-1;
    long long c = n-2;
    if(a%2 == 0) a/=2; else if(b%2==0) b/=2; else c/=2;
    if(a%3 == 0) a/=3; else if(b%3==0) b/=3; else c/=3;
    a%=MOD;
    b%=MOD;
    c%=MOD;
    long long ans = (a*b)%MOD;
    ans = (ans*c)%MOD;
    return ans;
}

int main() {
    int t; cin>>t;
    while(t--){
        cout<<solve()<<'\n';
    }
}
