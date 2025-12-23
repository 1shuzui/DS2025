#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include <queue>
#include <functional>
using namespace std;

// 二叉树节点类
template <typename T>
class BinNode {
public:
    T data;
    BinNode<T>* parent;
    BinNode<T>* lc;  // 左孩子
    BinNode<T>* rc;  // 右孩子
    int height;      // 高度

    // 构造函数
    BinNode() : parent(nullptr), lc(nullptr), rc(nullptr), height(0) {}
    BinNode(T e, BinNode<T>* p = nullptr, BinNode<T>* l = nullptr,
        BinNode<T>* r = nullptr, int h = 0)
        : data(e), parent(p), lc(l), rc(r), height(h) {
    }

    // 统计子树规模
    int size() const {
        int s = 1;
        if (lc) s += lc->size();
        if (rc) s += rc->size();
        return s;
    }

    // 插入左孩子
    BinNode<T>* insertAsLC(const T& e) {
        return lc = new BinNode<T>(e, this);
    }

    // 插入右孩子
    BinNode<T>* insertAsRC(const T& e) {
        return rc = new BinNode<T>(e, this);
    }

    // 判断是否为叶节点
    bool isLeaf() const {
        return !lc && !rc;
    }
};

// 二叉树类
template <typename T>
class BinTree {
protected:
    int _size;               // 规模
    BinNode<T>* _root;       // 根节点

public:
    // 构造函数
    BinTree() : _size(0), _root(nullptr) {}
    BinTree(const T& e) : _size(1), _root(new BinNode<T>(e)) {}

    // 析构函数
    ~BinTree() {
        if (_size > 0) remove(_root);
    }

    // 获取规模
    int size() const { return _size; }

    // 判断是否为空
    bool empty() const { return !_root; }

    // 获取根节点
    BinNode<T>* root() const { return _root; }

    // 更新节点高度
    virtual int updateHeight(BinNode<T>* x) {
        int hl = x->lc ? x->lc->height : -1;
        int hr = x->rc ? x->rc->height : -1;
        return x->height = 1 + max(hl, hr);
    }

    // 更新节点及其祖先的高度
    void updateHeightAbove(BinNode<T>* x) {
        while (x) {
            updateHeight(x);
            x = x->parent;
        }
    }

    // 插入根节点
    BinNode<T>* insertAsRoot(const T& e) {
        _size = 1;
        return _root = new BinNode<T>(e);
    }

    // 插入左孩子
    BinNode<T>* insertAsLC(BinNode<T>* x, const T& e) {
        _size++;
        x->insertAsLC(e);
        updateHeightAbove(x);
        return x->lc;
    }

    // 插入右孩子
    BinNode<T>* insertAsRC(BinNode<T>* x, const T& e) {
        _size++;
        x->insertAsRC(e);
        updateHeightAbove(x);
        return x->rc;
    }

    // 先序遍历
    template <typename VST>
    void travPre(VST& visit) {
        if (_root) travPre(_root, visit);
    }

    template <typename VST>
    void travPre(BinNode<T>* x, VST& visit) {
        if (!x) return;
        visit(x->data);
        travPre(x->lc, visit);
        travPre(x->rc, visit);
    }

    // 中序遍历
    template <typename VST>
    void travIn(VST& visit) {
        if (_root) travIn(_root, visit);
    }

    template <typename VST>
    void travIn(BinNode<T>* x, VST& visit) {
        if (!x) return;
        travIn(x->lc, visit);
        visit(x->data);
        travIn(x->rc, visit);
    }

    // 后序遍历
    template <typename VST>
    void travPost(VST& visit) {
        if (_root) travPost(_root, visit);
    }

    template <typename VST>
    void travPost(BinNode<T>* x, VST& visit) {
        if (!x) return;
        travPost(x->lc, visit);
        travPost(x->rc, visit);
        visit(x->data);
    }

    // 层次遍历
    template <typename VST>
    void travLevel(VST& visit) {
        if (!_root) return;
        queue<BinNode<T>*> q;
        q.push(_root);
        while (!q.empty()) {
            BinNode<T>* x = q.front();
            q.pop();
            visit(x->data);
            if (x->lc) q.push(x->lc);
            if (x->rc) q.push(x->rc);
        }
    }

    // 移除子树
    int remove(BinNode<T>* x) {
        if (!x) return 0;
        int n = 1 + remove(x->lc) + remove(x->rc);
        delete x;
        return n;
    }

    // 统计叶节点数量
    int countLeaves() const {
        if (!_root) return 0;
        return countLeaves(_root);
    }

private:
    int countLeaves(BinNode<T>* x) const {
        if (!x) return 0;
        if (x->isLeaf()) return 1;
        return countLeaves(x->lc) + countLeaves(x->rc);
    }
};

#endif // BINTREE_H