#ifndef BITMAP_H
#define BITMAP_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class Bitmap {
private:
    vector<unsigned char> data;  // 用无符号字符存储位
    size_t size;                 // 当前位数

public:
    // 构造函数
    Bitmap() : size(0) {}

    Bitmap(const string& bitStr) : size(0) {
        for (char c : bitStr) {
            if (c == '1') set(size++);
            else if (c == '0') clear(size++);
            else throw invalid_argument("Bitmap字符串只能包含'0'和'1'");
        }
    }

    // 获取位图大小
    size_t getSize() const { return size; }

    // 设置位
    void set(size_t pos) {
        ensureCapacity(pos);
        size_t byteIndex = pos / 8;
        size_t bitIndex = pos % 8;
        data[byteIndex] |= (1 << bitIndex);
        if (pos >= size) size = pos + 1;
    }

    // 清除位
    void clear(size_t pos) {
        ensureCapacity(pos);
        size_t byteIndex = pos / 8;
        size_t bitIndex = pos % 8;
        data[byteIndex] &= ~(1 << bitIndex);
        if (pos >= size) size = pos + 1;
    }

    // 测试位
    bool test(size_t pos) const {
        if (pos >= size) return false;
        size_t byteIndex = pos / 8;
        size_t bitIndex = pos % 8;
        return (data[byteIndex] & (1 << bitIndex)) != 0;
    }

    // 追加位
    void append(bool bit) {
        if (bit) set(size);
        else clear(size);
    }

    // 追加位图
    void append(const Bitmap& other) {
        for (size_t i = 0; i < other.size; i++) {
            append(other.test(i));
        }
    }

    // 转换为字符串
    string toString() const {
        string result;
        for (size_t i = 0; i < size; i++) {
            result += test(i) ? '1' : '0';
        }
        return result;
    }

    // 删除最后一位
    void pop() {
        if (size > 0) {
            size--;
        }
    }

    // 重载输出运算符
    friend ostream& operator<<(ostream& os, const Bitmap& bm) {
        os << bm.toString();
        return os;
    }

private:
    // 确保容量足够
    void ensureCapacity(size_t pos) {
        size_t byteNeeded = pos / 8 + 1;
        if (byteNeeded > data.size()) {
            data.resize(byteNeeded, 0);
        }
    }
};

#endif // BITMAP_H