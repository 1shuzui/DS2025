#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include "BoundingBox.h"
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <chrono>
using namespace std;

class DataGenerator {
private:
    mt19937 rng;

public:
    DataGenerator() {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        rng.seed(seed);
    }

    // 生成随机分布的边界框
    vector<BoundingBox> generateRandomBoxes(int count,
        float minX = 0, float maxX = 1000,
        float minY = 0, float maxY = 1000,
        float minSize = 10, float maxSize = 100,
        float minConf = 0.1, float maxConf = 1.0) {
        vector<BoundingBox> boxes;
        uniform_real_distribution<float> distX(minX, maxX);
        uniform_real_distribution<float> distY(minY, maxY);
        uniform_real_distribution<float> distSize(minSize, maxSize);
        uniform_real_distribution<float> distConf(minConf, maxConf);

        for (int i = 0; i < count; i++) {
            float x = distX(rng);
            float y = distY(rng);
            float w = distSize(rng);
            float h = distSize(rng);
            float conf = distConf(rng);

            boxes.emplace_back(i, x, y, w, h, conf);
        }

        return boxes;
    }

    // 生成聚集分布的边界框（在几个聚类中心周围）
    vector<BoundingBox> generateClusteredBoxes(int count, int clusterCount = 5,
        float minX = 0, float maxX = 1000,
        float minY = 0, float maxY = 1000,
        float minSize = 10, float maxSize = 100,
        float minConf = 0.1, float maxConf = 1.0,
        float clusterRadius = 150) {
        vector<BoundingBox> boxes;

        // 生成聚类中心
        vector<pair<float, float>> clusterCenters;
        uniform_real_distribution<float> distCenterX(minX + 100, maxX - 100);
        uniform_real_distribution<float> distCenterY(minY + 100, maxY - 100);

        for (int i = 0; i < clusterCount; i++) {
            clusterCenters.emplace_back(distCenterX(rng), distCenterY(rng));
        }

        // 分配每个边界框到聚类中心
        uniform_int_distribution<int> distCluster(0, clusterCount - 1);
        uniform_real_distribution<float> distOffset(-clusterRadius, clusterRadius);
        uniform_real_distribution<float> distSize(minSize, maxSize);
        uniform_real_distribution<float> distConf(minConf, maxConf);

        for (int i = 0; i < count; i++) {
            int clusterIdx = distCluster(rng);
            auto& center = clusterCenters[clusterIdx];

            float x = center.first + distOffset(rng);
            float y = center.second + distOffset(rng);

            // 确保在边界内
            x = max(minX + 5.0f, min(maxX - 5.0f, x));
            y = max(minY + 5.0f, min(maxY - 5.0f, y));

            float w = distSize(rng);
            float h = distSize(rng);
            float conf = distConf(rng);

            boxes.emplace_back(i, x, y, w, h, conf);
        }

        return boxes;
    }
};

#endif // DATAGENERATOR_H