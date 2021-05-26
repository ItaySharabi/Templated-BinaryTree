#include "doctest.h"
#include "BinaryTree.hpp"
#include <sstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <set>
#include <iostream>

using namespace std;
using namespace ariel;

template<typename T>
struct Node {
    T val;
    Node *left, *right;
    Node(T value):val(value), left(nullptr), right(nullptr){}
    ~Node(){/*delete left; delete right;*/}
};

template<typename V = int>
BinaryTree<V> build(vector<V> elements) {

    Node<V> node;
    
    
    // if (elements.size() == 0) {
    //     BinaryTree<V> none;
    //     cout << "none returnedddddd" << endl;
    //     return none;
    // }

    BinaryTree<V> tree_of_V;
    V next_root = *tree_of_V.begin_preorder();

    CHECK_NOTHROW(tree_of_V.add_root(elements.at(0)));
    CHECK(next_root == elements.at(0)); // first element returned from pre-order is root

    unsigned int i = 0;
    // [1,3,6,2,7]
    /*
        1
       / \
      3   6
         / \
        2   7
    */
    while(++i < elements.size()) {
        if(i%2 == 0) { // add right and reset next_root 
            CHECK_NOTHROW(tree_of_V.add_right(next_root, elements.at(i)));
            next_root = elements.at(i);
        } else { // add left and reset root 1 back
            CHECK_NOTHROW(tree_of_V.add_left(next_root, elements.at(i)));
            next_root = elements.at(i-1);
        }
    }

    return tree_of_V;
}


template <typename V>
void test_iterators(BinaryTree<V> tree) { // template function to get any type V inside a tree


    auto pre_iter = tree.begin_preorder();  // root -> left -> right. 
    auto post_iter = tree.begin_postorder();// left -> right -> root.
    auto in_iter1 = tree.begin_inorder();   // left -> root -> right
    auto in_iter2 = tree.begin();           // like in-order

    V root /*= *pre_iter*/; 
    for(;post_iter != tree.end_postorder(); ++post_iter) {
        root = *post_iter;
    } // after for loop, 'root' will get the value (V) of the root of 'tree'


    // pre_iter should point to root first
    CHECK(*pre_iter == root);   // Check if pre and post iterators return the root as first/last element
    /* ^ IF Type V has operator == ^ */


    // in-order and regular begin() should behave the same in terms of traversal
    for (; in_iter1 != tree.end() && in_iter2 != tree.end_inorder();) {
        CHECK(*(++in_iter1) == *(++in_iter2));
    }    
}   


TEST_CASE("Test 1(GOOD): Traversal Orders ( Operators != / ++ / * )") {

    BinaryTree</*int*/> tree_of_ints; // tree 1
    /*              1
                   / \
                  2   5
                 / \ 
                3   4 
    */
   CHECK_NOTHROW(
    tree_of_ints.add_root(1).
    add_left(1,2).
    add_left(2,3).
    add_right(2,4).
    add_right(1,5));
// ==================================

    BinaryTree<double> tree_of_doubles; // tree 2 (same tree as 1)

    CHECK_NOTHROW(
    tree_of_doubles.add_root(1).
    add_left(1,2).
    add_left(2,3).
    add_right(2,4).
    add_right(1,5));
// ==================================

    BinaryTree<string> tree_of_strings; // tree 3 (same tree as 1)

    CHECK_NOTHROW(
    tree_of_strings.add_root("1").
    add_left("1","2").
    add_left("2","3").
    add_right("2","4").
    add_right("1","5"));
// ==================================

    SUBCASE("Iterators General check") {
        test_iterators(tree_of_ints);
        test_iterators(tree_of_doubles);
        test_iterators(tree_of_strings);    

        // In-Order print:   3-2-4-1-5
        vector<int> in_vector =   {3,2,4,1,5};
        // Pre-Order print:  1-2-3-4-5
        vector<int> pre_vector =  {1,2,3,4,5};
        // Post-Order print: 3-4-2-5-1
        vector<int> post_vector = {3,4,2,5,1};

        auto pre_iter = tree_of_ints.begin_preorder();
        auto post_iter = tree_of_ints.begin_postorder();
        auto in_iter1 = tree_of_ints.begin_inorder();
        auto in_iter2 = tree_of_ints.begin(); // should work like in-order
        

        // cout << "pre_vector: " << endl;
        for (auto i : pre_vector) {
            CHECK(i == *(pre_iter++));
        }

        // cout << "post_vector: " << endl;
        for (auto i : post_vector) {
            CHECK(i == *(post_iter++));
        }

        // cout << "in_vector: " << endl;
        for (auto i : in_vector) {
            CHECK(i == *(in_iter1++));
            CHECK(i == *(in_iter2++));
        }
    }

}

TEST_CASE("Test 2 - Creating trees") {

    BinaryTree<string> tree_of_strings;
    /*
        CPP
        / \
      IS   FUN
    */
    CHECK_NOTHROW(
    tree_of_strings.add_root("CPP")
    .add_left("CPP","IS")
    .add_right("CPP","FUN"));


    CHECK_THROWS(tree_of_strings.add_left("Does not exist", "Some string value"));
    CHECK_THROWS(tree_of_strings.add_right("Does not exist", "Some string value"));

    CHECK_NOTHROW(tree_of_strings.add_right("CPP", "VERY")); // pre-order: CPP IS VERY 
    CHECK_NOTHROW(tree_of_strings.add_right("VERY", "FUN")); // pre-order: CPP IS VERY FUN

    string pre_order[] = {"CPP", "IS", "VERY", "FUN"};

    test_iterators(tree_of_strings);
    string all_words;
    int k = 0;
    // V all_words;
    for (auto i = tree_of_strings.begin_preorder(); i != tree_of_strings.end_preorder(); ++i) {
        CHECK(pre_order[k++] == *i);
        all_words += (*i + " ");
    }

    CHECK(all_words == "CPP IS VERY FUN");
                                         
}


TEST_CASE("Test 3") {
    BinaryTree<string> tree_of_strings;
    /*
        CPP
        / \
      IS   FUN
    */

    tree_of_strings.add_root("CPP")
    .add_left("CPP","IS")
    .add_right("CPP","FUN");

    BinaryTree</*int*/> tree_of_ints;
    /*              1
                   / \
                  2   5
                 / \ 
                3   4 
    */

    tree_of_ints.
    add_root(1).
    add_left(1,2).
    add_left(2,3).
    add_right(2,4).
    add_right(1,5);



    int i = 1;
    auto iter = tree_of_ints.begin_preorder();

    while (iter != tree_of_ints.end_preorder()) {
        CHECK(*(iter++) == i++);
    }

}

template<typename V>
V random_V_value(V param) {

    // V random_val;

    // string type = typeid(V).name();
    // cout << "TYPE: " << type << endl;
    // cout << "random_val: " << random_val << endl;
    char *param_type = typeid(V).name();
    switch (*param_type)
    {
    case 'd':
        cout << "double" << endl;
        return (rand()%10) + (1/rand()%30);
        break;
    case 'i':
        cout << "int" << endl;
        return (rand()%10);
        break;
    case 'f':
        cout << "float" << endl;
        return (rand()%10) + (1/rand()%30);
        break;
    default:
        try {
            return "DEFAULT STR";
        } catch(const std::exception& e) {
            throw e;
        }
        break;
    }


    return random_val + random_val;
}

template<typename V = int> // can accept only trees of types that can be initialized with numbers, like: int, float, double, short, unsigned....
BinaryTree<V>* create_tree_of_size(int n) {

    srand(9);

    for (int i = 0; i < 10; i++)
    {
        random_V_value(3);
        // random_V_value("king");
        random_V_value(3.7);
    }
    
    set<V> used_nums; // n 0's or defaults

    unsigned long random = rand()%10;
    unsigned long  r;
    cout << "random = " << random << endl;

    BinaryTree<> *tree_of_ints;
    int root = random;
    tree_of_ints->add_root(root);
    used_nums.insert(root);
    // used_nums.at(random) = 1;

    for(int i = 0; i < n; i++) {
        random = rand()%10;
        cout << "random = " << random << endl;
        if(used_nums.count(random)) {
            cout << "has element: " << random << endl;
            r = rand()%10;
            used_nums.insert(r);
            CHECK_NOTHROW(tree_of_ints->add_left(random, r));
        } else {
            cout << "no element: " << random << endl;
            CHECK_THROWS(tree_of_ints->add_left(random, rand()%10));
            CHECK_THROWS(tree_of_ints->add_right(random, rand()%10));
        }
    }

    return tree_of_ints;
}

TEST_CASE("Test 4 - Building a tree of random numbers") {


    const int n = 30;   // reasonable amount of runs
    // vector<int> used_nums(n);
    
    // BinaryTree<> *t = create_tree_of_size(n);

    BinaryTree<string> strings = build(vector<string>({"d","a"}));
    
}