/*
    https://www.interviewbit.com/problems/divisor-sequences/

    Time : O(logN * sqrt(N))
    Space : O(logN)

*/


unordered_map<int, int> dp;

int go(int N) {
    if (N <= 1) return 0;

    if (dp.count(N)) return dp[N];

    int res = 1;

    for (long long d = 2; d * d <= N; d++) {
        if (N % d == 0) {
            int a = d;
            int b = N / a;

            res = max(res, 1 + go(N / a - 1));

            res = max(res, 1 + go(N / b - 1));
        }
    }

    return dp[N] = res;
}

int Solution::solve(int N) {
    return max(go(N), 1 + go(N - 1));
}
