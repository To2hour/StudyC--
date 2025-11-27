#include <algorithm>
#include <climits>
#include <cstddef>
#include <iostream>
#include <math.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
// leecode 216. 组合总和 III
class Solution {
public:
  vector<vector<int>> combinationSum3(int k, int n) {
    vector<int> temp(9, 1);
    vector<int> res;
    vector<vector<int>> rres;
    for (int i = 0; i < 9; i++) {
      temp[i] = i + 1;
    }
    auto dfs = [&](auto &&dfs, int value, int index) -> void {
      if (res.size() == k) {
        if (value == n) {
          rres.push_back(res);
        }
        return;
      }
      for (int i = index; i <= 8; i++) {
        if (value >= n) {
          continue;
        }
        value += temp[i];
        res.push_back(temp[i]);
        dfs(dfs, value, i + 1);
        value -= temp[i];
        res.pop_back();
      }
    };
    dfs(dfs, 0, 0);
    return rres;
  }
};
//
class Solution2 {
public:
  vector<vector<int>> res;
  vector<int> path;
  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end());
    auto dfs = [&](auto &&dfs, int &value, int index) -> void {
      if (target < value) {
        return;
      }
      if (target == value) {
        res.push_back(path);
      }
      for (int i = index; i < candidates.size(); i++) {
        if (i < candidates.size() - 1 && candidates[i] == candidates[i + 1]) {

          continue;
        }
        path.push_back(candidates[i]);
        value += candidates[i];
        dfs(dfs, value, i);
        path.pop_back();
        value -= candidates[i];
      }
    };
    int value = 0;
    dfs(dfs, value, 0);
    return res;
  }
};

class Solution3 {
public:
  vector<vector<string>> res;
  vector<string> path;
  vector<vector<string>> partition(string s) {
    auto dfs = [&](auto &&dfs, int startIndex) -> void {
      if (startIndex == s.size()) {
        return;
      }
      for (int i = startIndex; i < s.size(); i++) {
        string temp = s.substr(startIndex, i - startIndex + 1);
        if (huiWen(temp)) {
          path.push_back(temp);
          dfs(dfs, i + 1);
          path.pop_back();
        }
      }
    };
  }
  bool huiWen(string s) {
    int left = 0;
    int right = s.size() - 1;
    while (left < right) {
      if (s[left] != s[right]) {
        return false;
      }
      left++;
      right--;
    }
    return true;
  }
};

// 78. 子集
class Solution4 {
public:
  vector<int> path;
  vector<vector<int>> res;
  vector<vector<int>> subsets(vector<int> &nums) {
    auto dfs = [&](auto &&dfs, int index) -> void {
      res.push_back(path);
      if (index == nums.size()) {
        return;
      }
      for (int i = index; i < nums.size(); i++) {
        path.push_back(nums[i]);
        dfs(dfs, i + 1);
        path.pop_back();
      }
    };
    dfs(dfs, 0);
    return res;
  }
};

class Solution5 {
public:
  vector<int> path;

  vector<vector<int>> res;
  vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    vector<bool> used = vector<bool>(nums.size(), false);
    sort(nums.begin(), nums.end());
    auto dfs = [&](auto &&dfs, int index) -> void {
      res.push_back(path);
      if (index == nums.size()) {
        return;
      }
      for (int i = index; i < nums.size(); i++) {
        if (i > 0 && nums[i] == nums[i - 1] && !used[i]) {
          continue;
        }
        path.push_back(nums[i]);
        dfs(dfs, i + 1);
        path.pop_back();
      }
    };
    dfs(dfs, 0);
    return res;
  }
};
//递增子序列
class Solution6 {
public:
  vector<vector<int>> res;
  vector<int> path;
  vector<vector<int>> findSubsequences(vector<int> &nums) {
    auto dfs = [&](auto &&dfs, int pre, int startIndex) -> void {
      if (startIndex == nums.size()) {
        if (path.size() >= 2) {
          res.push_back(path);
        }
        return;
      }
      //不选
      //对于两个相同的值，比如223。如果第一个2不选，那可以选择第二个2,可以出现23。
      //而如果选择了第一个2，那第二个2必须选，否则会重复出现。
      if (pre != nums[startIndex]) {
        dfs(dfs, pre, startIndex + 1);
      }
      //选
      //这里如果不加条件，会导致path中出现不对的数据。
      if (pre <= nums[startIndex]) {
        path.push_back(nums[startIndex]);
        dfs(dfs, nums[startIndex], startIndex + 1);
        path.pop_back();
      }
    };
    dfs(dfs, INT_MIN, 0);
    return res;
  }
};
//全排列，无重复的那种
class Solution7 {
public:
  vector<vector<int>> ans;
  vector<int> path;

  vector<vector<int>> permute(vector<int> &nums) {
    vector<bool> used = vector<bool>(nums.size(), false);
    auto dfs = [&](auto &&dfs) -> void {
      if (path.size() == nums.size()) {
        ans.push_back(path);
        return;
      }
      for (int i = 0; i < nums.size(); i++) {
        if (!used[i]) {
          used[i] = true;
          path.push_back(nums[i]);
          dfs(dfs);
          used[i] = false;
          path.pop_back();
        }
      }
    };
    dfs(dfs);
    return ans;
  }
};
//全排列，有重复的那种
class Solution8 {
public:
  vector<vector<int>> ans;
  vector<int> path;
  vector<vector<int>> permuteUnique(vector<int> &nums) {
    vector<bool> used = vector<bool>(nums.size(), false);
    sort(nums.begin(),nums.end());
    auto dfs = [&](auto &&dfs) -> void {
      if (path.size() == nums.size()) {
        ans.push_back(path);
        return;
      }
      for (int i = 0; i < nums.size(); i++) {
        //当i>0，且上一个没有被用过的情况下，相等就跳过。
        if (i > 0 && !used[i-1] && nums[i] == nums[i - 1]) {
          continue;
        }
        if (!used[i]) {
          used[i] = true;
          path.push_back(nums[i]);
          dfs(dfs);
          used[i] = false;
          path.pop_back();
        }
      }
    };
    dfs(dfs);
    return ans;
  }
};
int main() {
  Solution8 *sol = new Solution8;
  vector<int> nums{1, 1, 2};
  sol->permuteUnique(nums);
  return 0;
}
