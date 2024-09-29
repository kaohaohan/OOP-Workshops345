#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H
#include <string>
namespace seneca{
    //dropdown
    enum class PartOfSpeech
{
  Unknown,
  Noun,
  Pronoun,
  Adjective,
  Adverb,
  Verb,
  Preposition,
  Conjunction,
  Interjection,
};
struct Word
{
  std::string m_word{};
  std::string m_definition{};
  PartOfSpeech m_pos = PartOfSpeech::Unknown;
};
class Dictionary{
    //a dynamically allocated collection of objects of type Word 
    // Word *m_words=nullptr;
    // size_t m_size = 0;
    //add any other private members that your design requires.
    Word *m_words=nullptr;
    size_t m_size = 0;
    public:
   
    Dictionary()= default;
    // Constructor that loads from file
    Dictionary(const char* filename);
    
    // Copy assignment operator
    Dictionary& operator=(const Dictionary& other);
    // Copy constructor
    Dictionary(const Dictionary& other);
    // Move constructor
    Dictionary(Dictionary&& other) noexcept;
    // Move assignment operator
    Dictionary& operator=(Dictionary&& other) noexcept;

    ~Dictionary();

    void searchWord(const char* word);
    void loadFromFile(const char* filename);
    PartOfSpeech getPartOfSpeech(const std::string& pos);
    // PartOfSpeech operator 
    // Getter for word array and size
        const Word* getWords() const { return m_words; }
        size_t getSize() const { return m_size; }
};
    std::string partOfSpeechToString(PartOfSpeech pos);
};
#endif