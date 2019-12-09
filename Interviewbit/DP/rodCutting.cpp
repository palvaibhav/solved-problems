/*

    Time : O(N^3)
    Space : O(N^2)

*/

const long long INF = 1e15;
int n, m;
vector<int> cut, orderOfCuts;
vector<vector<long long>> dp;
 
long long f(int i, int j) {
    if (i > j) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    long long curLength = (j + 1 < m ? cut[j + 1] : n) - (i - 1 >= 0 ? cut[i - 1] : 0);
    long long ans = INF;
    for (int k = i; k <= j; k++) {
        ans = min(ans, f(i, k - 1) + f(k + 1, j));
    }
    ans += curLength;
    return dp[i][j] = ans;
}
 
void trace(int i, int j) {
    if (i > j) return;
    long long ans = INF;
    int at = -1;
    for (int k = i; k <= j; k++) {
        long long nxt = f(i, k - 1) + f(k + 1, j);
        if (nxt < ans) {
            ans = nxt;
            at = k;
        }
    }
    orderOfCuts.push_back(cut[at]);
    trace(i, at - 1);
    trace(at + 1, j);
}
 
vector<int> Solution::rodCut(int A, vector<int> &B) {
    n = A;
    cut = B;
    m = cut.size();
    dp = vector<vector<long long>>(m, vector<long long>(m, -1));
    orderOfCuts = vector<int>();
    sort(cut.begin(),cut.end());
    f(0, m - 1);
    trace(0, m - 1);
    return orderOfCuts;
}