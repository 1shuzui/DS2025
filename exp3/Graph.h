#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <functional>
using namespace std;

// 定义无穷大值
const int INF = numeric_limits<int>::max();

// 边的结构体
struct Edge {
    int from;
    int to;
    int weight;
    Edge(int f = 0, int t = 0, int w = 1) : from(f), to(t), weight(w) {}

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// 图类（邻接矩阵实现）
class Graph {
private:
    int numVertices;          // 顶点数
    bool directed;           // 是否有向
    vector<vector<int>> adjMatrix;  // 邻接矩阵
    vector<char> vertices;    // 顶点标签（字符）
    map<char, int> vertexIndex; // 顶点标签到索引的映射

    // 辅助函数
    int getIndex(char v) const;
    char getLabel(int index) const;

    // DFS递归辅助函数
    void DFSUtil(int v, vector<bool>& visited, vector<char>& result) const;

    // Tarjan算法辅助函数
    void tarjanDFS(int u, int parent, vector<int>& disc, vector<int>& low,
        vector<int>& parentArr, vector<bool>& articulation,
        vector<vector<int>>& biconnectedComponents,
        stack<Edge>& edgeStack, int& time) const;

    // Union-Find结构（用于Kruskal算法）
    struct UnionFind {
        vector<int> parent, rank;
        UnionFind(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            for (int i = 0; i < n; i++) parent[i] = i;
        }

        int find(int x) {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }

        void unite(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);

            if (rootX != rootY) {
                if (rank[rootX] < rank[rootY]) {
                    parent[rootX] = rootY;
                }
                else if (rank[rootX] > rank[rootY]) {
                    parent[rootY] = rootX;
                }
                else {
                    parent[rootY] = rootX;
                    rank[rootX]++;
                }
            }
        }
    };

public:
    // 构造函数
    Graph(int n = 0, bool dir = false);

    // 从顶点标签初始化
    Graph(const vector<char>& verts, bool dir = false);

    // 添加边
    void addEdge(char from, char to, int weight = 1);

    // 获取顶点数
    int getNumVertices() const { return numVertices; }

    // 获取顶点标签
    char getVertexLabel(int index) const;

    // 打印邻接矩阵
    void printAdjMatrix() const;

    // BFS遍历
    vector<char> BFS(char start) const;

    // DFS遍历
    vector<char> DFS(char start) const;

    // Dijkstra最短路径算法
    vector<int> dijkstra(char start) const;

    // 打印最短路径
    void printShortestPaths(char start) const;

    // Prim最小生成树算法
    vector<Edge> primMST(char start) const;

    // Kruskal最小生成树算法
    vector<Edge> kruskalMST() const;

    // 打印最小生成树
    void printMST(const vector<Edge>& mst) const;

    // 计算最小生成树总权重
    int getMSTWeight(const vector<Edge>& mst) const;

    // 查找关节点（Articulation Points）
    vector<char> findArticulationPoints() const;

    // 查找双连通分量（Biconnected Components）
    vector<vector<char>> findBiconnectedComponents() const;

    // 打印双连通分量
    void printBiconnectedComponents() const;

    // 获取所有边
    vector<Edge> getAllEdges() const;

    // 检查图是否连通
    bool isConnected() const;

    // 获取顶点索引
    int getVertexIndex(char v) const;

    // 检查边是否存在
    bool hasEdge(char from, char to) const;

    // 获取边的权重
    int getEdgeWeight(char from, char to) const;
};

#endif // GRAPH_H