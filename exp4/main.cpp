#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include "BoundingBox.h"
#include "DataGenerator.h"
#include "NMS.h"
#include "PerformanceTest.h"

using namespace std;

// 功能1: 基本NMS算法演示
void demoBasicNMS() {
    cout << "" << endl;
    cout << "功能1: 基本NMS算法演示" << endl;
    cout << "" << endl;

    DataGenerator generator;
    NMS nms(0.5);

    // 生成小规模数据用于演示
    auto boxes = generator.generateClusteredBoxes(15, 3);

    cout << "\n生成15个边界框（聚集分布，3个聚类中心）：" << endl;
    for (int i = 0; i < boxes.size(); i++) {
        const auto& box = boxes[i];
        cout << "  BBox[" << box.id << "] 位置:(" << box.x << "," << box.y
            << ") 大小:" << box.width << "x" << box.height
            << " 置信度:" << box.confidence << endl;
    }

    // 应用NMS
    auto start = chrono::high_resolution_clock::now();
    auto result = nms.standardNMS(boxes);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "\n应用NMS算法（IoU阈值=0.5）..." << endl;
    cout << "NMS后保留 " << result.size() << " 个边界框：" << endl;
    for (int i = 0; i < result.size(); i++) {
        const auto& box = result[i];
        cout << "  BBox[" << box.id << "] 置信度:" << box.confidence << endl;
    }

    float compressionRate = nms.computeCompressionRate(boxes, result);
    cout << "\n压缩率: " << compressionRate * 100 << "%" << endl;
    cout << "处理时间: " << duration.count() << " 微秒" << endl;

    if (nms.verifyNMSResult(result)) {
        cout << "✓ NMS结果验证通过" << endl;
    }
}

// 功能2: 排序算法性能比较
void demoSortingComparison() {
    cout << "\n\n" << endl;
    cout << "              功能2: 排序算法性能比较" << endl;
    cout << "" << endl;

    DataGenerator generator;

    cout << "\n比较六种排序算法的性能：" << endl;
    cout << "1. 快速排序（O(n log n)）" << endl;
    cout << "2. 归并排序（O(n log n)）" << endl;
    cout << "3. 堆排序（O(n log n)）" << endl;
    cout << "4. 冒泡排序（O(n²)）" << endl;
    cout << "5. 选择排序（O(n²)）" << endl;
    cout << "6. 插入排序（O(n²)）" << endl;

    vector<int> testSizes = { 100, 1000, 5000 };

    for (int size : testSizes) {
        cout << "\n测试 " << size << " 个边界框：" << endl;
        auto boxes = generator.generateRandomBoxes(size);

        // 定义排序算法
        vector<pair<string, function<void(vector<BoundingBox>&)>>> algorithms = {
            {"快速排序", [](vector<BoundingBox>& b) {
                SortAlgorithms::quickSort(b, [](const BoundingBox& a, const BoundingBox& b) {
                    return a.confidence > b.confidence;
                });
            }},
            {"归并排序", [](vector<BoundingBox>& b) {
                SortAlgorithms::mergeSort(b, [](const BoundingBox& a, const BoundingBox& b) {
                    return a.confidence > b.confidence;
                });
            }},
            {"堆排序", [](vector<BoundingBox>& b) {
                SortAlgorithms::heapSort(b, [](const BoundingBox& a, const BoundingBox& b) {
                    return a.confidence > b.confidence;
                });
            }},
            {"冒泡排序", [](vector<BoundingBox>& b) {
                SortAlgorithms::bubbleSort(b, [](const BoundingBox& a, const BoundingBox& b) {
                    return a.confidence > b.confidence;
                });
            }},
            {"选择排序", [](vector<BoundingBox>& b) {
                SortAlgorithms::selectionSort(b, [](const BoundingBox& a, const BoundingBox& b) {
                    return a.confidence > b.confidence;
                });
            }},
            {"插入排序", [](vector<BoundingBox>& b) {
                SortAlgorithms::insertionSort(b, [](const BoundingBox& a, const BoundingBox& b) {
                    return a.confidence > b.confidence;
                });
            }}
        };

        cout << setw(15) << "算法" << setw(20) << "排序时间(ms)" << endl;
        cout << string(35, '-') << endl;

        for (const auto& algo : algorithms) {
            auto boxesCopy = boxes;
            auto start = chrono::high_resolution_clock::now();
            algo.second(boxesCopy);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

            cout << setw(15) << algo.first
                << setw(20) << fixed << setprecision(2) << duration.count() / 1000.0 << endl;
        }
    }
}

// 功能3: 数据分布对NMS的影响
void demoDistributionImpact() {
    cout << "\n\n" << endl;
    cout << " 功能3: 数据分布对NMS的影响" << endl;
    cout << "" << endl;

    DataGenerator generator;
    NMS nms(0.5);

    int numBoxes = 2000;
    cout << "\n生成 " << numBoxes << " 个边界框，比较两种分布：" << endl;

    // 随机分布
    auto randomBoxes = generator.generateRandomBoxes(numBoxes);
    auto start1 = chrono::high_resolution_clock::now();
    auto randomResult = nms.standardNMS(randomBoxes);
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1);
    float compression1 = nms.computeCompressionRate(randomBoxes, randomResult);

    // 聚集分布
    auto clusteredBoxes = generator.generateClusteredBoxes(numBoxes, 5);
    auto start2 = chrono::high_resolution_clock::now();
    auto clusteredResult = nms.standardNMS(clusteredBoxes);
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2);
    float compression2 = nms.computeCompressionRate(clusteredBoxes, clusteredResult);

    cout << "\n随机分布结果：" << endl;
    cout << "  原始数量: " << randomBoxes.size() << endl;
    cout << "  NMS后数量: " << randomResult.size() << endl;
    cout << "  压缩率: " << compression1 * 100 << "%" << endl;
    cout << "  处理时间: " << duration1.count() / 1000.0 << " ms" << endl;

    cout << "\n聚集分布结果：" << endl;
    cout << "  原始数量: " << clusteredBoxes.size() << endl;
    cout << "  NMS后数量: " << clusteredResult.size() << endl;
    cout << "  压缩率: " << compression2 * 100 << "%" << endl;
    cout << "  处理时间: " << duration2.count() / 1000.0 << " ms" << endl;

    cout << "\n分析：" << endl;
    cout << "1. 聚集分布的压缩率比随机分布高 " << (compression2 - compression1) * 100 << "%" << endl;
    cout << "2. 这是因为聚集分布的边界框重叠更多，NMS能过滤掉更多重复检测" << endl;
    cout << "3. 处理时间差异主要取决于边界框的重叠程度" << endl;
}

// 功能4: 完整性能测试
void runCompletePerformanceTest() {
    cout << "\n\n" << endl;
    cout << "完整性能测试 (100-10000个边界框)" << endl;
    cout << "" << endl;

    PerformanceTest tester;
    tester.runFullTest();
}

int main() {
    cout << "" << endl;
    cout << "排序算法与非极大值抑制（NMS）" << endl;
 

    // 开始计时
    auto startTotal = chrono::high_resolution_clock::now();

    // 依次运行四个功能
    demoBasicNMS();
    demoSortingComparison();
    demoDistributionImpact();
    runCompletePerformanceTest();

    // 总运行时间
    auto endTotal = chrono::high_resolution_clock::now();
    auto durationTotal = chrono::duration_cast<chrono::milliseconds>(endTotal - startTotal);

    cout << "\n\n" << endl;
    cout << "" << endl;
    cout << "总运行时间: " << durationTotal.count() / 1000.0 << " 秒" << endl;
    cout << "" << endl;
    return 0;
}