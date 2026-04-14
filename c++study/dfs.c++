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

// 邻接表表示的图
class GraphAdjList {
public:
    // 邻接表：key = 顶点，value = 该顶点的所有邻接顶点
    unordered_map<Vertex*, vector<Vertex*>> adjList;

    // 构造函数：根据边列表构建图
    GraphAdjList(const vector<vector<Vertex*>>& edges) {
        for (auto& edge : edges) {
            addVertex(edge[0]);
            addVertex(edge[1]);
            addEdge(edge[0], edge[1]);
        }
    }

    // 添加顶点
    void addVertex(Vertex* v) {
        if (adjList.find(v) == adjList.end()) {
            adjList[v] = vector<Vertex*>();
        }
    }

    // 添加边（无向图）
    void addEdge(Vertex* v1, Vertex* v2) {
        adjList[v1].push_back(v2);
        adjList[v2].push_back(v1);
    }
};

/* 广度优先遍历 BFS */
vector<Vertex*> graphBFS(GraphAdjList& graph, Vertex* startVet) {
    vector<Vertex*> res;
    unordered_set<Vertex*> visited = {startVet};
    queue<Vertex*> que;
    que.push(startVet);

    while (!que.empty()) {
        Vertex* vet = que.front();
        que.pop();
        res.push_back(vet);

        // 遍历所有邻接顶点
        for (auto adjVet : graph.adjList[vet]) {
            if (visited.count(adjVet))
                continue;
            que.push(adjVet);
            visited.emplace(adjVet);
        }
    }
    return res;
}

// 主函数测试
int main() {
    // 构建顶点
    Vertex* v0 = new Vertex(0);
    Vertex* v1 = new Vertex(1);
    Vertex* v2 = new Vertex(2);
    Vertex* v3 = new Vertex(3);
    Vertex* v4 = new Vertex(4);

    // 构建边（无向图）
    vector<vector<Vertex*>> edges = {
        {v0, v1},
        {v0, v2},
        {v1, v3},
        {v1, v4},
        {v2, v4}
    };

    // 构建图
    GraphAdjList graph(edges);

    // BFS 遍历，起点 v0
    vector<Vertex*> res = graphBFS(graph, v0);

    // 输出结果
    cout << "BFS 遍历顺序：";
    for (auto v : res) {
        cout << v->val << " ";
    }
    cout << endl;

    return 0;
}