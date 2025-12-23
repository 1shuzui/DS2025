#include "Graph.h"
#include <ctime>
#include <random>
using namespace std;

// 构造函数
Graph::Graph(int n, bool dir) : numVertices(n), directed(dir) {
    adjMatrix.resize(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        vertices.push_back('A' + i);
        vertexIndex['A' + i] = i;
    }
}

// 从顶点标签初始化
Graph::Graph(const vector<char>& verts, bool dir) : directed(dir) {
    numVertices = (int)verts.size();
    adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
    vertices = verts;
    for (int i = 0; i < numVertices; i++) {
        vertexIndex[verts[i]] = i;
    }
}

// 获取顶点索引
int Graph::getIndex(char v) const {
    auto it = vertexIndex.find(v);
    if (it != vertexIndex.end()) {
        return it->second;
    }
    return -1;
}

// 获取顶点标签
char Graph::getLabel(int index) const {
    if (index >= 0 && index < numVertices) {
        return vertices[index];
    }
    return '\0';
}

// 添加边
void Graph::addEdge(char from, char to, int weight) {
    int f = getIndex(from);
    int t = getIndex(to);
    if (f != -1 && t != -1) {
        adjMatrix[f][t] = weight;
        if (!directed) {
            adjMatrix[t][f] = weight;
        }
    }
}

// 获取顶点标签
char Graph::getVertexLabel(int index) const {
    return getLabel(index);
}

// 打印邻接矩阵
void Graph::printAdjMatrix() const {
    cout << "邻接矩阵：" << endl;
    cout << "   ";
    for (int i = 0; i < numVertices; i++) {
        cout << vertices[i] << "  ";
    }
    cout << endl;

    for (int i = 0; i < numVertices; i++) {
        cout << vertices[i] << "  ";
        for (int j = 0; j < numVertices; j++) {
            if (adjMatrix[i][j] == 0) {
                cout << "0  ";
            }
            else {
                cout << adjMatrix[i][j] << "  ";
            }
        }
        cout << endl;
    }
}

// BFS遍历
vector<char> Graph::BFS(char start) const {
    vector<char> result;
    int startIndex = getIndex(start);
    if (startIndex == -1) return result;

    vector<bool> visited(numVertices, false);
    queue<int> q;

    visited[startIndex] = true;
    q.push(startIndex);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        result.push_back(getLabel(current));

        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[current][i] != 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    return result;
}

// DFS递归辅助函数
void Graph::DFSUtil(int v, vector<bool>& visited, vector<char>& result) const {
    visited[v] = true;
    result.push_back(getLabel(v));

    for (int i = 0; i < numVertices; i++) {
        if (adjMatrix[v][i] != 0 && !visited[i]) {
            DFSUtil(i, visited, result);
        }
    }
}

// DFS遍历
vector<char> Graph::DFS(char start) const {
    vector<char> result;
    int startIndex = getIndex(start);
    if (startIndex == -1) return result;

    vector<bool> visited(numVertices, false);
    DFSUtil(startIndex, visited, result);

    return result;
}

// Dijkstra最短路径算法
vector<int> Graph::dijkstra(char start) const {
    vector<int> dist(numVertices, INF);
    int startIndex = getIndex(start);
    if (startIndex == -1) return dist;

    dist[startIndex] = 0;
    vector<bool> visited(numVertices, false);

    // 使用优先队列（最小堆）
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, startIndex });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (adjMatrix[u][v] != 0 && !visited[v]) {
                int weight = adjMatrix[u][v];
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({ dist[v], v });
                }
            }
        }
    }

    return dist;
}

// 打印最短路径
void Graph::printShortestPaths(char start) const {
    vector<int> dist = dijkstra(start);
    cout << "从顶点 " << start << " 出发的最短路径：" << endl;
    for (int i = 0; i < numVertices; i++) {
        if (dist[i] == INF) {
            cout << start << " -> " << getLabel(i) << ": 不可达" << endl;
        }
        else {
            cout << start << " -> " << getLabel(i) << ": " << dist[i] << endl;
        }
    }
}

// Prim最小生成树算法
vector<Edge> Graph::primMST(char start) const {
    vector<Edge> mst;
    int startIndex = getIndex(start);
    if (startIndex == -1 || directed) return mst;

    vector<int> key(numVertices, INF);
    vector<int> parent(numVertices, -1);
    vector<bool> inMST(numVertices, false);

    // 使用优先队列（最小堆）
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[startIndex] = 0;
    pq.push({ 0, startIndex });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (adjMatrix[u][v] != 0 && !inMST[v] && adjMatrix[u][v] < key[v]) {
                key[v] = adjMatrix[u][v];
                parent[v] = u;
                pq.push({ key[v], v });
            }
        }
    }

    // 构建MST边集合
    for (int i = 0; i < numVertices; i++) {
        if (parent[i] != -1) {
            mst.push_back(Edge(parent[i], i, adjMatrix[parent[i]][i]));
        }
    }

    return mst;
}

// 获取所有边
vector<Edge> Graph::getAllEdges() const {
    vector<Edge> edges;
    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            if (adjMatrix[i][j] != 0) {
                edges.push_back(Edge(i, j, adjMatrix[i][j]));
            }
        }
    }
    return edges;
}

// Kruskal最小生成树算法
vector<Edge> Graph::kruskalMST() const {
    vector<Edge> mst;
    if (directed) return mst;

    // 获取所有边
    vector<Edge> edges = getAllEdges();

    // 按权重排序
    sort(edges.begin(), edges.end());

    // 初始化Union-Find
    UnionFind uf(numVertices);

    // 构建MST
    for (const Edge& edge : edges) {
        if (uf.find(edge.from) != uf.find(edge.to)) {
            mst.push_back(edge);
            uf.unite(edge.from, edge.to);
        }
    }

    return mst;
}

// 打印最小生成树
void Graph::printMST(const vector<Edge>& mst) const {
    cout << "最小生成树的边：" << endl;
    for (const Edge& edge : mst) {
        cout << getLabel(edge.from) << " -- " << getLabel(edge.to)
            << " (权重: " << edge.weight << ")" << endl;
    }
}

// 计算最小生成树总权重
int Graph::getMSTWeight(const vector<Edge>& mst) const {
    int totalWeight = 0;
    for (const Edge& edge : mst) {
        totalWeight += edge.weight;
    }
    return totalWeight;
}

// Tarjan算法辅助函数
void Graph::tarjanDFS(int u, int parent, vector<int>& disc, vector<int>& low,
    vector<int>& parentArr, vector<bool>& articulation,
    vector<vector<int>>& biconnectedComponents,
    stack<Edge>& edgeStack, int& time) const {
    // 初始化发现时间和低链接值
    disc[u] = low[u] = ++time;
    int children = 0;

    // 遍历所有邻居
    for (int v = 0; v < numVertices; v++) {
        if (adjMatrix[u][v] != 0) {
            // 如果v未被访问
            if (disc[v] == -1) {
                children++;
                parentArr[v] = u;

                // 将边压入栈
                edgeStack.push(Edge(u, v));

                // 递归访问v
                tarjanDFS(v, u, disc, low, parentArr, articulation,
                    biconnectedComponents, edgeStack, time);

                // 更新u的低链接值
                low[u] = min(low[u], low[v]);

                // 检查u是否是关节点
                // 情况1: u是根节点且有两个以上子节点
                if (parent == -1 && children > 1) {
                    articulation[u] = true;
                }

                // 情况2: u不是根节点且low[v] >= disc[u]
                if (parent != -1 && low[v] >= disc[u]) {
                    articulation[u] = true;

                    // 弹出边直到(u, v)，这些边构成一个双连通分量
                    vector<int> component;
                    while (!edgeStack.empty()) {
                        Edge edge = edgeStack.top();
                        edgeStack.pop();
                        component.push_back(edge.from);
                        component.push_back(edge.to);
                        if (edge.from == u && edge.to == v) break;
                    }
                    biconnectedComponents.push_back(component);
                }
            }
            // 如果v已被访问且不是父节点
            else if (v != parent) {
                low[u] = min(low[u], disc[v]);
                if (disc[v] < disc[u]) {
                    edgeStack.push(Edge(u, v));
                }
            }
        }
    }

    // 处理根节点的双连通分量
    if (parent == -1 && !edgeStack.empty()) {
        vector<int> component;
        while (!edgeStack.empty()) {
            Edge edge = edgeStack.top();
            edgeStack.pop();
            component.push_back(edge.from);
            component.push_back(edge.to);
        }
        biconnectedComponents.push_back(component);
    }
}

// 查找关节点
vector<char> Graph::findArticulationPoints() const {
    vector<char> articulationPoints;
    if (numVertices == 0) return articulationPoints;

    vector<int> disc(numVertices, -1);
    vector<int> low(numVertices, -1);
    vector<int> parentArr(numVertices, -1);
    vector<bool> articulation(numVertices, false);
    vector<vector<int>> biconnectedComponents;
    stack<Edge> edgeStack;
    int time = 0;

    // 对每个未访问的顶点进行DFS
    for (int i = 0; i < numVertices; i++) {
        if (disc[i] == -1) {
            tarjanDFS(i, -1, disc, low, parentArr, articulation,
                biconnectedComponents, edgeStack, time);
        }
    }

    // 收集关节点
    for (int i = 0; i < numVertices; i++) {
        if (articulation[i]) {
            articulationPoints.push_back(getLabel(i));
        }
    }

    return articulationPoints;
}

// 查找双连通分量
vector<vector<char>> Graph::findBiconnectedComponents() const {
    vector<vector<char>> bccs;
    if (numVertices == 0) return bccs;

    vector<int> disc(numVertices, -1);
    vector<int> low(numVertices, -1);
    vector<int> parentArr(numVertices, -1);
    vector<bool> articulation(numVertices, false);
    vector<vector<int>> biconnectedComponents;
    stack<Edge> edgeStack;
    int time = 0;

    // 对每个未访问的顶点进行DFS
    for (int i = 0; i < numVertices; i++) {
        if (disc[i] == -1) {
            tarjanDFS(i, -1, disc, low, parentArr, articulation,
                biconnectedComponents, edgeStack, time);
        }
    }

    // 转换结果为字符形式
    for (const auto& component : biconnectedComponents) {
        set<char> uniqueVertices;
        for (int vertex : component) {
            uniqueVertices.insert(getLabel(vertex));
        }

        vector<char> charComponent;
        for (char v : uniqueVertices) {
            charComponent.push_back(v);
        }
        bccs.push_back(charComponent);
    }

    return bccs;
}

// 打印双连通分量
void Graph::printBiconnectedComponents() const {
    vector<vector<char>> bccs = findBiconnectedComponents();
    cout << "双连通分量：" << endl;
    for (size_t i = 0; i < bccs.size(); i++) {
        cout << "分量 " << i + 1 << ": ";
        for (char v : bccs[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

// 检查图是否连通
bool Graph::isConnected() const {
    if (numVertices == 0) return true;

    vector<bool> visited(numVertices, false);
    stack<int> s;
    s.push(0);
    visited[0] = true;

    while (!s.empty()) {
        int u = s.top();
        s.pop();

        for (int v = 0; v < numVertices; v++) {
            if ((adjMatrix[u][v] != 0 || adjMatrix[v][u] != 0) && !visited[v]) {
                visited[v] = true;
                s.push(v);
            }
        }
    }

    for (bool v : visited) {
        if (!v) return false;
    }
    return true;
}

// 获取顶点索引
int Graph::getVertexIndex(char v) const {
    return getIndex(v);
}

// 检查边是否存在
bool Graph::hasEdge(char from, char to) const {
    int f = getIndex(from);
    int t = getIndex(to);
    if (f == -1 || t == -1) return false;
    return adjMatrix[f][t] != 0;
}

// 获取边的权重
int Graph::getEdgeWeight(char from, char to) const {
    int f = getIndex(from);
    int t = getIndex(to);
    if (f == -1 || t == -1) return 0;
    return adjMatrix[f][t];
}