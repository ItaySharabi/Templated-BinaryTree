#include <iostream>
#include "sources/BinaryTree.hpp"

using namespace std;
using namespace ariel;

template<typename T>
struct Node {
    T val;
    Node *left, *right;
    Node(T value):val(value), left(nullptr), right(nullptr){}
    ~Node(){/*delete left; delete right;*/}
};

template<typename T = int>
BinaryTree<T> create_tree(Node<T> root) {

    BinaryTree<T> tree;
    build(&root, tree);
    
}

template<typename T = int>
void build(Node<T> *root, BinaryTree<T> tree) {

    if (root == nullptr) return;

    if (root.left == nullptr) {
        build(root->left, tree.add_left(root, ));

    }
}

int main() {

    srand(7);
    int n = 10;

    Node<int> *nodes[n];
    

    for (int i = 0; i < 10; i++) {
        Node<int> *node = Node<int>(rand()%10);
        nodes[i] = node;
    }  

    

    // Node<int> root(3);
    // Node<int> left(5);
    // Node<int> right(8);

    root.right = &right;
    root.left = &left;

    cout << "Root = " << root.val << ", left  = " << root.left->val << ", right = " << root.right->val << endl;

    // while () {

    // }
    return 0;
}