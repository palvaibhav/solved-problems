/*
    https://leetcode.com/problems/dungeon-game/

    Time: O(N*M)
    Space: O(N*M)

*/


const int INF = 1e7;

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int n = dungeon.size();        
        int m = dungeon[0].size();
        
        vector<vector<int>> energy(n + 1, vector<int>(m + 1, INF));
        energy[n][m - 1] = energy[n - 1][m] = 1;
        
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                energy[i][j] = max(1, min(energy[i + 1][j], energy[i][j + 1]) - dungeon[i][j]);
            }
        }
        
        return energy[0][0];
    }
};