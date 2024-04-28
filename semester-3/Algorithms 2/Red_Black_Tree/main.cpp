//ALGO2 IS1 223A LAB04
//Vladyslav Zosimchuk
//zv53855@zut.edu.pl

#include <iostream>
#include <sstream>
#include <random>

enum Color { Red, Black };

template<typename T>
struct Node {
    int key;
    T data;
    Color color;
    Node *parent, *left, *right;

    Node (const int _key, const T _data) :
            key(_key),
            data(std::move(_data)),
            color(Red),
            parent(nullptr),
            left(nullptr),
            right(nullptr)
    {}

    ~Node() = default;
};

template<typename T>
class RBT {
    int size;
    Node<T>* root;
    Node<T>* NIL;

public:
    explicit RBT() :
            size(0),
            root(nullptr),
            NIL(nullptr)
    {}
    ~RBT() {
        clearRBT(root);
    }
    Node<T>*& getRoot();
    Node<T>* searchNode(T); // a
    std::string preOrder(Node<T>*&); // b
    std::string inOrder(Node<T>*&); // c
    void clearRBT(Node<T>*&); // d
    int getHeight(Node<T>*&); // e
    void insertNewNode(Node<T>*&); // f
    void insertFixUp(Node<T>*&); // f
    std::string node_to_string(Node<T>*&);
    std::string RBT_to_string(int); // g
    void leftRotation(Node<T>*&); // h
    void rightRotation(Node<T>*&); // i
};

int main() {

    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_int_distribution<int> distribution(0, 100000000);
    // RBT<int> myRBT;
    // const int MAX_ORDER = 7;
    //
    // for (int o = 1; o <= MAX_ORDER; ++o) {
    //     const int n = pow(10, o);
    //     clock_t t1 = clock();
    //     for (int i = 1; i <= n; ++i) {
    //         auto newNode = new Node<int>(i, distribution(gen));
    //         myRBT.insertNewNode(newNode);
    //     }
    //     clock_t t2 = clock();
    //     std::cout << "It took " << double(t2 - t1) / CLOCKS_PER_SEC * 1000 << " miliseconds to add " << n << " nodes" << std::endl;
    //     myRBT.clearRBT(myRBT.getRoot());
    // }

    //
    // RBT<int> myRBT;
    // auto* newNode = new Node<int>(1, 10);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(2, 5);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(3, 15);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(4, 2);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(5, 7);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(6, 6);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(7, 8);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;


    RBT<int> myRBT;
    auto* newNode = new Node<int>(1, 7);
    myRBT.insertNewNode(newNode);
    newNode = new Node<int>(2, 2);
    myRBT.insertNewNode(newNode);
    newNode = new Node<int>(3, 1);
    myRBT.insertNewNode(newNode);
    newNode = new Node<int>(4, 5);
    myRBT.insertNewNode(newNode);
    newNode = new Node<int>(5, 14);
    myRBT.insertNewNode(newNode);
    newNode = new Node<int>(6, 8);
    myRBT.insertNewNode(newNode);
    newNode = new Node<int>(7, 15);
    myRBT.insertNewNode(newNode);
    newNode = new Node<int>(8, 11);
    myRBT.insertNewNode(newNode);
    std::cout << myRBT.RBT_to_string(1) << std::endl;
    newNode = new Node<int>(9, 13);
    myRBT.insertNewNode(newNode);
    std::cout << myRBT.RBT_to_string(1) << std::endl;
    newNode = new Node<int>(10, 17);
    myRBT.insertNewNode(newNode);
    std::cout << myRBT.RBT_to_string(1) << std::endl;
    newNode = new Node<int>(11, 9);
    myRBT.insertNewNode(newNode);
    std::cout << myRBT.RBT_to_string(1) << std::endl;
    newNode = new Node<int>(12, 12);
    myRBT.insertNewNode(newNode);
    std::cout << myRBT.RBT_to_string(1) << std::endl;

    // RBT<int> myRBT;
    // auto* newNode = new Node<int>(1, 10);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // newNode = new Node<int>(2, 18);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // newNode = new Node<int>(3, 7);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // newNode = new Node<int>(4, 15);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // newNode = new Node<int>(5, 16);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // newNode = new Node<int>(6, 30);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // newNode = new Node<int>(7, 25);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // newNode = new Node<int>(8, 40);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // newNode = new Node<int>(9, 60);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // newNode = new Node<int>(10, 2);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // newNode = new Node<int>(11, 70);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // newNode = new Node<int>(12, 1);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;

    // RBT<int> myRBT;
    // auto* newNode = new Node<int>(1, 38);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(2, 81);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(3, 18);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(4, 91);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(5, 30);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(6, 20);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(7, 10);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // auto* search = myRBT.searchNode(18);
    // myRBT.rightRotation(search);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // search = myRBT.searchNode(38);
    // myRBT.leftRotation(search);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // search = myRBT.searchNode(9999999);
    // std::cout << search << std::endl;
    // search = myRBT.searchNode(91);
    // std::cout << search << std::endl;


    // RBT<int> myRBT;
    // auto* newNode = new Node<int>(1, 9);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(2, 12);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(3, 4);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(4, 7);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(5, 2);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node<int>(6, 1);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // auto* search = myRBT.searchNode(7);
    // myRBT.leftRotation(search);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // search = myRBT.searchNode(2);
    // myRBT.rightRotation(search);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // search = myRBT.searchNode(12);
    // myRBT.leftRotation(search);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // myRBT.rightRotation(search);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;

    // RBT<int> myRBT;
    // auto* newNode = new Node(1, 5);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node(2, 2);
    // myRBT.insertNewNode(newNode);
    // newNode = new Node(3, 7);
    // myRBT.insertNewNode(newNode);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;
    // auto* search = myRBT.searchNode(5);
    // myRBT.rightRotation(search);
    // std::cout << myRBT.RBT_to_string(1) << std::endl;

    return 0;
    }

template <typename T>
Node<T>*& RBT<T>::getRoot() {
    return root;
}

template <typename T>
Node<T>* RBT<T>::searchNode(T data) {
    Node<T>* traverser = root;

    while (traverser != NIL) {
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

template <typename T>
std::string RBT<T>::inOrder(Node<T>*& traverser) {
    if (!traverser || traverser == NIL) return "";

    std::string result;
    result += inOrder(traverser->left);
    result += node_to_string(traverser);
    result += inOrder(traverser->right);

    return result;
}

template <typename T>
std::string RBT<T>::preOrder(Node<T>*& traverser) {
    if (traverser == NIL) return "";

    std::string result = node_to_string(traverser);
    result += preOrder(traverser->left);
    result += preOrder(traverser->right);

    return result;
}

template <typename T>
void RBT<T>::clearRBT(Node<T>*& traverser) {
    if (traverser->left && traverser != NIL) clearRBT(traverser->left);
    if (traverser->right && traverser != NIL) clearRBT(traverser->right);
    if (traverser && traverser != NIL) delete traverser;
    traverser = nullptr;
    --size;
}

template <typename T>
int RBT<T>::getHeight(Node<T>*& traverser) {
    if (!traverser || traverser == NIL) {
        return 0;
    }

    const int leftHeight = getHeight(traverser->left);
    const int rightHeight = getHeight(traverser->right);

    return 1 + std::max(leftHeight, rightHeight);
}


template<typename T>
void RBT<T>::insertFixUp(Node<T>*& node) {
    while (node != root && node->parent->color == Red) {
    auto*& parent = node->parent;
    auto*& grandparent = parent->parent;
        if (parent == grandparent->left) {
            auto*& uncle = grandparent->right;
            if (uncle != nullptr && uncle->color == Red) {
                node->parent->color = Black;
                uncle->color = Black;
                node->parent->parent->color = Red;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    leftRotation(node);
                    node = (node->left) ? node->left : node->right;
                }
            rightRotation(node->parent);
            node = node->parent;
            node->right->color = Red;
            node->color = Black;
            }
        } else {
            auto*& uncle = grandparent->left;
            if (uncle != nullptr && uncle->color == Red) {
                node->parent->color = Black;
                uncle->color = Black;
                node->parent->parent->color = Red;
            } else {
                if (node == parent->left) {
                    rightRotation(node);
                    node = (node->left) ? node->left : node->right;
                }
                leftRotation(node->parent);
                node = node->parent;
                node->color = Black;
                node->left->color = Red;
                }
            }
    }
    root->color = Black;
}

template <typename T>
void RBT<T>::insertNewNode(Node<T>*& node) {
    auto* traverser = root;
    Node<T>* parent = nullptr;

    while (traverser && traverser != NIL) {
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
        root->color = Black;
    } else if (node->data > parent->data) {
        parent->right = node;
    } else {
        parent->left = node;
    }

    node->parent = parent;
    node->left = NIL;
    node->right = NIL;
    ++size;
    insertFixUp(node);
}

template <typename T>
std::string RBT<T>::node_to_string(Node<T>*& node) {
    std::stringstream ss;
    std::string p = (node->parent) ? std::to_string(node->parent->key) : "NULL";
    std::string l = (node->left != NIL) ? std::to_string(node->left->key) : "NIL";
    std::string r = (node->right != NIL) ? std::to_string(node->right->key) : "NIL";
    std::string color = (node->color == Black) ? "black" : "red";

    ss << "(" << node->key << ": [" << color << " p: " << p << ", l: " << l << ", r: " << r << "], data: " << node->data;
    (node->left || node->right) ? ss << "), " : ss << ")";
    ss << std::endl;

    return ss.str();
}

template <typename T>
std::string RBT<T>::RBT_to_string(const int mode) {
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

template <typename T>
void RBT<T>::leftRotation(Node<T>*& node) {
    if (node == root) {
        root = node->right;
        root->left = node;
        node->parent = root;
        root->parent = nullptr;
        node->right = nullptr;
        root->color = Black;
        return;
    }

    Node<T>* parent = node->parent;
    Node<T>* child = node->left;
    if (parent) {
        if (parent == root && parent->right == node) root = parent->right;
        (parent->right == node) ? parent->right = child : parent->left = child;
    } else {
        root = child;
    }
    if (child) child->parent = parent;
    node->left = parent;
    node->parent = parent->parent;
    if (parent->parent) {
        (parent->parent->left == parent) ? parent->parent->left = node : parent->parent->right = node;
    }
    parent->parent = node;
}

template <typename T>
void RBT<T>::rightRotation(Node<T>*& node) {
    if (node == root) {
        root = node->left;
        root->right = node;
        node->parent = root;
        root->parent = nullptr;
        node->left = nullptr;
        root->color = Black;
        return;
    }

    Node<T>* parent = node->parent;
    Node<T>* child = node->right;
    if (parent) {
        if (parent == root && parent->left == node) root = parent->left;
        (parent->right == node) ? parent->right = child : parent->left = child;
    } else {
        root = child;
    }
    if (child) child->parent = parent;
    node->right = parent;
    node->parent = parent->parent;
    if (parent->parent) {
        (parent->parent->left == parent) ? parent->parent->left = node : parent->parent->right = node;
    }    parent->parent = node;
}
