#include <vector>
#include <iostream>
#include "vector.h"
#include <string>
using namespace std;

// 任务1：复数向量测试
void task1() {
    cout << "=== 任务1：复数向量测试 ===" << endl;
    
    // 创建无序复数向量（有重复项）
    Vector<Complex> vec;
    srand(time(NULL));
    
    // 随机生成10个复数
    for (int i = 0; i < 10; i++) {
        double real = rand() % 10;
        double imag = rand() % 10;
        vec.insert(Complex(real, imag));
    }
    
    cout << "原始向量: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    
    // (1) 测试置乱
    vec.unsort();
    cout << "置乱后: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    
    // (1) 测试查找
    Complex searchTarget(3, 4);
    Rank pos = vec.find(searchTarget);
    if (pos >= 0) {
        cout << "找到 " << searchTarget << " 在位置 " << pos << endl;
    } else {
        cout << "未找到 " << searchTarget << endl;
    }
    
    // (1) 测试插入
    vec.insert(Complex(7, 8));
    cout << "插入后大小: " << vec.size() << endl;
    
    // (1) 测试删除
    if (vec.size() > 0) {
        vec.remove(0);
        cout << "删除第一个元素后大小: " << vec.size() << endl;
    }
    
    // (1) 测试唯一化（需要先排序）
    vec.sort();
    int removed = vec.uniquify();
    cout << "唯一化后删除重复元素: " << removed << " 个" << endl;
    
    // (2) 比较排序效率
    cout << "\n=== 排序效率比较 ===" << endl;
    
    // 创建顺序、逆序、乱序向量
    Vector<Complex> ordered, reversed, random;
    for (int i = 0; i < 100; i++) { // 减少数据量便于测试
        ordered.insert(Complex(i, i));
        reversed.insert(Complex(99 - i, 99 - i));
        random.insert(Complex(rand() % 100, rand() % 100));
    }
    
    // 测试起泡排序
    Vector<Complex> bubbleTest = ordered;
    clock_t start = clock();
    bubbleTest.bubbleSort(0, bubbleTest.size());
    clock_t end = clock();
    cout << "顺序-起泡排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    
    bubbleTest = reversed;
    start = clock();
    bubbleTest.bubbleSort(0, bubbleTest.size());
    end = clock();
    cout << "逆序-起泡排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    
    bubbleTest = random;
    start = clock();
    bubbleTest.bubbleSort(0, bubbleTest.size());
    end = clock();
    cout << "乱序-起泡排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    
    // 测试归并排序
    Vector<Complex> mergeTest = ordered;
    start = clock();
    mergeTest.mergeSort(0, mergeTest.size());
    end = clock();
    cout << "顺序-归并排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    
    mergeTest = reversed;
    start = clock();
    mergeTest.mergeSort(0, mergeTest.size());
    end = clock();
    cout << "逆序-归并排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    
    mergeTest = random;
    start = clock();
    mergeTest.mergeSort(0, mergeTest.size());
    end = clock();
    cout << "乱序-归并排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    
    // (3) 区间查找
    cout << "\n=== 区间查找 ===" << endl;
    Vector<Complex> sortedVec;
    for (int i = 0; i < 20; i++) {
        sortedVec.insert(Complex(rand() % 10, rand() % 10));
    }
    sortedVec.sort();
    
    cout << "有序向量: ";
    for (int i = 0; i < sortedVec.size(); i++) {
        cout << sortedVec[i] << "(模:" << sortedVec[i].modulus() << ") ";
    }
    cout << endl;
    
    // 查找模在[5, 10)范围内的元素
    double m1 = 5.0, m2 = 10.0;
    Vector<Complex> result;
    for (int i = 0; i < sortedVec.size(); i++) {
        double mod = sortedVec[i].modulus();
        if (mod >= m1 && mod < m2) {
            result.insert(sortedVec[i]);
        }
    }
    
    cout << "模在[" << m1 << ", " << m2 << ")范围内的元素: ";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}

// 任务2：计算器测试
void task2() {
    cout << "\n=== 任务2：计算器测试 ===" << endl;
    
    vector<string> testCases = {
        "2 + 3 * 4",
        "(2 + 3) * 4",
        "10 / 2 - 1",
        "2 ^ 3 + 1",
        "3 * (4 + 5) / 2"
    };
    
    for (const string& expr : testCases) {
        try {
            double result = Calculator::evaluate(expr);
            cout << expr << " = " << result << endl;
        } catch (const exception& error) {
            cout << expr << " -> 错误: " << error.what() << endl;
        }
    }
}

// 任务3：柱状图最大面积
void task3() {
    cout << "\n=== 任务3：柱状图最大面积测试 ===" << endl;
    
    srand(time(NULL));
    
    for (int test = 1; test <= 5; test++) { // 减少测试次数
        int n = rand() % 10 + 5; // 5-14个柱子
        Vector<int> heights;
        
        cout << "测试" << test << " - " << n << "个柱子: ";
        for (int i = 0; i < n; i++) {
            int height = rand() % 20 + 1; // 高度1-20
            heights.insert(height);
            cout << height << " ";
        }
        
        int area = largestRectangleArea(heights);
        cout << "-> 最大面积: " << area << endl;
    }
}

int main() {
    cout << "C++数据结构学习任务演示" << endl;
    cout << "=========================" << endl;
    
    // 任务1：复数向量测试
    task1();
    
    // 任务2：计算器测试
    task2();
    
    // 任务3：柱状图最大面积
    task3();
    
    return 0;
}