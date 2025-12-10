#include <algorithm>
#include <cstddef>
#include <iostream>
#include <math.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
/**
Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
right(right) {}
};
 */
class Solution {
public:
  struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
  };
  int sumOfLeftLeaves(TreeNode *root) {
    auto dfs = [&](auto &&dfs, TreeNode *node, int &num) -> int {
      if (!node) {
        return num;
      }
      if (node->left != NULL && node->left->left == NULL &&
          node->left->right == NULL) {
        num += node->left->val;
      }
      dfs(dfs, node->right, num);
      dfs(dfs, node->left, num);
    };
    int res = 0;
    return dfs(dfs, root, res);
  };
  bool hasPathSum(TreeNode *root, int targetSum) {
    auto dfs = [&](auto &&dfs, TreeNode *node, int res) -> bool {
      if (!node) {
        return false;
      }
      if (!node->left && !node->right) {
        res += node->val;
        if (res == targetSum) {
          return true;
        } else {
          return false;
        }
      }
      dfs(dfs, node->left, res + node->val);
      dfs(dfs, node->right, res + node->val);
    };
    return dfs(dfs, root, 0);
  };

  int rob(TreeNode *root) {
    vector<pair<int, int>> dp;
    auto dfs = [&](auto &&dfs, TreeNode *node) -> vector<pair<int, int>> {
      if (node == nullptr) {
        return vector<pair<int, int>>{{0, 0}};
      }
      vector<pair<int, int>> left = dfs(node->left);
      vector<pair<int, int>> right = dfs(node->right);
      //偷当前的
      int rob = node->val + left.front().first + right.front().first;
      //不偷当前的
      int nonrob = max(left.front().first, left.front().second) +
                   max(right.front().first, right.front().second);
      return vector<pair<int, int>>{{rob, nonrob}};
      ;
    };
    dfs(root);
    return max(dp.front().first,dp.front().second);
  }
};