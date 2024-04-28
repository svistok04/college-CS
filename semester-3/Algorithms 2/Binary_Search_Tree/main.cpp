//ALGO2 IS1 223A LAB03
//Vladyslav Zosimchuk
//zv53855@zut.edu.pl

#include <iostream>
#include <sstream>

template<typename T>
struct Node {
    int key;
    T data;
    struct Node<T> *parent, *left, *right;

    Node (int _key, T _data) :
            key(_key),
            data(std::move(_data)),
            parent(nullptr),
            left(nullptr),
            right(nullptr)
    {}

    ~Node() = default;
};

template<typename T>
class BST {
    int size;
    Node<T>* root;

public:
    explicit BST(Node<T>*& _root) :
    size(1),
    root(_root)
    {}
    ~BST() {
        clearBST(root);
    };
    void insertNewNode(Node<T>*&); // a
    Node<T>* searchNode(T); // b
    Node<T>* findMinimumDataNode(Node<T>*&); // helps to remove a node with two children
    void removeNode(Node<T>*&); // c
    void removeNodeNoChildren(Node<T>*&); // this one is used twice
    void removeNodeOneChildren(Node<T>*&); // this one too, so code becomes cleaner
    std::string preOrder(Node<T>*&); // d
    std::string inOrder(Node<T>*&); // e
    void clearBST(Node<T>*&); // f
    int getHeight(Node<T>*&); // g
    std::string node_to_string(Node<T>*&);
    std::string BST_to_string(int); // h
};

    int main() {

        auto* root = new Node<int>(1, 38);

        BST<int> myBST(root);

        auto* newNode = new Node<int>(2, 81);
        myBST.insertNewNode(newNode);
        newNode = new Node<int>(3, 18);
        myBST.insertNewNode(newNode);
        newNode = new Node<int>(4, 91);
        myBST.insertNewNode(newNode);
        newNode = new Node<int>(5, 30);
        myBST.insertNewNode(newNode);
        newNode = new Node<int>(6, 20);
        myBST.insertNewNode(newNode);
        newNode = new Node<int>(7, 10);
        myBST.insertNewNode(newNode);
        newNode = new Node<int>(7, 10);
        myBST.insertNewNode(newNode);
        newNode = new Node<int>(7, 10);

        std::cout << myBST.BST_to_string(1); // mode: 1 - pre-order, 2 - in-order

        auto* search = myBST.searchNode(18);

        myBST.removeNode(search);

        std::cout << myBST.BST_to_string(2); // mode: 1 - pre-order, 2 - in-order

        return 0;
    }

//template <typename T>
//Node<T>*& BST<T>::insertNewNode(Node<T>*& traverser, Node<T>*& node) {
//    if (!traverser) {
//        traverser = node;
//        ++size;
//    }
//
//    if (node->data > traverser->data) {
//        traverser->right = insertNewNode(traverser->right, node);
//        traverser->right->parent = traverser;
//    }
//
//    if (node->data < traverser->data) {
//        traverser->left = insertNewNode(traverser->left, node);
//        traverser->left->parent = traverser;
//    }
//
//    return traverser;
//}

template <typename T>
void BST<T>::insertNewNode(Node<T>*& node) {
    Node<T>* traverser = root;
    Node<T>* parent = nullptr;

    while (traverser) {
        parent = traverser;
        if (node->data > traverser->data) {
            traverser = traverser->right;
        } else if (node->data < traverser->data) {
            traverser = traverser->left;
        } else {
            delete node;
            return;
        }
    }

    if (!parent) {
        root = node;
    } else if (node->data > parent->data) {
        parent->right = node;
    } else {
        parent->left = node;
    }

    node->parent = parent;

    ++size;
}

template <typename T>
Node<T>* BST<T>::searchNode(T data) {
    Node<T>* traverser = root;

    while (traverser) {
        if (traverser->data == data) {
            return traverser;
        } else if (traverser->data > data) {
            traverser = traverser->left;
        } else {
            traverser = traverser->right;
        }
    }

    return nullptr;
}

//template <typename T>
//Node<T>* BST<T>::searchNode(Node<T>*& traverser, T data) {
//
//    if (!traverser) {
//        return nullptr;
//    }
//
//    if (traverser->data == data) {
//        return traverser;
//    }
//
//    if (traverser->data > data) {
//        return searchNode(traverser->left, data);
//    }
//
//    return searchNode(traverser->right, data);
//}

template <typename T>
Node<T>* BST<T>::findMinimumDataNode(Node<T>*& traverser) {
    if (!traverser->left) {
        return traverser;
    }
    return findMinimumDataNode(traverser->left);
}


template <typename T>
void BST<T>::removeNodeNoChildren(Node<T>*& node) {
    (node->parent->left == node) ? node->parent->left = nullptr : node->parent->right = nullptr;
    delete node;
}

template <typename T>
void BST<T>::removeNodeOneChildren(Node<T>*& node) {
    if (node->parent->left == node) {
        if (node->left) {
            node->parent->left = node->left;
            node->left->parent = node->parent;
        } else {
            node->parent->left = node->right;
            node->right->parent = node->parent;
        }
        (node->left) ? node->parent->left = node->left : node->parent->left = node->right;
        delete node;
        return;
    } else {
        if (node->left) {
            node->parent->right = node->left;
            node->left->parent = node->parent;
        } else {
            node->parent->right = node->right;
            node->right->parent = node->parent;
        }
        delete node;
        return;
    }
}

template <typename T>
void BST<T>::removeNode(Node<T>*& node) {

    if (!node) return;

    // no children
    if (!node->left && !node->right) {
        removeNodeNoChildren(node);
    }
    // one child
    if (!(node->left && node->right)) {
        removeNodeOneChildren(node);
    } else {  // both children
        Node<T>* minimumNode = findMinimumDataNode(node->right);
        node->data = minimumNode->data;
        node->key = minimumNode->key;
        if (!minimumNode->left && !minimumNode->right) {
            removeNodeNoChildren(minimumNode);
        } else { // as this node will never have both children, we omit that case
            removeNodeOneChildren(minimumNode);
        }
    }

    --size;
}

template <typename T>
std::string BST<T>::inOrder(Node<T>*& traverser) {
    if (!traverser) return "";

    std::string result;
    result += inOrder(traverser->left);
    result += node_to_string(traverser);
    result += inOrder(traverser->right);

    return result;
}

template <typename T>
std::string BST<T>::preOrder(Node<T>*& traverser) {
    if (!traverser) return "";

    std::string result = node_to_string(traverser);
    result += preOrder(traverser->left);
    result += preOrder(traverser->right);

    return result;
}

template <typename T>
void BST<T>::clearBST(Node<T>*& traverser) {
    if (traverser->left) clearBST(traverser->left);
    if (traverser->right) clearBST(traverser->right);
    delete traverser;
    traverser = nullptr;
}

template <typename T>
int BST<T>::getHeight(Node<T>*& traverser) {
    if (!traverser) {
        return 0;
    }

    int leftHeight = getHeight(traverser->left);
    int rightHeight = getHeight(traverser->right);

    return 1 + std::max(leftHeight, rightHeight);
}

template <typename T>
std::string BST<T>::node_to_string(Node<T>*& node) {
    std::stringstream ss;
    std::string p = (node->parent) ? std::to_string(node->parent->key) : "NULL";
    std::string l = (node->left) ? std::to_string(node->left->key) : "NULL";
    std::string r = (node->right) ? std::to_string(node->right->key) : "NULL";

    ss << "(" << node->key << ": [p: " << p << ", l: " << l << ", r: " << r << "], data: " << node->data;
    (node->left || node->right) ? ss << "), " : ss << ")";
    ss << std::endl;

    return ss.str();
}

template <typename T>
std::string BST<T>::BST_to_string(int mode) {
    std::stringstream ss;

    ss << "size: " << size << std::endl
    << "height: " << getHeight(root) << std::endl;

    switch(mode) {
        case(1):
            ss << "Pre-order traversal:" << std::endl;
            ss << "{" << std::endl << preOrder(root) << "}" << std::endl;
            break;
        case(2):
            ss << "In-order traversal:" << std::endl;
            ss << "{" << std::endl << inOrder(root) << "}" << std::endl;
            break;
        default:
            ss << "No traversal mode chosen" << std::endl;
    }

    return ss.str();
}
