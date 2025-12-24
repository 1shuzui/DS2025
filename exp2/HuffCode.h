#ifndef HUFFCODE_H
#define HUFFCODE_H

#include "HuffTree.h"
#include <fstream>
#include <cctype>
#include <algorithm>
using namespace std;

class HuffCode {
private:
    map<char, int> freqMap;      // 频率表
    HuffTree* huffTree;          // Huffman树
    map<char, Bitmap> codeTable; // 编码表

public:
    // 构造函数
    HuffCode() : huffTree(nullptr) {}

    // 析构函数
    ~HuffCode() {
        if (huffTree) {
            delete huffTree;
        }
    }

    // 从文件构建频率表
    void buildFrequencyTable(const string& filename) {
        freqMap.clear();
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "无法打开文件: " << filename << endl;
            return;
        }

        char c;
        while (file.get(c)) {
            if (isalpha(c)) {
                char lowerC = tolower(c);
                freqMap[lowerC]++;
            }
        }
        file.close();

        // 只保留26个字母
        map<char, int> filteredMap;
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (freqMap.find(ch) != freqMap.end()) {
                filteredMap[ch] = freqMap[ch];
            }
        }
        freqMap = filteredMap;
    }

    // 从字符串构建频率表
    void buildFrequencyTableFromString(const string& text) {
        freqMap.clear();
        for (char c : text) {
            if (isalpha(c)) {
                char lowerC = tolower(c);
                freqMap[lowerC]++;
            }
        }

        // 只保留26个字母
        map<char, int> filteredMap;
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (freqMap.find(ch) != freqMap.end()) {
                filteredMap[ch] = freqMap[ch];
            }
        }
        freqMap = filteredMap;
    }

    // 构建Huffman树
    void buildHuffmanTree() {
        if (huffTree) {
            delete huffTree;
        }
        huffTree = HuffTree::buildHuffTree(freqMap);
        if (huffTree) {
            codeTable = huffTree->getCodeTable();
        }
    }

    // 获取编码表
    const map<char, Bitmap>& getCodeTable() const {
        return codeTable;
    }

    // 编码单词
    Bitmap encodeWord(const string& word) const {
        Bitmap result;
        for (char c : word) {
            char lowerC = tolower(c);
            if (codeTable.find(lowerC) != codeTable.end()) {
                result.append(codeTable.at(lowerC));
            }
        }
        return result;
    }

    // 解码位图
    string decodeBitmap(const Bitmap& bm) const {
        if (!huffTree || !huffTree->root()) {
            cerr << "Huffman树未构建或为空" << endl;
            return "";
        }

        string result;
        BinNode<HuffChar>* current = huffTree->root();

        // 处理每个位
        for (size_t i = 0; i < bm.getSize(); i++) {
            if (bm.test(i)) {
                // 位为1，走右子树
                current = current->rc;
            }
            else {
                // 位为0，走左子树
                current = current->lc;
            }

            // 检查是否为空
            if (!current) {
                cerr << "解码错误：无效的编码路径" << endl;
                return "";
            }

            // 如果是叶节点，添加字符并回到根节点
            if (current->isLeaf()) {
                result += current->data.ch;
                current = huffTree->root();
            }
        }

        // 检查是否结束在非叶节点
        if (current != huffTree->root()) {
            cerr << "警告：编码不完整，部分位未处理" << endl;
        }

        return result;
    }

    // 打印频率表
    void printFrequencyTable() const {
        cout << "字符频率表：" << endl;
        cout << "------------" << endl;
        int total = 0;
        for (const auto& pair : freqMap) {
            cout << pair.first << ": " << pair.second << endl;
            total += pair.second;
        }
        cout << "------------" << endl;
        cout << "总计: " << total << " 个字母" << endl;
    }

    // 打印编码表
    void printCodeTable() const {
        cout << "\nHuffman编码表：" << endl;
        cout << "------------" << endl;
        for (const auto& pair : codeTable) {
            cout << pair.first << ": " << pair.second.toString() << endl;
        }
    }

    // 打印Huffman树
    void printHuffmanTree() const {
        if (huffTree) {
            huffTree->printTree();
        }
    }
};

#endif // HUFFCODE_H