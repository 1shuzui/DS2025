#ifndef HUFFTREE_H
#define HUFFTREE_H

#include "BinTree.h"
#include "Bitmap.h"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

// Huffman字符结构
struct HuffChar {
    char ch;       // 字符
    int weight;    // 权重（频率）

    HuffChar(char c = '^', int w = 0) : ch(c), weight(w) {}

    bool operator<(const HuffChar& hc) const {
        return weight < hc.weight;
    }

    bool operator==(const HuffChar& hc) const {
        return weight == hc.weight;
    }

    friend ostream& operator<<(ostream& os, const HuffChar& hc) {
        if (hc.ch == '^') {
            os << "{" << hc.weight << "}";
        }
        else {
            os << "{" << hc.ch << ":" << hc.weight << "}";
        }
        return os;
    }
};

// Huffman树类
class HuffTree : public BinTree<HuffChar> {
private:
    // 生成编码表
    void generateCode(BinNode<HuffChar>* x, Bitmap& code, map<char, Bitmap>& codeTable) {
        if (!x) return;

        // 如果是叶节点（存储字符）
        if (x->isLeaf() && x->data.ch != '^') {
            codeTable[x->data.ch] = code;
            return;
        }

        // 向左遍历
        code.append(false);  // 添加0
        generateCode(x->lc, code, codeTable);
        code.pop();  // 移除最后一位

        // 向右遍历
        code.append(true);   // 添加1
        generateCode(x->rc, code, codeTable);
        code.pop();  // 移除最后一位
    }

    // 附加子树作为左孩子
    void attachAsLC(BinNode<HuffChar>* x, HuffTree*& t) {
        if (!x || !t) return;
        x->lc = t->root();
        if (x->lc) x->lc->parent = x;
        _size += t->size();
        updateHeightAbove(x);
        t->_root = nullptr;
        delete t;
        t = nullptr;
    }

    // 附加子树作为右孩子
    void attachAsRC(BinNode<HuffChar>* x, HuffTree*& t) {
        if (!x || !t) return;
        x->rc = t->root();
        if (x->rc) x->rc->parent = x;
        _size += t->size();
        updateHeightAbove(x);
        t->_root = nullptr;
        delete t;
        t = nullptr;
    }

public:
    // 根据频率构建Huffman树
    static HuffTree* buildHuffTree(const map<char, int>& freqMap) {
        if (freqMap.empty()) return nullptr;

        // 创建叶节点森林
        vector<HuffTree*> forest;
        for (const auto& pair : freqMap) {
            HuffTree* tree = new HuffTree();
            tree->insertAsRoot(HuffChar(pair.first, pair.second));
            forest.push_back(tree);
        }

        // 按权重排序（从小到大）
        sort(forest.begin(), forest.end(),
            [](HuffTree* a, HuffTree* b) {
                return a->root()->data.weight < b->root()->data.weight;
            });

        // 构建Huffman树
        while (forest.size() > 1) {
            // 取出权重最小的两棵树
            HuffTree* t1 = forest[0];
            HuffTree* t2 = forest[1];

            // 创建新树，权重为两棵树之和
            HuffTree* newTree = new HuffTree();
            newTree->insertAsRoot(HuffChar('^',
                t1->root()->data.weight + t2->root()->data.weight));

            // 将t1和t2作为新树的左右子树
            newTree->attachAsLC(newTree->root(), t1);
            newTree->attachAsRC(newTree->root(), t2);

            // 从森林中移除t1和t2
            forest.erase(forest.begin(), forest.begin() + 2);

            // 将新树插入森林并保持有序
            auto it = lower_bound(forest.begin(), forest.end(), newTree,
                [](HuffTree* a, HuffTree* b) {
                    return a->root()->data.weight < b->root()->data.weight;
                });
            forest.insert(it, newTree);
        }

        return forest.empty() ? nullptr : forest[0];
    }

    // 获取编码表
    map<char, Bitmap> getCodeTable() {
        map<char, Bitmap> codeTable;
        Bitmap code;
        generateCode(_root, code, codeTable);
        return codeTable;
    }

    // 打印树结构
    void printTree() const {
        cout << "Huffman树结构：" << endl;
        printTree(_root, "", true);
    }

private:
    // 打印树结构（辅助函数）
    void printTree(BinNode<HuffChar>* x, const string& prefix, bool isLeft) const {
        if (!x) return;

        cout << prefix;
        cout << (isLeft ? "├──" : "└──");
        cout << x->data << endl;

        // 递归打印子节点
        printTree(x->lc, prefix + (isLeft ? "│   " : "    "), true);
        printTree(x->rc, prefix + (isLeft ? "│   " : "    "), false);
    }
};

#endif // HUFFTREE_H