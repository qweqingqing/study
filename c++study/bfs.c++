#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;

// 顶点结构体
struct Vertex {
    int val;
    Vertex(int x) : val(x) {}
};

// 邻接表图
class GraphAdjList {
public:
    unordered_map<Vertex*, vector<Vertex*>> adjList;

    GraphAdjList(const vector<vector<Vertex*>>& edges) {
        for (auto& edge : edges) {
            addVertex(edge[0]);
            addVertex(edge[1]);
            addEdge(edge[0], edge[1]);
        }
    }

    void addVertex(Vertex* v) {
        if (adjList.find(v) == adjList.end()) {
            adjList[v] = vector<Vertex*>();
        }
    }

    // 无向图
    void addEdge(Vertex* v1, Vertex* v2) {
        adjList[v1].push_back(v2);
        adjList[v2].push_back(v1);
    }
};

// ===================== 你提供的 BFS 代码 =====================
vector<Vertex*> graphBFS(GraphAdjList& graph, Vertex* startVet) {
    vector<Vertex*> res;
    unordered_set<Vertex*> visited = {startVet};
    queue<Vertex*> que;
    que.push(startVet);

    while (!que.empty()) {
        Vertex* vet = que.front();
        que.pop();
        res.push_back(vet);

        for (auto adjVet : graph.adjList[vet]) {
            if (visited.count(adjVet))
                continue;
            que.push(adjVet);
            visited.emplace(adjVet);
        }
    }
    return res;
}

// ===================== 你提供的 DFS 代码 =====================
/* 深度优先遍历辅助函数 */
void dfs(GraphAdjList &graph, unordered_set<Vertex *> &visited, vector<Vertex *> &res, Vertex *vet) {
    res.push_back(vet);   // 记录访问顶点
    visited.emplace(vet); // 标记该顶点已被访问
    // 遍历该顶点的所有邻接顶点
    for (Vertex *adjVet : graph.adjList[vet]) {
        if (visited.count(adjVet))
            continue; // 跳过已被访问的顶点
        // 递归访问邻接顶点
        dfs(graph, visited, res, adjVet);
    }
}

/* 深度优先遍历 */
vector<Vertex *> graphDFS(GraphAdjList &graph, Vertex *startVet) {
    // 顶点遍历序列
    vector<Vertex *> res;
    // 哈希集合，用于记录已被访问过的顶点
    unordered_set<Vertex *> visited;
    dfs(graph, visited, res, startVet);
    return res;
}

// ===================== 测试 =====================
int main() {
    // 构建顶点
    Vertex* v0 = new Vertex(0);
    Vertex* v1 = new Vertex(1);
    Vertex* v2 = new Vertex(2);
    Vertex* v3 = new Vertex(3);
    Vertex* v4 = new Vertex(4);

    // 构建边
    vector<vector<Vertex*>> edges = {
        {v0, v1},
        {v0, v2},
        {v1, v3},
        {v1, v4},
        {v2, v4}
    };

    GraphAdjList graph(edges);

    // BFS
    cout << "BFS 遍历: ";
    auto bfs_res = graphBFS(graph, v0);
    for (auto v : bfs_res) cout << v->val << " ";
    cout << endl;

    // DFS
    cout << "DFS 遍历: ";
    auto dfs_res = graphDFS(graph, v0);
    for (auto v : dfs_res) cout << v->val << " ";
    cout << endl;

    return 0;
}