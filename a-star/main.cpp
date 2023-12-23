#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <vector>

using namespace std;

struct Node {
  float distance(Node *other) {
    return sqrt(pow(x - other->x, 2) + pow(y - other->y, 2));
  }

  char name;
  float x, y;
};

typedef pair<float, Node *> NodePair;

class Graph {
public:
  void addEdge(Node *a, Node *b) {
    if (edges.find(a) == edges.end()) {
      edges[a] = vector<Node *>();
    }
    if (edges.find(b) == edges.end()) {
      edges[b] = vector<Node *>();
    }
    edges[a].push_back(b);
    edges[b].push_back(a);
  }

  void setStart(Node *s) { start = s; }

  void setGoal(Node *g) { goal = g; }

  float h(Node *node) { return node->distance(goal); }

  vector<Node *> aStar() {
    priority_queue<NodePair, vector<NodePair>, greater<NodePair>> open;
    set<Node *> closed;
    map<Node *, float> g;

    open.push({0, start});
    map<Node *, Node *> cameFrom;
    g[start] = 0;

    while (!open.empty()) {
      Node *curr = open.top().second;
      open.pop();
      closed.insert(curr);

      if (curr == goal) {
        vector<Node *> path;
        while (curr) {
          path.push_back(curr);
          curr = cameFrom[curr];
        }
        reverse(path.begin(), path.end());
        return path;
      }

      for (Node *n : edges[curr]) {
        if (closed.find(n) != closed.end()) {
          continue;
        }

        float d = curr->distance(n);
        float possibleG = g[curr] + d;

        if (g.find(n) == g.end() || possibleG < g[n]) {
          g[n] = possibleG;
          cameFrom[n] = curr;

          float f = possibleG + h(n);
          open.push({f, n});
        }
      }
    }
    return vector<Node *>();
  }

private:
  map<Node *, vector<Node *>> edges;
  Node *start, *goal;
};

int main() {
  Node A = {'A', 0, 0};
  Node B = {'B', 1, 3};
  Node C = {'C', 2, 1};
  Node D = {'D', 4, 0};
  Node E = {'E', 3, 3};
  Node F = {'F', 4, 2};
  Node G = {'G', 6, 4};

  Graph graph;
  graph.addEdge(&A, &B);
  graph.addEdge(&A, &C);
  graph.addEdge(&A, &D);
  graph.addEdge(&B, &E);
  graph.addEdge(&C, &E);
  graph.addEdge(&B, &F);
  graph.addEdge(&C, &F);
  graph.addEdge(&D, &E);
  graph.addEdge(&D, &F);
  graph.addEdge(&E, &G);
  graph.addEdge(&F, &G);

  graph.setStart(&A);
  graph.setGoal(&G);

  vector<Node *> path = graph.aStar();
  for (const Node *node : path) {
    cout << node->name << " ";
  }
  return 0;
}
