/*
    https://leetcode.com/problems/minimum-number-of-refueling-stops/
    
    Solution 1    
    Time: O(N * logN)
    Space: O(N)
*/

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        
        int n = stations.size();
        
        int fuel = startFuel;
        int pos = 0;
        
        priority_queue<int> refuel;
        
        int stops = 0;        
        
        while (pos < target) {
            
            int canReach = pos + fuel;
            
            for (int i = 0; i < n; i++) {
                if (pos < stations[i][0] && stations[i][0] <= canReach) {
                    refuel.push(stations[i][1]);
                }
            }
            
            pos = canReach;
            
            if (pos < target) {
                if (refuel.empty()) return -1;
                
                stops++;
                fuel = refuel.top();
                refuel.pop();
            }
        }
        
        return stops;
    }
};

/*

    Solution 2
    Time: O(N^2)
    Space: O(N)

*/

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        
        int n = stations.size();
        
        vector<long long> dp(n + 1);
        dp[0] = startFuel;
        // dp[i] = farthest distance we can reach with i stops
        
        for (int i = 0; i < n; i++) {
            for (int stops = i; stops >= 0; stops--) {
                if (dp[stops] >= stations[i][0]) {
                    dp[stops + 1] = max(dp[stops + 1], dp[stops] + stations[i][1]);
                }
            }
        }
        
        for (int stops = 0; stops <= n; stops++) {
            if (dp[stops] >= target) return stops;
        }
        
        return -1;        
    }
};