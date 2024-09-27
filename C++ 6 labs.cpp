#include <iostream>
#include <fstream>
#include <string>
#include <vector> // Чисто чтобы небыло лишних ошибочек)
#include <random>
#include <map>

const int ALPHABET_SIZE = 26;

class TrieNode {
public:
    char data; // Добавим поле data для хранения символа в узле
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;

    void destroyTrie(TrieNode* node) {
        if (node) {
            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                destroyTrie(node->children[i]);
            }
            delete node;
        }
    }

public:
    Trie() : root(new TrieNode()) {}

    ~Trie() {
        destroyTrie(root);
    }

    void insert(const std::string& key) {
        TrieNode* current = root;

        for (char ch : key) {
            int index = ch - 'a';
            if (!current->children[index]) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }

        // Устанавливаем флаг конца слова для последней буквы
        current->isEndOfWord = true;
    }

    bool search(const std::string& key) const {
        TrieNode* current = root;

        for (char ch : key) {
            int index = ch - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index];
        }

        return (current != nullptr && current->isEndOfWord);
    }

    bool remove(const std::string& key) {
        return removeHelper(root, key, 0);
    }

    void print() const {
        printHelper(root, "");
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        saveToFileHelper(root, "", file);
        file.close();
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string word;

        while (file >> word) {
            insert(word);
        }

        file.close();
    }

    void generateRandomTree(int numWords, int wordLength) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis('a', 'z');

        for (int i = 0; i < numWords; ++i) {
            std::string randomWord;
            for (int j = 0; j < wordLength; ++j) {
                randomWord += static_cast<char>(dis(gen));
            }
            insert(randomWord);
        }
    }

    int countWordsWithPrefix(const std::string& prefix) const {
        TrieNode* current = root;

        for (char ch : prefix) {
            int index = ch - 'a';
            if (!current->children[index]) {
                // Префикс не найден, возвращаем 0
                return 0;
            }
            current = current->children[index];
        }

        // Если префикс найден, вызываем вспомогательную рекурсивную функцию
        return countWordsWithPrefixHelper(current);
    }

    //Второе задание
    void buildReverseTrieFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string word;
        while (file >> word) {
            std::reverse(word.begin(), word.end());
            insert(word);
        }

        file.close();
    }

    void findWordsWithSuffix(const std::string& suffix) const {
        std::cout << "Words with suffix '" << suffix << "':\n";
        findWordsWithSuffixHelper(root, "", suffix);
        std::cout << std::endl;
    }
    //Второе задание

    //Третье задание
    int countWordsWithConsonants(int numConsonants) const {
        return countWordsWithConsonantsHelper(root, numConsonants);
    }
    //Третье задание

    //Четвертое Задание
    void printWordsInAlphabeticalOrder() const {
        std::map<std::string, int> wordFrequency;
        buildWordFrequency(root, "", wordFrequency);

        std::cout << "Words in alphabetical order with their frequencies:\n";
        for (const auto& entry : wordFrequency) {
            std::cout << entry.first << " - " << entry.second << " times\n";
        }
        std::cout << std::endl;
    }
    //Четвертое задание
private:

    //Задание 5
    void buildWordFrequency(const TrieNode* node, std::string currentWord, std::map<std::string, int>& wordFrequency) const {
        if (node == nullptr) {
            return;
        }

        if (node->isEndOfWord) {
            wordFrequency[currentWord]++;
        }

        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (node->children[i]) {
                char ch = static_cast<char>('a' + i);
                std::string newCurrentWord = currentWord + ch;
                buildWordFrequency(node->children[i], newCurrentWord, wordFrequency);
            }
        }
    }
    //Задание 5
    
    //Задание 3
    int countWordsWithConsonantsHelper(const TrieNode* node, int numConsonants) const {
        if (node == nullptr) {
            return 0;
        }

        int count = 0;

        // Подсчет согласных в текущем узле
        if (!isVowel(node->data)) {
            count = 1;
        }

        // Рекурсивный вызов для всех дочерних узлов
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (node->children[i]) {
                count += countWordsWithConsonantsHelper(node->children[i], numConsonants);
            }
        }

        // Возвращаем 1, если согласных в текущем узле совпадает с numConsonants
        return (count == numConsonants) ? 1 : 0;
    }

    bool isVowel(char ch) const {
        ch = tolower(ch);
        return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
    }
    //Задание 3

    //Задание 2
    void findWordsWithSuffixHelper(const TrieNode* node, const std::string& currentWord, const std::string& suffix) const {
        if (node == nullptr) {
            return;
        }

        if (node->isEndOfWord && endsWith(currentWord, suffix)) {
            std::cout << currentWord << std::endl;
        }

        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (node->children[i]) {
                char ch = static_cast<char>('a' + i);
                std::string newCurrentWord = ch + currentWord;
                findWordsWithSuffixHelper(node->children[i], newCurrentWord, suffix);
            }
        }
    }

    bool endsWith(const std::string& str, const std::string& suffix) const {
        if (str.length() < suffix.length()) {
            return false;
        }
        return str.substr(str.length() - suffix.length()) == suffix;
    }

    //Задание 2

    int countWordsWithPrefixHelper(const TrieNode* node) const {
        int count = 0;

        if (node->isEndOfWord) {
            // Если текущий узел является концом слова, увеличиваем счетчик
            ++count;
        }

        // Рекурсивно вызываем функцию для всех дочерних узлов
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (node->children[i]) {
                count += countWordsWithPrefixHelper(node->children[i]);
            }
        }

        return count;
    }

    bool removeHelper(TrieNode*& node, const std::string& key, int depth) {
        if (!node) {
            return false;
        }

        if (depth == key.length()) {
            if (node->isEndOfWord) {
                node->isEndOfWord = false;

                // Check if the current node has no other children
                for (int i = 0; i < ALPHABET_SIZE; ++i) {
                    if (node->children[i]) {
                        return false; // Node has other children, do not delete
                    }
                }

                // Node has no other children, it can be deleted
                delete node;
                node = nullptr;

                return true; // Node is deleted
            }

            return false; // Word not found
        }

        int index = key[depth] - 'a';
        if (removeHelper(node->children[index], key, depth + 1)) {
            // Recursively delete nodes and backtrack
            delete node->children[index];
            node->children[index] = nullptr;

            // Check if the current node has no other children
            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                if (node->children[i]) {
                    return false; // Node has other children, do not delete
                }
            }

            // Node has no other children, it can be deleted
            delete node;
            node = nullptr;

            return true; // Node is deleted
        }

        return false; // Word not found
    }

    void printHelper(const TrieNode* node, const std::string& prefix) const {
        if (node) {
            std::cout << prefix;
            std::cout << (node->isEndOfWord ? "* " : "");
            std::cout << "|--";

            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                if (node->children[i]) {
                    char ch = static_cast<char>('a' + i);
                    std::string newPrefix = prefix + (node->children[i]->isEndOfWord ? "   " : "|  ");
                    std::cout << ch << std::endl;
                    printHelper(node->children[i], newPrefix);
                }
            }
        }
    }


    void saveToFileHelper(const TrieNode* node, const std::string& currentWord, std::ofstream& file) const {
        if (node) {
            if (node->isEndOfWord) {
                file << currentWord << std::endl;
            }

            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                if (node->children[i]) {
                    saveToFileHelper(node->children[i], currentWord + static_cast<char>('a' + i), file);
                }
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    Trie trie;

    int choice;
    std::string word;

    do {
        std::cout << "Menu:\n"
            << "1. Insert a word\n"
            << "2. Remove a word\n"
            << "3. Search for a word\n"
            << "4. Print the trie\n"
            << "5. Save to file\n"
            << "6. Load from file\n"
            << "7. Generate random tree\n"
            << "8. Count words with a prefix(Задание 1)\n"
            << "10. Build Trie with reversed words from file(Задание 2)\n"
            << "11. Find words with a suffix(Задание 3)\n"
            << "12. Count words with a specific number of consonants(Задание 4)\n"
            << "13. Print words in alphabetical order with frequencies(Задание 5)\n"
            << "20. Exit\n"
            << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter a word to insert: ";
            std::cin >> word;
            trie.insert(word);
            break;
        case 2:
            std::cout << "Enter a word to remove: ";
            std::cin >> word;
            if (trie.remove(word)) {
                std::cout << "Word removed successfully.\n";
            }
            else {
                std::cout << "Word not found.\n";
            }
            break;
        case 3:
            std::cout << "Enter a word to search: ";
            std::cin >> word;
            if (trie.search(word)) {
                std::cout << "Word found.\n";
            }
            else {
                std::cout << "Word not found.\n";
            }
            break;
        case 4:
            std::cout << "Trie structure:\n";
            std::cout << "Выглядит как древовидное представление trie-дерева.\n";
            std::cout << "Каждый уровень дерева представлен буквой, и если буква является конечной буквой слова,\n";
            std::cout << "то рядом с ней стоит символ ' * ', обозначающий конец слова.\n";
            std::cout << "Каждая буква представляет собой уровень в trie, а вложенность буквы отображает отношение префиксов и слов в дереве.\n";
            trie.print();
            std::cout << std::endl;
            break;
        case 5:
            std::cout << "Enter the filename to save to: ";
            std::cin >> word;
            trie.saveToFile(word);
            std::cout << "Trie saved to file.\n";
            break;
        case 6:
            std::cout << "Enter the filename to load from: ";
            std::cin >> word;
            trie.loadFromFile(word);
            std::cout << "Trie loaded from file.\n";
            break;
        case 7:
            int numWords, wordLength;
            std::cout << "Enter the number of words: ";
            std::cin >> numWords;
            std::cout << "Enter the length of each word: ";
            std::cin >> wordLength;
            trie.generateRandomTree(numWords, wordLength);
            std::cout << "Random tree generated.\n";
            break;
        case 8:
            std::cout << "Enter a prefix to count words: ";
            std::cin >> word;
            std::cout << "Number of words with prefix '" << word << "': " << trie.countWordsWithPrefix(word) << std::endl;
            break;
        case 20:
            std::cout << "Exiting the program.\n";
            break;
        case 10:
            std::cout << "Enter the filename for reverse Trie construction: ";
            std::cin >> word;
            trie.buildReverseTrieFromFile(word);
            std::cout << "Reverse Trie constructed.\n";
            break;
        case 11:
            std::cout << "Enter the suffix to find words with: ";
            std::cin >> word;
            trie.findWordsWithSuffix(word);
            break;
        case 12:
            int numConsonants;
            std::cout << "Enter the number of consonants to count words: ";
            std::cin >> numConsonants;

            // Очистка буфера ввода
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Number of words with " << numConsonants << " consonants: " << trie.countWordsWithConsonants(numConsonants) << std::endl;
            break;
        case 13:
            trie.printWordsInAlphabeticalOrder();
            break;
        default:
            std::cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }

    } while (choice != 20);

    return 0;
}
