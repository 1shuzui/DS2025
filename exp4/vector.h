#ifndef VECTOR_AND_UTILS_H
#define VECTOR_AND_UTILS_H

#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <stdexcept>
using namespace std;

// ============================ 复数类 ============================
class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    double modulus() const {
        return sqrt(real * real + imag * imag);
    }

    double getReal() const { return real; }
    double getImag() const { return imag; }

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    bool operator<(const Complex& other) const {
        double mod1 = modulus();
        double mod2 = other.modulus();
        if (mod1 != mod2) return mod1 < mod2;
        return real < other.real;
    }

    bool operator>(const Complex& other) const {
        return other < *this;
    }

    bool operator<=(const Complex& other) const {
        return !(other < *this);
    }

    bool operator>=(const Complex& other) const {
        return !(*this < other);
    }

    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << "(" << c.real << " + " << c.imag << "i)";
        return os;
    }
};

// ============================ Vector类 ============================
typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T>
class Vector {
protected:
    Rank _size;
    int _capacity;
    T* _elem;

    void copyFrom(T const* A, Rank lo, Rank hi) {
        _elem = new T[_capacity = 2 * (hi - lo)];
        _size = 0;
        while (lo < hi)
            _elem[_size++] = A[lo++];
    }

    void expand() {
        if (_size < _capacity) return;
        if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
        T* oldElem = _elem;
        _elem = new T[_capacity <<= 1];
        for (int i = 0; i < _size; i++)
            _elem[i] = oldElem[i];
        delete[] oldElem;
    }

    void shrink() {
        if (_capacity < DEFAULT_CAPACITY << 1) return;
        if (_size << 2 > _capacity) return;
        T* oldElem = _elem;
        _elem = new T[_capacity >>= 1];
        for (int i = 0; i < _size; i++)
            _elem[i] = oldElem[i];
        delete[] oldElem;
    }

    bool bubble(Rank lo, Rank hi) {
        bool sorted = true;
        while (++lo < hi) {
            if (_elem[lo - 1] > _elem[lo]) {
                sorted = false;
                swap(_elem[lo - 1], _elem[lo]);
            }
        }
        return sorted;
    }

    void merge(Rank lo, Rank mi, Rank hi) {
        T* A = _elem + lo;
        int lb = mi - lo;
        T* B = new T[lb];
        for (Rank i = 0; i < lb; i++)
            B[i] = A[i];

        int lc = hi - mi;
        T* C = _elem + mi;

        for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc); ) {
            if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))
                A[i++] = B[j++];
            if ((k < lc) && (!(j < lb) || (C[k] < B[j])))
                A[i++] = C[k++];
        }
        delete[] B;
    }

public:
    // 构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    }

    Vector(T const* A, Rank n) { copyFrom(A, 0, n); }
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }

    // 析构函数
    ~Vector() { delete[] _elem; }

    // 赋值操作符
    Vector<T>& operator=(Vector<T> const& V) {
        if (_elem) delete[] _elem;
        copyFrom(V._elem, 0, V.size());
        return *this;
    }

    // 只读访问接口
    Rank size() const { return _size; }
    bool empty() const { return !_size; }

    int disordered() const {
        int n = 0;
        for (int i = 1; i < _size; i++)
            if (_elem[i - 1] > _elem[i]) n++;
        return n;
    }

    Rank find(T const& e) const { return find(e, 0, _size); }

    Rank find(T const& e, Rank lo, Rank hi) const {
        while ((lo < hi--) && (e != _elem[hi]));
        return hi;
    }

    Rank search(T const& e) const {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }

    Rank search(T const& e, Rank lo, Rank hi) const {
        // 简化版本：顺序查找，你可以替换为二分查找
        for (Rank i = lo; i < hi; i++) {
            if (_elem[i] == e) return i;
        }
        return -1;
    }

    // 可写访问接口
    T& operator[](Rank r) const { return _elem[r]; }

    T remove(Rank r) {
        T e = _elem[r];
        remove(r, r + 1);
        return e;
    }

    int remove(Rank lo, Rank hi) {
        if (lo == hi) return 0;
        while (hi < _size)
            _elem[lo++] = _elem[hi++];
        _size = lo;
        shrink();
        return hi - lo;
    }

    Rank insert(Rank r, T const& e) {
        expand();
        for (int i = _size; i > r; i--)
            _elem[i] = _elem[i - 1];
        _elem[r] = e;
        _size++;
        return r;
    }

    Rank insert(T const& e) { return insert(_size, e); }

    void sort(Rank lo, Rank hi) {
        // 简化：使用归并排序
        mergeSort(lo, hi);
    }

    void sort() { sort(0, _size); }

    void unsort(Rank lo, Rank hi) {
        T* V = _elem + lo;
        for (Rank i = hi - lo; i > 0; i--)
            swap(V[i - 1], V[rand() % i]);
    }

    void unsort() { unsort(0, _size); }

    int deduplicate() {
        int oldSize = _size;
        Rank i = 1;
        while (i < _size)
            (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
        return oldSize - _size;
    }

    int uniquify() {
        Rank i = 0, j = 0;
        while (++j < _size)
            if (_elem[i] != _elem[j])
                _elem[++i] = _elem[j];
        _size = ++i;
        shrink();
        return j - i;
    }

    // 排序算法
    void bubbleSort(Rank lo, Rank hi) {
        while (!bubble(lo, hi--));
    }

    void mergeSort(Rank lo, Rank hi) {
        if (hi - lo < 2) return;
        int mi = (lo + hi) >> 1;
        mergeSort(lo, mi);
        mergeSort(mi, hi);
        merge(lo, mi, hi);
    }

    void selectionSort(Rank lo, Rank hi) {
        // 简化实现
        for (Rank i = lo; i < hi; i++) {
            Rank minIndex = i;
            for (Rank j = i + 1; j < hi; j++) {
                if (_elem[j] < _elem[minIndex]) {
                    minIndex = j;
                }
            }
            swap(_elem[i], _elem[minIndex]);
        }
    }

    void quickSort(Rank lo, Rank hi) {
        // 简化实现
        if (hi - lo < 2) return;
        Rank mi = partition(lo, hi - 1);
        quickSort(lo, mi);
        quickSort(mi + 1, hi);
    }

    void heapSort(Rank lo, Rank hi) {
        // 简化实现
        Vector<T> temp;
        for (Rank i = lo; i < hi; i++) {
            temp.insert(_elem[i]);
        }
        temp.mergeSort(0, temp.size());
        for (Rank i = lo; i < hi; i++) {
            _elem[i] = temp[i - lo];
        }
    }

    Rank partition(Rank lo, Rank hi) {
        // 简化实现
        T pivot = _elem[hi];
        Rank i = lo - 1;
        for (Rank j = lo; j < hi; j++) {
            if (_elem[j] <= pivot) {
                i++;
                swap(_elem[i], _elem[j]);
            }
        }
        swap(_elem[i + 1], _elem[hi]);
        return i + 1;
    }

    // 遍历
    void traverse(void (*visit)(T&)) {
        for (int i = 0; i < _size; i++)
            visit(_elem[i]);
    }

    template <typename VST>
    void traverse(VST& visit) {
        for (int i = 0; i < _size; i++)
            visit(_elem[i]);
    }
};

// ============================ 栈类 ============================
template <typename T>
class Stack {
private:
    Vector<T> data;

public:
    void push(const T& value) {
        data.insert(value);
    }

    T pop() {
        if (empty()) {
            throw runtime_error("Stack underflow");
        }
        return data.remove(data.size() - 1);
    }

    T top() const {
        if (empty()) {
            throw runtime_error("Stack underflow");
        }
        return data[data.size() - 1];
    }

    bool empty() const {
        return data.empty();
    }

    int size() const {
        return data.size();
    }
};

// ============================ 计算器类 ============================
class Calculator {
private:
    static int getPriority(char op) {
        switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
        }
    }

    static double calculate(double a, double b, char op) {
        switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw runtime_error("Division by zero");
            return a / b;
        case '^': return pow(a, b);
        default: throw runtime_error("Unknown operator");
        }
    }

    static void processOperator(Stack<double>& numbers, Stack<char>& operators) {
        if (numbers.size() < 2) throw runtime_error("Invalid expression");

        double b = numbers.pop();
        double a = numbers.pop();
        char op = operators.pop();

        numbers.push(calculate(a, b, op));
    }

public:
    static double evaluate(const string& expression) {
        Stack<double> numbers;
        Stack<char> operators;

        for (size_t i = 0; i < expression.length(); i++) {
            char c = expression[i];

            if (isspace(c)) {
                continue;
            }
            else if (isdigit(c) || c == '.') {
                string numStr;
                while (i < expression.length() &&
                    (isdigit(expression[i]) || expression[i] == '.')) {
                    numStr += expression[i++];
                }
                i--;
                numbers.push(stod(numStr));
            }
            else if (c == '(') {
                operators.push(c);
            }
            else if (c == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    processOperator(numbers, operators);
                }
                if (operators.empty()) throw runtime_error("Mismatched parentheses");
                operators.pop();
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                while (!operators.empty() &&
                    getPriority(operators.top()) >= getPriority(c)) {
                    processOperator(numbers, operators);
                }
                operators.push(c);
            }
            else {
                throw runtime_error("Invalid character in expression");
            }
        }

        while (!operators.empty()) {
            processOperator(numbers, operators);
        }

        if (numbers.size() != 1) throw runtime_error("Invalid expression");

        return numbers.pop();
    }
};

// ============================ 工具函数 ============================
// 柱状图最大面积函数
template <typename T>
int largestRectangleArea(Vector<T>& heights) {
    Stack<int> stack;
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i <= n; i++) {
        int currentHeight = (i == n) ? 0 : heights[i];

        while (!stack.empty() && currentHeight < heights[stack.top()]) {
            int height = heights[stack.pop()];
            int width = stack.empty() ? i : i - stack.top() - 1;
            maxArea = max(maxArea, height * width);
        }

        stack.push(i);
    }

    return maxArea;
}

// 辅助函数：用于遍历测试
template <typename T>
struct Increase {
    void operator()(T& e) { e++; }
};

template <typename T>
void increase(Vector<T>& V) {
    V.traverse(Increase<T>());
}

#endif // VECTOR_AND_UTILS_H