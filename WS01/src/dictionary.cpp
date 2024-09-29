#include "dictionary.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include "settings.h"
using namespace std;
namespace seneca{
    Dictionary::~Dictionary() {
        delete[] m_words;
    }

    Dictionary::Dictionary(const char* filename) {
        loadFromFile(filename);
    }

    // Copy constructor
    Dictionary::Dictionary(const Dictionary& other) : m_size(other.m_size) {
        m_words = new Word[m_size];
        for (size_t i = 0; i < m_size; ++i) {
            m_words[i] = other.m_words[i];  // Copy each word
        }
    }

    // Copy assignment operator
    Dictionary& Dictionary::operator=(const Dictionary& other) {
        if (this != &other) {
            delete[] m_words;  // Free the current memory
            m_size = other.m_size;
            m_words = new Word[m_size];
            for (size_t i = 0; i < m_size; ++i) {
                m_words[i] = other.m_words[i];  // Copy each word
            }
        }
        return *this;
    }

    // Move constructor
    Dictionary::Dictionary(Dictionary&& other) noexcept : m_words(other.m_words), m_size(other.m_size) {
        other.m_words = nullptr;
        other.m_size = 0;
    }

    // Move assignment operator
    Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
        if (this != &other) {
            delete[] m_words;  // Free the current memory
            m_words = other.m_words;
            m_size = other.m_size;

            other.m_words = nullptr;
            other.m_size = 0;
        }
        return *this;
    }
    
    PartOfSpeech Dictionary::getPartOfSpeech(const std::string& pos){
         if (pos == "n." || pos == "n. pl.") {
        return PartOfSpeech::Noun;
    } else if (pos == "adv.") {
        return PartOfSpeech::Adverb;
    } else if (pos == "a.") {
        return PartOfSpeech::Adjective;
    } else if (pos == "v." || pos == "v. i." || pos == "v. t." || pos == "v. t. & i.") {
        return PartOfSpeech::Verb;
    } else if (pos == "prep.") {
        return PartOfSpeech::Preposition;
    } else if (pos == "pron.") {
        return PartOfSpeech::Pronoun;
    } else if (pos == "conj.") {
        return PartOfSpeech::Conjunction;
    } else if (pos == "interj.") {
        return PartOfSpeech::Interjection;
    } else {
        return PartOfSpeech::Unknown;  
    }
    }
    void Dictionary::loadFromFile(const char* filename){
        std::ifstream file(filename);
        if (!file.is_open()) {
                throw runtime_error("Could not open file");
                return;
        }
     
        std::string line;
        int count=0;
        
        while (std::getline(file, line)) {
            if(!line.empty()){
                count++;
            }
        }
        file.clear() ;
        file.seekg(0);
        // cout<<count<< endl;
        m_size =count;
        m_words = new Word[m_size];

        int currentIndex=0;
        while (std::getline(file, line)) {
            if(!line.empty()){
                std::istringstream iss(line);
                std::string word, pos, definition;
                    // 使用逗號來分隔每個字段
                if (std::getline(iss, word, ',') && std::getline(iss, pos, ',') && std::getline(iss, definition)) {
                    // if (word.empty()) word = "[Empty Word]";
                    
                    Word readWord;
                    readWord.m_word = word;
                    if (pos.empty()){
                        readWord.m_pos=PartOfSpeech::Unknown;
                    } else{
                        readWord.m_pos =getPartOfSpeech(pos);
                    }
                    readWord.m_definition=definition;
                    m_words[currentIndex] = readWord;
                    //go to next index
                    currentIndex++;
            }
            }
        }
        file.close();
    }
    std::string partOfSpeechToString(PartOfSpeech pos) {
        switch (pos) {
            case PartOfSpeech::Noun:
                return "noun";
            case PartOfSpeech::Pronoun:
                return "pronoun";
            case PartOfSpeech::Adjective:
                return "adjective";
            case PartOfSpeech::Adverb:
                return "adverb";
            case PartOfSpeech::Verb:
                return "verb";
            case PartOfSpeech::Preposition:
                return "preposition";
            case PartOfSpeech::Conjunction:
                return "conjunction";
            case PartOfSpeech::Interjection:
                return "interjection";
            default:
                return "unknown";
        }
    }


     void Dictionary::searchWord(const char* word)  {
        bool found = false; 
        size_t word_length = std::strlen(word);  
          
        for (size_t i = 0; i < m_size; ++i) {
            if (m_words[i].m_word == std::string(word)) {
                found = true;
                std::cout << m_words[i].m_word << " - ";
                if (g_settings.m_verbose) {
                    if(m_words[i].m_pos != PartOfSpeech::Unknown){
                        cout << "("<< partOfSpeechToString(m_words[i].m_pos) << ")";
                    }
                    if(m_words[i].m_pos != PartOfSpeech::Unknown){
                           std::cout << " ";
                        }
                }
                cout << m_words[i].m_definition << std::endl;

                // 如果全局設置不允許顯示所有定義，則返回
                if (!g_settings.m_show_all) {
                    return;
                }

                // 繼續輸出後續的定義，如果有多個定義
                for (size_t j = i + 1; j < m_size; ++j) {
                    if(m_words[j].m_word == word){
                        std::cout << std::setw(word_length+1) << " ";  
                        std::cout << "- ";
                        if (g_settings.m_verbose && m_words[j].m_pos != PartOfSpeech::Unknown) {
                            std::cout << "(" << partOfSpeechToString(m_words[j].m_pos) << ")";
                        }
                        if(m_words[j].m_pos != PartOfSpeech::Unknown){
                           std::cout << " ";
                        }
                        cout << m_words[j].m_definition << std::endl;

                    }
             
                    
                }
                return;  // 找到並打印完畢後退出
            }
        }

        // 如果沒找到詞語，打印未找到的消息
        if (!found) {
            std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
        }
    }
}