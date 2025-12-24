#include <iostream>
#include <fstream>
#include <string>
#include "HuffCode.h"

using namespace std;

// 测试从文件构建
void testFromFile(const string& filename) {
    cout << "从文件构建Huffman编码" << endl;

    HuffCode huffman;

    // 从文件构建频率表
    huffman.buildFrequencyTable(filename);

    // 打印频率表
    huffman.printFrequencyTable();

    // 构建Huffman树
    huffman.buildHuffmanTree();

    // 打印编码表
    huffman.printCodeTable();

    // 打印Huffman树结构
    cout << endl;
    huffman.printHuffmanTree();

    // 编码示例单词
    cout << "\n示例 " << endl;
    string testWords[] = { "hello", "world", "test", "example" };
    for (const auto& word : testWords) {
        Bitmap encoded = huffman.encodeWord(word);
        cout << word << " -> " << encoded.toString() << endl;

        // 解码验证
        string decoded = huffman.decodeBitmap(encoded);
        cout << "解码: " << decoded << endl;

        // 验证结果
        string wordLower;
        for (char c : word) {
            wordLower += tolower(c);
        }

        if (decoded == wordLower) {
            cout << "编码解码成功" << endl;
        }
        else {
            cout << "编码解码失败" << endl;
        }
        cout << endl;
    }
}

// 测试从字符串构建
void testFromString(const string& text) {
    cout << "\n从字符串构建Huffman编码" << endl;
    cout << "输入文本: \"" << text << "\"" << endl << endl;

    HuffCode huffman;

    // 从字符串构建频率表
    huffman.buildFrequencyTableFromString(text);

    // 打印频率表
    huffman.printFrequencyTable();

    // 构建Huffman树
    huffman.buildHuffmanTree();

    // 打印编码表
    huffman.printCodeTable();

    // 打印Huffman树结构
    cout << endl;
    huffman.printHuffmanTree();

    // 编码整个文本
    cout << "\n完整编码解码测试" << endl;

    // 准备小写文本（只保留字母）
    string textLower;
    for (char c : text) {
        if (isalpha(c)) {
            textLower += tolower(c);
        }
    }

    cout << "待编码文本: " << textLower << endl;

    // 编码
    Bitmap encoded = huffman.encodeWord(textLower);
    cout << "编码结果 (" << encoded.getSize() << "位): " << encoded.toString() << endl;

    // 解码
    string decoded = huffman.decodeBitmap(encoded);
    cout << "解码结果: " << decoded << endl;

    // 验证
    if (decoded == textLower) {
        cout << "完整编码解码成功" << endl;
    }
    else {
        cout << "完整编码解码失败" << endl;
        cout << "原始: " << textLower << endl;
        cout << "解码: " << decoded << endl;
    }

    // 计算压缩率
    int originalBits = textLower.length() * 8; // ASCII编码
    int compressedBits = encoded.getSize();
    double compressionRatio = (1.0 - (double)compressedBits / originalBits) * 100;

    cout << "\n压缩统计" << endl;
    cout << "原始大小: " << originalBits << " 位" << endl;
    cout << "压缩大小: " << compressedBits << " 位" << endl;
    cout << "压缩率: " << compressionRatio << "%" << endl;
}

// 交互式测试
void interactiveTest() {
    cout << "\n交互式测试" << endl;

    HuffCode huffman;
    string input;

    cout << "请输入要编码的文本（输入'exit'退出）: ";
    getline(cin, input);

    while (input != "exit") {
        // 从输入构建频率表
        huffman.buildFrequencyTableFromString(input);

        // 构建Huffman树
        huffman.buildHuffmanTree();

        // 显示编码表
        huffman.printCodeTable();

        // 编码
        Bitmap encoded = huffman.encodeWord(input);
        cout << "\n编码结果 (" << encoded.getSize() << "位): " << encoded.toString() << endl;

        // 解码
        string decoded = huffman.decodeBitmap(encoded);
        cout << "解码结果: " << decoded << endl;

        // 准备小写文本（只保留字母）
        string inputLower;
        for (char c : input) {
            if (isalpha(c)) {
                inputLower += tolower(c);
            }
        }

        // 验证
        if (decoded == inputLower) {
            cout << "编码解码成功" << endl;
        }
        else {
            cout << "编码解码失败" << endl;
        }

        // 计算压缩率
        if (!inputLower.empty()) {
            int originalBits = inputLower.length() * 8;
            int compressedBits = encoded.getSize();
            double compressionRatio = (1.0 - (double)compressedBits / originalBits) * 100;
            cout << "压缩率: " << compressionRatio << "%" << endl;
        }

        cout << "\n请输入要编码的文本（输入'exit'退出）: ";
        getline(cin, input);
    }
}

int main() {
    cout << "Huffman编码测试" << endl;

    // 创建测试文件
    ofstream testFile("test.txt");
    if (testFile.is_open()) {
        testFile << "hello world this is a test of huffman coding\n";
        testFile << "huffman coding is a popular algorithm for lossless data compression\n";
        testFile << "the algorithm was developed by david a huffman while he was a phd student at mit\n";
        testFile.close();
        cout << "已创建测试文件 test.txt" << endl;
    }
    else {
        cout << "无法创建测试文件，将使用字符串测试" << endl;
    }

    // 测试1：从文件构建
    testFromFile("test.txt");

    // 测试2：从字符串构建
    string testText = "this is an example of a huffman tree";
    testFromString(testText);

    // 测试3：交互式测试
    interactiveTest();

    cout << "\n测试完成" << endl;

    return 0;
}