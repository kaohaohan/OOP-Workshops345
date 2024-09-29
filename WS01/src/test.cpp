#include <iostream>
#include <fstream>
#include "dictionary.h"

using namespace std;
using namespace seneca;

// 将字典的内容写入文本文件
void writeDictionaryToFile(const Dictionary& dict, const std::string& filename) {
    // 创建输出文件流
    std::ofstream outFile(filename);

    // 检查文件是否成功打开
    if (!outFile) {
        std::cerr << "Could not open the file for writing: " << filename << std::endl;
        return;
    }

    const Word* words = dict.getWords();  // 获取单词数组
    size_t size = dict.getSize();         // 获取单词数组的大小

    // 遍历并输出每个单词到文件
    for (size_t i = 0; i < size; ++i) {
        // 输出单词
        outFile << "Word: " << words[i].m_word << std::endl;

        // 输出词性
        std::string posStr = partOfSpeechToString(words[i].m_pos);
        outFile << "Part of Speech: " << posStr << std::endl;

        // 输出定义
        outFile << "Definition: " << words[i].m_definition << std::endl;

        outFile << "---------------------------------" << std::endl;
    }

    // 关闭文件流
    outFile.close();
    std::cout << "Dictionary has been written to " << filename << std::endl;
}

int main(int argc, char** argv) {

    // 创建字典对象并加载文件
    Dictionary dict(argv[1]);

    // 定义输出文件名
    std::string outputFilename = "dictionary_output.txt";

    // 将字典内容写入文本文件
    writeDictionaryToFile(dict, outputFilename);

    return 0;
}
