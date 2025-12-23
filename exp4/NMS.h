#ifndef NMS_H
#define NMS_H

#include "BoundingBox.h"
#include <vector>
#include <algorithm>
using namespace std;

class NMS {
private:
    float iouThreshold;  // IoU阈值

public:
    NMS(float threshold = 0.5) : iouThreshold(threshold) {}

    // 使用标准库排序的基本NMS算法
    vector<BoundingBox> standardNMS(vector<BoundingBox> boxes) {
        vector<BoundingBox> result;

        // 按置信度降序排序
        sort(boxes.begin(), boxes.end());

        // 标准NMS算法
        while (!boxes.empty()) {
            // 选取置信度最高的边界框
            BoundingBox current = boxes[0];
            result.push_back(current);
            boxes.erase(boxes.begin());

            // 移除与当前边界框IoU超过阈值的边界框
            vector<BoundingBox> remaining;
            for (const auto& box : boxes) {
                if (current.computeIoU(box) < iouThreshold) {
                    remaining.push_back(box);
                }
            }
            boxes = move(remaining);
        }

        return result;
    }

    // 计算NMS后的压缩率
    float computeCompressionRate(const vector<BoundingBox>& original,
        const vector<BoundingBox>& nmsResult) {
        if (original.empty()) return 0;
        return 1.0f - static_cast<float>(nmsResult.size()) / original.size();
    }

    // 验证NMS结果
    bool verifyNMSResult(const vector<BoundingBox>& result) {
        for (size_t i = 0; i < result.size(); i++) {
            for (size_t j = i + 1; j < result.size(); j++) {
                if (result[i].computeIoU(result[j]) >= iouThreshold) {
                    return false;
                }
            }
        }
        return true;
    }
};

#endif // NMS_H