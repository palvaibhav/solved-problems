/*
 * https://codeforces.com/contest/803/problem/F
 */

#include<bits/stdc++.h>
using namespace std;

const int MOD=1e9+7;

template <typename A, typename B>
void sub(A& a, B b) {
    a -= b;
    if (a < 0) a += MOD;
}

long long mul(long long a, long long b) {
    return (a * b) % MOD;
}

long long pwr(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

void solve(int test){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++)cin>>a[i];

    int mx=*max_element(a.begin(),a.end());
    vector<int> dp(mx+1),freq(mx+1);
    // dp[g] -> count of subsets with gcd==g

    for(int i=0;i<n;i++)freq[a[i]]++;

    // dp[g] = (2^multiples - 1)  -   sum(dp[i]),2*g <= i <= mx
    for(int g=mx;g>=1;g--){
        int multiples=0;
        for(int i=g;i<=mx;i+=g)multiples+=freq[i];

        dp[g]=pwr(2,multiples);
        sub(dp[g],1);

        for(int i=2*g;i<=mx;i+=g)sub(dp[g],dp[i]);
    }

    cout<<dp[1]<<"\n";
}

signed main(){
#ifdef VPAL
    freopen("in.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    cout<<fixed<<setprecision(10);
    int t=1;
    //cin>>t;
    for(int test=1;test<=t;test++){
        solve(test);
    }
    return 0;
}