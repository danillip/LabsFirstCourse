#include <iostream>
#include <fstream>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <iomanip>  // Добавлен заголовок для std::setw

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;

    void insert(TreeNode*& node, int value);
    TreeNode* remove(TreeNode*& node, int key);
    TreeNode* findMin(TreeNode* node);
    TreeNode* search(TreeNode* node, int key);

    void printInOrder(TreeNode* node, std::ofstream& outfile);
    void printPreOrder(TreeNode* node, std::ofstream& outfile);
    void printPostOrder(TreeNode* node, std::ofstream& outfile);

    int findLastLevelWithPositiveElements(TreeNode* node);

    // Correct function declarations
    void printTreeStructureInOrder(TreeNode* node, std::ostream& os, int indent);
    void printTreeStructurePreOrder(TreeNode* node, std::ostream& os, int indent);
    void printTreeStructurePostOrder(TreeNode* node, std::ostream& os, int indent);

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value);
    void remove(int key);
    bool search(int key);
    void printInOrder(const std::string& filename);
    void printPreOrder(const std::string& filename);
    void printPostOrder(const std::string& filename);
    int findLastLevelWithPositiveElements();

    void fillTreeManually();
    void fillTreeRandomly(int numElements);
    void printTreeStructure(std::ostream& os);

    // Correct function declarations
    void printTreeStructureInOrder(std::ostream& os);
    void printTreeStructurePreOrder(std::ostream& os);
    void printTreeStructurePostOrder(std::ostream& os);
};

void BinaryTree::insert(TreeNode*& node, int value) {
    if (!node) {
        node = new TreeNode(value);
    }
    else if (value < node->data) {
        insert(node->left, value);
    }
    else if (value > node->data) {
        insert(node->right, value);
    }
}

void BinaryTree::insert(int value) {
    insert(root, value);
}

TreeNode* BinaryTree::remove(TreeNode*& node, int key) {
    if (!node) {
        return node;
    }

    if (key < node->data) {
        node->left = remove(node->left, key);
    }
    else if (key > node->data) {
        node->right = remove(node->right, key);
    }
    else {
        if (!node->left) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }

        TreeNode* temp = findMin(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data);
    }

    return node;
}

void BinaryTree::remove(int key) {
    root = remove(root, key);
}

TreeNode* BinaryTree::findMin(TreeNode* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

TreeNode* BinaryTree::search(TreeNode* node, int key) {
    if (!node || node->data == key) {
        return node;
    }

    if (key < node->data) {
        return search(node->left, key);
    }

    return search(node->right, key);
}

bool BinaryTree::search(int key) {
    return search(root, key) != nullptr;
}

// Add an additional parameter 'outfile' to printInOrder, printPreOrder, and printPostOrder
void BinaryTree::printInOrder(TreeNode* node, std::ofstream& outfile) {
    if (node) {
        printInOrder(node->left, outfile);
        outfile << node->data << " ";
        printInOrder(node->right, outfile);
    }
}

void BinaryTree::printInOrder(const std::string& filename) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        printInOrder(root, outfile);
        outfile.close();
        std::cout << "In-order traversal saved to '" << filename << "'." << std::endl;
    }
    else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

void BinaryTree::printPreOrder(TreeNode* node, std::ofstream& outfile) {
    if (node) {
        outfile << node->data << " ";
        printPreOrder(node->left, outfile);
        printPreOrder(node->right, outfile);
    }
}

void BinaryTree::printPreOrder(const std::string& filename) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        printPreOrder(root, outfile);
        outfile.close();
        std::cout << "Pre-order traversal saved to '" << filename << "'." << std::endl;
    }
    else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

void BinaryTree::printPostOrder(TreeNode* node, std::ofstream& outfile) {
    if (node) {
        printPostOrder(node->left, outfile);
        printPostOrder(node->right, outfile);
        outfile << node->data << " ";
    }
}

void BinaryTree::printPostOrder(const std::string& filename) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        printPostOrder(root, outfile);
        outfile.close();
        std::cout << "Post-order traversal saved to '" << filename << "'." << std::endl;
    }
    else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}


void BinaryTree::printTreeStructureInOrder(TreeNode* node, std::ostream& os, int indent) {
    if (node) {
        printTreeStructureInOrder(node->left, os, indent + 4);
        if (indent) {
            os << std::setw(indent) << ' ';
        }
        os << node->data << "\n ";
        printTreeStructureInOrder(node->right, os, indent + 4);
    }
}

void BinaryTree::printTreeStructurePreOrder(TreeNode* node, std::ostream& os, int indent) {
    if (node) {
        if (indent) {
            os << std::setw(indent) << ' ';
        }
        os << node->data << "\n ";
        printTreeStructurePreOrder(node->left, os, indent + 4);
        printTreeStructurePreOrder(node->right, os, indent + 4);
    }
}

void BinaryTree::printTreeStructurePostOrder(TreeNode* node, std::ostream& os, int indent) {
    if (node) {
        printTreeStructurePostOrder(node->left, os, indent + 4);
        printTreeStructurePostOrder(node->right, os, indent + 4);
        if (indent) {
            os << std::setw(indent) << ' ';
        }
        os << node->data << "\n ";
    }
}

// Wrapper functions to call the respective printTreeStructure functions
void BinaryTree::printTreeStructureInOrder(std::ostream& os) {
    printTreeStructureInOrder(root, os, 0);
}

void BinaryTree::printTreeStructurePreOrder(std::ostream& os) {
    printTreeStructurePreOrder(root, os, 0);
}

void BinaryTree::printTreeStructurePostOrder(std::ostream& os) {
    printTreeStructurePostOrder(root, os, 0);
}





int BinaryTree::findLastLevelWithPositiveElements(TreeNode* node) {
    if (!node) {
        return -1;
    }

    std::queue<std::pair<TreeNode*, int>> q;
    q.push({ node, 0 });
    int lastLevel = -1;

    while (!q.empty()) {
        TreeNode* current = q.front().first;
        int level = q.front().second;
        q.pop();

        if (current->data > 0) {
            lastLevel = level;
        }

        if (current->left) {
            q.push({ current->left, level + 1 });
        }

        if (current->right) {
            q.push({ current->right, level + 1 });
        }
    }

    return lastLevel;
}

int BinaryTree::findLastLevelWithPositiveElements() {
    return findLastLevelWithPositiveElements(root);
}

void BinaryTree::fillTreeManually() {
    int numElements;
    std::cout << "Enter the number of elements to insert: ";
    std::cin >> numElements;

    for (int i = 0; i < numElements; ++i) {
        int element;
        std::cout << "Enter element " << (i + 1) << ": ";
        std::cin >> element;
        insert(element);
    }
}

void BinaryTree::fillTreeRandomly(int numElements) {
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < numElements; ++i) {
        int element = rand() % 100;
        insert(element);
    }
}

int main() {
    BinaryTree tree;

    while (true) {
        std::cout << "Binary Tree Operations:" << std::endl;
        std::cout << "1. Fill Tree Manually" << std::endl;
        std::cout << "2. Fill Tree Randomly" << std::endl;
        std::cout << "3. Insert Element" << std::endl;
        std::cout << "4. Remove Element" << std::endl;
        std::cout << "5. Search Element" << std::endl;
        std::cout << "6. Print Tree (In-order)" << std::endl;
        std::cout << "7. Print Tree (Pre-order)" << std::endl;
        std::cout << "8. Print Tree (Post-order)" << std::endl;
        std::cout << "9. Find Last Level with Positive Elements" << std::endl;
        std::cout << "10. Print In-order" << std::endl;
        std::cout << "11. Print Pre-order" << std::endl;
        std::cout << "12. Print Post-order" << std::endl;
        std::cout << "13. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            tree.fillTreeManually();
            std::cout << "Tree filled with elements entered manually." << std::endl;
            break;
        }
        case 2: {
            int numElements;
            std::cout << "Enter the number of elements to generate randomly: ";
            std::cin >> numElements;
            tree.fillTreeRandomly(numElements);
            std::cout << "Tree filled with random elements." << std::endl;
            break;
        }
        case 3: {
            int element;
            std::cout << "Enter the element to insert: ";
            std::cin >> element;
            tree.insert(element);
            break;
        }
        case 4: {
            int key;
            std::cout << "Enter the key of the element to remove: ";
            std::cin >> key;
            tree.remove(key);
            break;
        }
        case 5: {
            int key;
            std::cout << "Enter the key to search for: ";
            std::cin >> key;
            if (tree.search(key)) {
                std::cout << "Element " << key << " found in the tree." << std::endl;
            }
            else {
                std::cout << "Element " << key << " not found in the tree." << std::endl;
            }
            break;
        }
        case 6: {
            std::string filename;
            std::cout << "Enter the filename to save the In-order traversal: ";
            std::cin >> filename;
            tree.printInOrder(filename);
            break;
        }
        case 7: {
            std::string filename;
            std::cout << "Enter the filename to save the Pre-order traversal: ";
            std::cin >> filename;
            tree.printPreOrder(filename);
            break;
        }
        case 8: {
            std::string filename;
            std::cout << "Enter the filename to save the Post-order traversal: ";
            std::cin >> filename;
            tree.printPostOrder(filename);
            break;
        }
        case 9: {
            int level = tree.findLastLevelWithPositiveElements();
            if (level >= 0) {
                std::cout << "Last level with positive elements: " << level << std::endl;
            }
            else {
                std::cout << "No positive elements found in the tree." << std::endl;
            }
            break;
        }
        case 10: {
            std::cout << "Print Tree Structure (In-order):" << std::endl;
            tree.printTreeStructureInOrder(std::cout);
            break;
        }
        case 11: {
            std::cout << "Print Tree Structure (Pre-order):" << std::endl;
            tree.printTreeStructurePreOrder(std::cout);
            break;
        }
        case 12: {
            std::cout << "Print Tree Structure (Post-order):" << std::endl;
            tree.printTreeStructurePostOrder(std::cout);
            break;
        }
        case 13: {
            std::cout << "Exiting program." << std::endl;
            return 0;
        }
        default: {
            std::cout << "Invalid choice. Please select a valid option." << std::endl;
            break;
        }
        }
    }

    return 0;
}
