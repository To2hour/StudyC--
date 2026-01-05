#include <algorithm>
#include <climits>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <math.h>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
class Solution {
public:
  int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
    //需要把endWord，beginWord加入到wordList中
    unordered_map<string, vector<string>> map;
    unordered_map<string, bool> visit;
    for (int i = 0; i < wordList.size(); i++) {
      for (int j = i + 1; j < wordList.size(); j++) {
        if (edge(wordList[i], wordList[j])) {
          map[wordList[i]].push_back(wordList[j]);
          map[wordList[j]].push_back(wordList[i]);
        }
      }
    }
    int res = INT_MAX;
    int count = 1;
    auto dfs = [&](auto &&dfs, string str) -> void {
      if (str == endWord) {
        res = min(count, res);
        return;
      }
      if (visit[str]) {
        return;
      }
      visit[str] = true;
      count++;
      for (auto &s : map[str]) {
        dfs(dfs, s);
      }
      visit[str] = false;
      count--;
    };
    dfs(dfs, beginWord);
    return res == INT_MAX ? 0 : res;
  }
  bool edge(const string &a, const string &b) {
    if (a.size() != b.size())
      return false;

    int diff = 0;
    for (size_t i = 0; i < a.size(); i++) {
      if (a[i] != b[i]) {
        diff++;
        if (diff > 1)
          return false; // 提前剪枝
      }
    }
    return diff == 1;
  }
};