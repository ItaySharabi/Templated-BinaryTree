#include <iostream>
#include "sources/BinaryTree.hpp"

using namespace std;
using namespace ariel;


int main() {

    BinaryTree<int> ints;
    ints.add_root(1)
    .add_left(1, 9)      // Now 9 is the left child of 1
    .add_left(9, 4)      // Now 4 is the left child of 9
    .add_right(9, 5)     // Now 5 is the right child of 9
    .add_right(1, 3)     // Now 3 is the right child of 1
    .add_left(1, 2);     // Now 2 is the left child of 1, instead of 9 (the children of 9 remain in place)
    auto it = ints.begin_preorder();
    // ++it;
    // ++it;
    // ++it;
    for (; it != ints.end_preorder(); ++it) {
        cout << "*it = " << (*it) << endl;
    }
    
    return 0;
}