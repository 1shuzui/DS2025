#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "HuffCode.h"

using namespace std;

// 检查文件是否存在
bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

// 尝试从多个位置读取文件
string tryReadFile() {
    // 尝试不同的文件路径
    vector<string> possiblePaths = {
        "I_have_a_dream.txt",  // 当前目录
        "../I_have_a_dream.txt",  // 上级目录
        "../../I_have_a_dream.txt",  // 上上级目录
        "./演讲原文.txt",  // 中文文件名
        "演讲原文.txt"
    };

    for (const auto& path : possiblePaths) {
        if (fileExists(path)) {
            ifstream file(path);
            string content((istreambuf_iterator<char>(file)),
                istreambuf_iterator<char>());
            cout << "成功读取文件: " << path << endl;
            return content;
        }
    }


    int main()
        ; {


    // 创建Huffman编码器
    HuffCode huffCode;

    // 读取文本内容
    cout << "\n正在读取文本..." << endl;
    string textContent = tryReadFile();

    // 从字符串构建频率表
    huffCode.buildFrequencyTableFromString(textContent);

    cout << "\n1. 字符频率统计：" << endl;
    huffCode.printFrequencyTable();

    // 构建Huffman树
    cout << "\n2. 构建Huffman树..." << endl;
    huffCode.buildHuffmanTree();

    // 打印编码表
    huffCode.printCodeTable();

    // 打印Huffman树结构
    cout << "\n3. Huffman树结构：" << endl;
    huffCode.printHuffmanTree();

    // 编码测试单词
    cout << "\n4. 单词编码测试：" << endl;
    cout << "=========================================" << endl;

    vector<string> testWords = { "dream", "freedom", "justice", "equality", "hope", "brotherhood" };

    for (const string& word : testWords) {
        Bitmap code = huffCode.encodeWord(word);
        cout << word << " 的编码: " << code << endl;
        cout << "  长度: " << code.getSize() << " 位" << endl;
        cout << "  " << string(40, '-') << endl;
    }

    // 演示解码功能
    cout << "\n5. 解码演示：" << endl;
    string testWord = "dream";
    Bitmap testCode = huffCode.encodeWord(testWord);
    cout << "原始单词: " << testWord << endl;
    cout << "编码: " << testCode << endl;

    string decoded = huffCode.decodeBitmap(testCode);
    cout << "解码结果: " << decoded << endl;

    // 显示一些统计信息
    cout << "\n6. 统计信息：" << endl;
    cout << "=========================================" << endl;
    cout << "文本总字符数: " << textContent.length() << endl;

    // 计算压缩效率
    const auto& codeTable = huffCode.getCodeTable();
    int totalBits = 0;
    for (const auto& pair : codeTable) {
        totalBits += pair.second.getSize();
    }

    double avgCodeLength = codeTable.empty() ? 0 :
        static_cast<double>(totalBits) / codeTable.size();
    cout << "平均编码长度: " << avgCodeLength << " 位/字符" << endl;
    cout << "固定长度编码需要: 5 位/字符" << endl;
    cout << "编码效率提升: " << (1 - avgCodeLength / 5) * 100 << "%" << endl;

    return 0;
}