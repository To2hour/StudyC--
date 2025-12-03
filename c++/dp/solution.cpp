#include <algorithm>
#include <climits>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <math.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
//斐波那契
class Solution {
public:
  int fib(int n) {
    if (n <= 1) {
      return n;
    }
    //确认dp公式
    //确认dp中下标的含义
    //初始化dp
    //开始for
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
      dp[i] = dp[i - 2] + dp[i - 1];
    }
    return dp[n];
  }
};
//爬楼梯
class Solution2 {
public:
  int climbStairs(int n) {
    if (n <= 2) {
      return n;
    }
    vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; i++) {
      dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
  }
};
//最小代价爬楼梯
class Solution3 {
public:
  int minCostClimbingStairs(vector<int> &cost) {
    if (cost.size() <= 2) {
      return 0;
    }
    vector<int> dp(cost.size());
    dp[0] = cost[0];
    dp[1] = min(cost[0], cost[1]);
    for (int i = 2; i < cost.size(); i++) {
      dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]);
    }
    return min(dp[cost.size() - 1], dp[cost.size() - 2]);
  }
};
//走网格有多少路径
class Solution4 {
public:
  int uniquePaths(int m, int n) {
    if ((m <= 2 && n < 2) || (m < 2 && n <= 2)) {
      return 1;
    }
    // 格式：vector<vector<int>> 数组名(行数, vector<int>(列数, 初始值));
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 1));
    for (int i = 2; i <= m; i++) {
      for (int j = 2; j <= n; j++) {
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      }
    }
    return dp[m][n];
  }
  //尝试1维数组
  int uniquePaths2(int m, int n) {
    if ((m <= 2 && n < 2) || (m < 2 && n <= 2)) {
      return 1;
    }
    // 格式：vector<vector<int>> 数组名(行数, vector<int>(列数, 初始值));
    vector<int> dp(m + 1, 1);
    for (int i = 2; i <= m; i++) {
      for (int j = 2; j <= n; j++) {
        dp[j] += dp[j - 1];
      }
    }
    return dp[m];
  }
};

class Solution5 {
public:
  //二维写法
  int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
    int rows = obstacleGrid.size();
    if (rows == 0)
      return 0;
    int cols = obstacleGrid[0].size();
    if (cols == 0)
      return 0;
    // 2. 初始化dp数组：rows行cols列，全0
    vector<vector<int>> dp(rows, vector<int>(cols, 0));
    for (int i = 0; i < rows; i++) {
      if (obstacleGrid[i][0] == 1) {
        break;
      }
      dp[i][0] = 1;
    }
    for (int i = 0; i < cols; i++) {
      if (obstacleGrid[0][i] == 1) {
        break;
      }
      dp[0][i] = 1;
    }
    for (int i = 1; i < obstacleGrid.size(); i++) {
      for (int j = 1; j < obstacleGrid[i].size(); j++) {
        if (obstacleGrid[i][j] == 0) {
          dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
      }
    }
    return dp[rows - 1][cols - 1];
  }
  //一维写法
  int uniquePathsWithObstacles2(vector<vector<int>> &obstacleGrid) {
    vector<int> dp(obstacleGrid[0].size(), 0);
    dp[0] = (obstacleGrid[0][0] == 0 ? 1 : 0);
    for (int i = 0; i < obstacleGrid.size(); i++) {
      for (int j = 0; j < obstacleGrid[i].size(); j++) {
        if (obstacleGrid[i][j] == 1) {
          dp[j] = 0;
        }
        if (j > 0 && obstacleGrid[i][j] == 0) {
          dp[j] += dp[j - 1];
        }
      }
    }
    return dp[dp.size() - 1];
  }
};
// 整数拆分
class Solution6 {
public:
  int integerBreak(int n) {
    if (n <= 3) {
      return n - 1;
    }
    vector<int> dp(n + 1, 0);
    dp[1] = 1;
    dp[2] = 1;
    dp[3] = 2;
    for (int i = 4; i <= n; i++) {
      for (int j = 2; j < i; j++) {
        cout << i << "个=" << dp[i] << endl;
        cout << j << "个=" << j * dp[i - j];
        dp[i] = max(dp[i], j * dp[i - j]);
      }
    }
    return dp[n];
  }
};
// 01背包开始。有个好文章
// https://juejin.cn/post/7531888188774334499
//拆成等和子集
class Solution7 {
public:
  bool canPartition(vector<int> &nums) {
    int amount = 0;
    for (int num : nums) {
      amount += num;
    }
    if (amount & 1) {
      return false;
    }
    int target = amount / 2;
    vector<int> dp(target + 1, 0);
    for (int i = 0; i < nums.size(); i++) {
      for (int j = target; j >= nums[i]; j--) {
        dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
      }
    }
    return dp[target - 1] == target;
  }
};
// 1049. 最后一块石头的重量 II
class Solution8 {
public:
  int lastStoneWeightII(vector<int> &stones) {
    int amount = 0;
    for (int num : stones) {
      amount += num;
    }
    if (amount & 1) {
      return false;
    }
    int target = amount / 2;
    vector<int> dp(target + 1, 0);
    for (int i = 0; i < stones.size(); i++) {
      for (int j = target; j >= stones[i]; j--) {
        dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
      }
    }
    return amount - 2 * dp[target];
  }
};
// 01和

class Solution9 {
public:
  // 没活的回溯写法
  int findTargetSumWays(vector<int> &nums, int target) {
    int res = 0;
    auto sum = [&](auto &&sum, int len, int amout) -> void {
      if (len == nums.size()) {
        if (amout == target) {
          res += 1;
        }
        return;
      }
      sum(sum, len + 1, amout - nums[len]);
      sum(sum, len + 1, amout + nums[len]);
    };
    sum(sum, 0, 0);
    return res;
  }
  // 有活的dp写法
  int findTargetSumWays1(vector<int> &nums, int target) {
    // left + right=nums;
    // left - right = target;
    // left = (nums+target)/2|| nums + (target - nums) /
    // 2。如果除不尽，说明不可能可以成，返回0。
    // dp为容量为j的情况下，可以放多少的次数。
    // dp[j] =
    // (这一次不选他能放满的次数)dp[j]+(这一次选他能放满的次数)dp[j-nums[i]],需要dp[0]=1，否则没办法递增。
    // 有点像走格子，当前格子的走法是从上面来+从左边来。
    // 从后往前遍历是因为每个数据只能选一次
    int amount = 0;
    for (int n : nums) {
      amount += n;
    }
    int left = amount + (target - amount) / 2;
    if (2 * left != target) {
      return 0;
    }
    vector<int> dp(left + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < nums.size(); i++) {
      for (int j = dp.size(); j >= nums[i]; j--) {
        dp[j] += dp[j - nums[i]];
      }
    }
    return dp.back();
  }
};
// 完全背包
class Solution10 {
public:
  int change(int amount, vector<int> &coins) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < coins.size(); i++) {
      for (int j = coins[i]; j < dp.size(); j++) {
        dp[j] += dp[j - coins[i]];
      }
    }
    return dp.back();
  }
};

class Solution11_Combination {
public:
  int change(int amount, vector<int> &coins) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;

    cout << "\n---- 组合版(不考虑顺序) DP变化 ----\n";
    for (int i = 0; i < coins.size(); i++) {
      for (int j = coins[i]; j <= amount; j++) {
        dp[j] += dp[j - coins[i]];
      }

      // 打印每轮硬币后的 dp
      cout << "使用硬币 " << coins[i] << " 后: ";
      for (auto v : dp)
        cout << setw(3) << v << " ";
      cout << endl;
    }

    return dp[amount];
  }
};

class Solution11_Permutation {
public:
  int change(int amount, vector<int> &coins) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    cout << "\n---- 排列版本DP变化 ----\n";
    for (int j = 1; j <= amount; j++) {
      for (int i = 0; i < coins.size(); i++) {
        if (j >= coins[i]) {
          //不选coins为dp[j]，选当前硬币为dp[j-coins[i]],如果容量小于当前硬币，那就选不了当前硬币。
          //至于排列问题。当容量=3的时候，我先选第0个，值是1。这样就是dp[3]=dp[2]，里面选的1和dp[2]的值，是{1,1,1},{1,2}
          // 然后我选第1个数字，值是2.我dp[3]此时不选2，是前面的{1,1,1},{1,2}，选2，就得加上dp[1]，dp[1]={1}，所以这个时候
          //的dp[3]就是{2,1}，最后加起来就是{1,1,1},{1,2},{2,1}
          dp[j] = dp[j] + dp[j - coins[i]];
        } /*所以为了方便理解，其实还可以加*/ else {
          dp[j] = dp[j];
        }
      }
      for (auto v : dp)
        cout << setw(3) << v << " ";
      cout << endl;
    }

    return dp[amount];
  }
};
//组合总数4
class Solution12 {
public:
  int combinationSum4(vector<int> &nums, int target) {
    vector<int> dp(target + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= target; i++) {
      for (int j = 0; j < nums.size(); j++) {
        if (i >= nums[j]) {
          dp[i] += dp[i - nums[j]];
        }
      }
    }
    return dp.back();
  }
};
// 超级爬楼梯，n个楼梯，1次可以爬m层
class Solution13 {
public:
  int climbStairs(int n, int m) {
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (i >= j) {
          //不选爬j层能到达i层的次数+选择爬j层到底i层的次数
          dp[i] += dp[i - j];
        }
      }
    }
    return dp.back();
  }
};

//零钱兑换
class Solution14 {
public:
  int coinChange(vector<int> &coins, int amount) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 0;
    for (int i = 0; i < coins.size(); i++) {
      for (int j = coins[i]; j <= amount; j++) {
        dp[j] = min(dp[j - coins[i]] + 1, dp[j]);
      }
    }
    return dp.back() == 0 ? -1 : dp.back();
  }
};
int main() {
  vector<int> coins = {1, 2};
  int amount = 3;

  Solution11_Combination s1;
  Solution11_Permutation s2;

  cout << "coins = {1, 2}, amount = " << amount << endl;

  int res1 = s1.change(amount, coins);
  cout << "\n组合结果 = " << res1 << "（顺序不重要，例如 1+2 和 2+1 算一种）\n";

  int res2 = s2.change(amount, coins);
  cout << "\n排列结果 = " << res2 << "（顺序重要，例如 1+2 和 2+1 算两种）\n";

  return 0;
}