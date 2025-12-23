#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class BoundingBox {
public:
    int id;           // 边界框ID
    float x, y;       // 中心点坐标
    float width;      // 宽度
    float height;     // 高度
    float confidence; // 置信度

    // 构造函数
    BoundingBox(int id = 0, float x = 0, float y = 0, float w = 0, float h = 0, float conf = 0)
        : id(id), x(x), y(y), width(w), height(h), confidence(conf) {
    }

    // 获取左上角坐标
    float getLeft() const { return x - width / 2; }
    float getTop() const { return y - height / 2; }

    // 获取右下角坐标
    float getRight() const { return x + width / 2; }
    float getBottom() const { return y + height / 2; }

    // 计算面积
    float area() const { return width * height; }

    // 计算两个边界框的交并比(IoU)
    float computeIoU(const BoundingBox& other) const {
        // 计算交集的坐标
        float interLeft = max(getLeft(), other.getLeft());
        float interTop = max(getTop(), other.getTop());
        float interRight = min(getRight(), other.getRight());
        float interBottom = min(getBottom(), other.getBottom());

        // 计算交集面积
        float interWidth = max(0.0f, interRight - interLeft);
        float interHeight = max(0.0f, interBottom - interTop);
        float interArea = interWidth * interHeight;

        // 计算并集面积
        float unionArea = area() + other.area() - interArea;

        // 避免除以0
        if (unionArea == 0) return 0;

        return interArea / unionArea;
    }

    // 比较运算符（按置信度降序）
    bool operator<(const BoundingBox& other) const {
        return confidence > other.confidence; // 降序排序
    }
};

#endif // BOUNDINGBOX_H