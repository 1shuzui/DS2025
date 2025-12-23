#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Graph.h"
using namespace std;

// 创建图1（实验要求中的图1）
Graph createGraph1() {
    // 图1的顶点：A, B, C, D, E, F, G, H
    vector<char> vertices = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
    Graph g(vertices, false);  // 无向图

    // 添加边（根据图示）
    g.addEdge('A', 'B', 6);
    g.addEdge('A', 'D', 2);
    g.addEdge('A', 'G', 4);
    g.addEdge('B', 'C', 13);
    g.addEdge('B', 'E', 11);
    g.addEdge('C', 'D', 1);
    g.addEdge('C', 'F', 5);
    g.addEdge('D', 'E', 14);
    g.addEdge('D', 'G', 8);
    g.addEdge('E', 'F', 3);
    g.addEdge('F', 'H', 12);
    g.addEdge('G', 'H', 9);

    return g;
}

// 创建图2（实验要求中的图2）
Graph createGraph2() {
    // 图2的顶点：A, B, C, D, E, F, G, H, I, J, K, L
    vector<char> vertices = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L' };
    Graph g(vertices, false);  // 无向图

    // 添加边（根据图示）
    g.addEdge('A', 'B', 4);
    g.addEdge('A', 'C', 13);
    g.addEdge('A', 'D', 11);
    g.addEdge('B', 'C', 12);
    g.addEdge('B', 'E', 1);
    g.addEdge('C', 'D', 5);
    g.addEdge('C', 'F', 8);
    g.addEdge('D', 'E', 14);
    g.addEdge('D', 'G', 3);
    g.addEdge('E', 'F', 2);
    g.addEdge('E', 'H', 9);
    g.addEdge('F', 'G', 6);
    g.addEdge('G', 'H', 7);
    g.addEdge('H', 'I', 10);
    g.addEdge('I', 'J', 15);
    g.addEdge('J', 'K', 16);
    g.addEdge('K', 'L', 17);

    return g;
}

// 测试图1
void testGraph1() {
    cout << "图1" << endl;
    Graph g1 = createGraph1();

    // (1) 输出邻接矩阵
    cout << "\n(1) 图1的邻接矩阵：" << endl;
    g1.printAdjMatrix();

    // (2) BFS和DFS遍历
    cout << "\n(2) 从顶点A出发的遍历：" << endl;

    vector<char> bfsResult = g1.BFS('A');
    cout << "BFS遍历顺序: ";
    for (char v : bfsResult) {
        cout << v << " ";
    }
    cout << endl;

    vector<char> dfsResult = g1.DFS('A');
    cout << "DFS遍历顺序: ";
    for (char v : dfsResult) {
        cout << v << " ";
    }
    cout << endl;

    // (3) 最短路径和最小支撑树
    cout << "\n(3) 从顶点A出发的最短路径和最小支撑树：" << endl;

    // 最短路径
    g1.printShortestPaths('A');

    // Prim最小生成树
    cout << "\nPrim算法最小生成树：" << endl;
    vector<Edge> primMST = g1.primMST('A');
    g1.printMST(primMST);
    cout << "最小生成树总权重: " << g1.getMSTWeight(primMST) << endl;

    // Kruskal最小生成树
    cout << "\nKruskal算法最小生成树：" << endl;
    vector<Edge> kruskalMST = g1.kruskalMST();
    g1.printMST(kruskalMST);
    cout << "最小生成树总权重: " << g1.getMSTWeight(kruskalMST) << endl;

    cout << "\n图1测试完成！" << endl;
    cout << "\n" << endl;
}

// 测试图2
void testGraph2() {
    cout << " 图2 " << endl;
    Graph g2 = createGraph2();

    // 输出邻接矩阵
    cout << "\n图2的邻接矩阵：" << endl;
    g2.printAdjMatrix();

    // 检查连通性
    cout << "\n图2是否连通: " << (g2.isConnected() ? "是" : "否") << endl;

    // 从不同起点计算关节点和双连通分量
    vector<char> startVertices = { 'A', 'D', 'H', 'L' };

    // 先获取一次结果作为基准
    vector<char> firstArticulationPoints = g2.findArticulationPoints();
    vector<vector<char>> firstBCCs = g2.findBiconnectedComponents();

    cout << "\n从不同起点分析关节点和双连通分量：" << endl;

    for (char start : startVertices) {
        cout << "\n从顶点 " << start << " 开始分析：" << endl;

        // 查找关节点
        vector<char> articulationPoints = g2.findArticulationPoints();
        cout << "关节点: ";
        if (articulationPoints.empty()) {
            cout << "无";
        }
        else {
            for (char v : articulationPoints) {
                cout << v << " ";
            }
        }
        cout << endl;

        // 查找双连通分量
        vector<vector<char>> bccs = g2.findBiconnectedComponents();
        cout << "双连通分量数量: " << bccs.size() << endl;
        for (size_t i = 0; i < bccs.size(); i++) {
            cout << "分量 " << i + 1 << ": ";
            for (char v : bccs[i]) {
                cout << v << " ";
            }
            cout << endl;
        }

        cout << string(40, '-') << endl;
    }

    // 验证结果一致性
    cout << "\n验证关节点结果一致性：" << endl;

    bool consistent = true;

    for (size_t i = 1; i < startVertices.size(); i++) {
        vector<char> currentArticulationPoints = g2.findArticulationPoints();
        if (firstArticulationPoints.size() != currentArticulationPoints.size()) {
            consistent = false;
            break;
        }
        for (size_t j = 0; j < firstArticulationPoints.size(); j++) {
            if (firstArticulationPoints[j] != currentArticulationPoints[j]) {
                consistent = false;
                break;
            }
        }
        if (!consistent) break;
    }

    if (consistent) {
        cout << "所有起点得到的关节点结果一致！" << endl;
        cout << "最终关节点: ";
        for (char v : firstArticulationPoints) {
            cout << v << " ";
        }
        cout << endl;
    }
    else {
        cout << "不同起点得到的关节点结果不一致！" << endl;
    }

    // 打印双连通分量
    cout << "\n双连通分量结果：" << endl;
    g2.printBiconnectedComponents();

    cout << "\n图2完成" << endl;
    cout << "\n" << endl;
}

// 性能测试和算法比较
void performanceTest() {
    cout << "性能测试和算法比较" << endl;

    // 创建一个更大的图进行测试
    vector<char> vertices;
    for (int i = 0; i < 10; i++) {
        vertices.push_back('A' + i);
    }
    Graph g(vertices, false);

    // 添加随机边
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 15; i++) {
        char from = 'A' + rand() % 10;
        char to = 'A' + rand() % 10;
        if (from != to) {
            int weight = 1 + rand() % 20;
            g.addEdge(from, to, weight);
        }
    }

    cout << "随机生成的图：" << endl;
    g.printAdjMatrix();

    // 测试不同算法
    cout << "\n算法性能测试：" << endl;

    // BFS和DFS
    vector<char> bfsResult = g.BFS('A');
    cout << "BFS遍历: ";
    for (char v : bfsResult) cout << v << " ";
    cout << endl;

    vector<char> dfsResult = g.DFS('A');
    cout << "DFS遍历: ";
    for (char v : dfsResult) cout << v << " ";
    cout << endl;

    // 最短路径
    g.printShortestPaths('A');

    // 最小生成树比较
    vector<Edge> primMST = g.primMST('A');
    vector<Edge> kruskalMST = g.kruskalMST();

    cout << "\nPrim算法MST权重: " << g.getMSTWeight(primMST) << endl;
    cout << "Kruskal算法MST权重: " << g.getMSTWeight(kruskalMST) << endl;

    if (g.getMSTWeight(primMST) == g.getMSTWeight(kruskalMST)) {
        cout << "两种算法得到的最小生成树权重相同！" << endl;
    }
    else {
        cout << "两种算法得到的结果不同！" << endl;
    }

    cout << "\n性能测试完成" << endl;
    cout << "\n" << endl;
}

int main() {
    cout << "图数据结构" << endl;
    cout << "" << endl;

    // 测试图1
    testGraph1();

    // 测试图2
    testGraph2();

    // 性能测试
    performanceTest();

    cout << "完成" << endl;

    return 0;
}