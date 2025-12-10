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
//邻接矩阵版本
class GraphAdjMat {

public:
  vector<int> vertices;       //顶点
  vector<vector<int>> adjMat; //邻接关系
  /* 构造方法 */
  GraphAdjMat(const vector<int> &vertices, const vector<vector<int>> &edges) {
    for (auto vert : vertices) {
      addVertices(vert);
    }
    for (auto edge : edges) {
      editEdge(*edge.begin(), edge.back(), false);
    }
  }
  //增加顶点
  void addVertices(const int vert) {
    int size = getSize();
    vertices.push_back(vert);
    vector<int> rows(size, 0);
    adjMat.push_back(rows);
    for (auto &col : adjMat) {
      col.push_back(0);
    }
  }
  //删除顶点
  void deleteVertices(const int vert) {
    //学习用，不做存在性校验
    //找到迭代器
    auto it = find(vertices.begin(), vertices.end(), vert);
    if (it != vertices.end()) {
      //根据迭代器获取索引
      int index = it - vertices.begin();
      //先删横的
      adjMat.erase(adjMat.begin() + index);
      for (auto &row : adjMat) {
        //再删竖的
        row.erase(row.begin() + index);
      }
      vertices.erase(it);
    }
  }
  // i,j对应值
  void editEdge(int from, int to, bool isDelete) {
    int fromIndex = -1;
    int toIndex = -1;
    //不做合法性校验
    for (int i = 0; i < getSize(); i++) {
      if (vertices[i] == from) {
        fromIndex = i;
      }
      if (vertices[i] == to) {
        toIndex = i;
      }
    }
    if (fromIndex == -1 || toIndex == -1) {
      return;
    }
    if (isDelete) {
      adjMat[fromIndex][toIndex] = 0;
      adjMat[toIndex][fromIndex] = 0;
    } else {
      adjMat[fromIndex][toIndex] = 1;
      adjMat[toIndex][fromIndex] = 1;
    }
  }
  int getSize() { return this->vertices.size(); }
};

class GraphAdjList {
public:
  vector<int> vertices;
  unordered_map<int, vector<int>> adjMat;

  GraphAdjList(const vector<int> &verts,
               const unordered_map<int, vector<int>> &edges)
      : vertices(verts), adjMat(edges) {}

  void addVertex(int v) {
    if (adjMat.count(v) == 0) {
      adjMat[v] = {};
      vertices.push_back(v);
    }
  }
  void deleteVertex(int v) {
    if (adjMat.count(v) == 0) {
      return;
    }
    adjMat.erase(adjMat.find(v));
    for (auto &a : adjMat) {
      auto &list = a.second;
      auto it = std::find(list.begin(), list.end(), v);
      if (it != list.end()) {
        list.erase(it);
      }
    }
  }
  void addEdge(int from, int to) {
    if (!exists(from) || !exists(to))
      return;

    auto &listFrom = adjMat[from];
    if (find(listFrom.begin(), listFrom.end(), to) == listFrom.end())
      listFrom.push_back(to);

    auto &listTo = adjMat[to];
    if (find(listTo.begin(), listTo.end(), from) == listTo.end())
      listTo.push_back(from);
  }

  void removeEdge(int from, int to) {
    if (!exists(from) || !exists(to))
      return;

    auto &listFrom = adjMat[from];
    auto itFrom = find(listFrom.begin(), listFrom.end(), to);
    if (itFrom != listFrom.end())
      listFrom.erase(itFrom);

    auto &listTo = adjMat[to];
    auto itTo = find(listTo.begin(), listTo.end(), from);
    if (itTo != listTo.end())
      listTo.erase(itTo);
  }

private:
  bool exists(int v) { return adjMat.count(v) > 0; }
};

int main() {
  /*   GraphAdjMat *a = nullptr;
    int fromIndex;
    int toIndex;
    int res = INT_MAX;
    vector<bool> visit = vector<bool>(a->getSize(), false);
    auto dfs = [&](auto &&dfs, int cur, int len) -> void {
      if (toIndex == cur) {
        res = min(res, len);
        return;
      }
      visit[cur] = true;
      for (int i = 0; i < a->getSize(); i++) {
        if (!visit[i] && a->adjMat[cur][i] == 1) {
          visit[i] = true;
          dfs(dfs, i, len + 1);
          visit[i] = false;
        }
      }
      visit[cur] = false;
    }; */
  GraphAdjList *b = nullptr;
  int fromIndex;
  int toIndex;
  int res = INT_MAX;
  vector<bool> visit = vector<bool>(b->adjMat.size(), false);
  //深度优先搜索
  auto dfs = [&](auto &&dfs, int cur, int len) -> void {
    if (cur == toIndex) {
      res = min(res, len);
    }
    auto &c = b->adjMat.at(cur);
    visit[cur] = true;
    for (int i = 0; i < c.size(); i++) {
      if (!visit[c[i]]) {
        dfs(dfs, c[i], len + 1);
      }
    }
    visit[cur] = false;
  };
  //广度优先搜索
  queue<int> que;
  que.push(fromIndex);
  while (que.empty()) {
    auto i = que.front();
    que.pop();
    for (auto j = 0; j < b->adjMat.at(i).size(); j++) {
      que.push(b->adjMat.at(i)[j]);
      
    }
  }
}