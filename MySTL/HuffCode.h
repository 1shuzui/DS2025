#ifndef HUFFCODE_H
#define HUFFCODE_H

#include "Bitmap.h"
#include "HuffTree.h"
#include <fstream>
#include <cctype>
#include <algorithm>
using namespace std;

class HuffCode {
private:
    map<char, int> freqMap;      // 字符频率表
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

    // 从文本文件构建频率表
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

    // 解码位图（仅用于演示）
    string decodeBitmap(const Bitmap& bm) const {
        string result;
        BinNode<HuffChar>* current = huffTree->root();

        for (size_t i = 0; i < bm.getSize(); i++) {
            if (bm.test(i)) {
                current = current->rc;
            }
            else {
                current = current->lc;
            }

            if (!current) {
                cerr << "解码错误：无效的位图" << endl;
                return "";
            }

            if (current->isLeaf()) {
                result += current->data.ch;
                current = huffTree->root();
            }
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
            cout << pair.first << ": " << pair.second << endl;
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