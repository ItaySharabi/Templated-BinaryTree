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

TEST_CASE("Test 0: Construction and Destruction (Trivial)") {
    // CHECK_NOTHROW(BinaryTree<int> tree_of_ints;);
    // CHECK_NOTHROW(BinaryTree<float> tree_of_floats;);
    // CHECK_NOTHROW(BinaryTree<string> tree_of_strings;);
    // CHECK_NOTHROW(BinaryTree<char *> tree_of_char_ptrs;);
    // BinaryTree<int> tree_of_ints;
    // BinaryTree<float> tree_of_floats;
    // BinaryTree<string> tree_of_strings;
    // CHECK_NOTHROW(tree_of_ints.add_root(3));
    // CHECK_NOTHROW(tree_of_floats.add_root(83.22));
    // CHECK_NOTHROW(tree_of_strings.add_root("Hello, world!"));
}


/** 
 * @param vector<V>: A vector ONLY of size 5, with any elements.
 *  A simple method to fill a tree with elements from a vector v
 */
template<typename V = int>
BinaryTree<V> fill_tree(vector<V> v) {
    if (v.size() != 5){
        BinaryTree<V> tree_of_ints;
        V some_val;
        tree_of_ints.add_root(some_val).
        add_left(some_val, some_val).
        add_left(some_val, some_val).
        add_right(some_val, some_val).
        add_right(some_val, some_val);
        return tree_of_ints;
    }

    BinaryTree<V> ans;
     /*             0
                   / \
                  1   4
                 / \ 
                2   3 
    */
    CHECK_NOTHROW(
    ans.add_root(v.at(0)).
    add_left(v.at(0),v.at(1)).
    add_left(v.at(1),v.at(2)).
    add_right(v.at(1),v.at(3)).
    add_right(v.at(0),v.at(4)));

    return ans;
}

/**
 * @param BinaryTree<V>: any tree of any typename should work.
 * A method to test the tree iterators:
 * 1. Pre-Order iterator will always start with root node.
 * 2. Post-Order iterator will always finish with root node.
 * 3. In-Order iterator and the tree's default iterator - will give the same iteration results.
 **/
template <typename V = int>
void test_iterators(BinaryTree<V> tree) {

    auto pre_iter = tree.begin_preorder();  // root -> left -> right. 
    auto post_iter = tree.begin_postorder();// left -> right -> root.
    auto in_iter1 = tree.begin_inorder();   // left -> root -> right
    auto in_iter2 = tree.begin();           // like in-order

    V root; 
    for(;post_iter != tree.end_postorder(); ++post_iter) {
        root = *post_iter;
    } // after for loop, 'root' will get the value (V) of the root of 'tree'

    // pre_iter should point to root first
    CHECK(*pre_iter == root);   // Check if pre and post iterators return the root as first/last element
    /* ^ IF Type V has operator == ^ */


    // in-order and regular begin() should behave the same in terms of traversal
    for (; in_iter1 != tree.end() && in_iter2 != tree.end_inorder();) {
        cout << "*in_iter1 = " << *in_iter1 << ", " << " *in_iter2 = " << *in_iter2 << endl;
        CHECK(*(++in_iter1) == *(++in_iter2));
    }
}   


template<typename T = int>
void test_add_methods(vector<T> elements) {

    BinaryTree<T> test_tree;
    
    T new_root, new_left, new_right;
    T rand_val;
    test_tree.add_root(rand_val);   // init with default root
                                    
    unsigned int random;

    for(unsigned int i = 0; i < elements.size()-2; i++) {
        new_root = elements.at(i); //  3
        new_left = elements.at(i+1);// 3
        new_right = elements.at(i+2);//6

        random = ((unsigned long)rand() % (elements.size()-2)); // random index
        // cout << "random = " << random << endl;
        if (random >= elements.size()) continue;    // `random` recieves large values at last iteration
        
        rand_val = elements.at(random);                       // random value 
        // cout << "rand_val = " << rand_val << endl;
        if(new_root != rand_val && new_left != rand_val && new_right != rand_val) {
            /* if found a value which does not belong to the tree */
            CHECK_THROWS(test_tree.add_left(rand_val, rand_val));
            CHECK_THROWS(test_tree.add_right(rand_val, rand_val));
        } else {
            /* if found a value which belongs to the tree */
            CHECK_NOTHROW(test_tree.add_root(new_root));
            CHECK_NOTHROW(test_tree.add_left(new_root, new_left));
            CHECK_NOTHROW(test_tree.add_right(new_root, new_right));
            test_iterators(test_tree); // tree of size 3: root, left and right.
        } 
    }

}

TEST_CASE("Test 1: Traversal Orders (Pre-set 5-Node trees)") {
    // Pre-determined trees of size 5
    BinaryTree</*int*/> tree_of_ints; // tree 1
    tree_of_ints = fill_tree<int>({1,2,3,4,5});
    /*              1       tree form
                   / \
                  2   5
                 / \ 
                3   4 
    */
// ==================================
    
    BinaryTree<double> tree_of_doubles; // tree 2 (same tree as 1)
    tree_of_doubles = fill_tree<double>({1.4,2.5,3.5,4,5});
    /*             1.4       tree form
                   / \
                 2.5  5
                 / \ 
               3.5  4 
    */
// ==================================

    BinaryTree<string> tree_of_strings; // tree 3 (same tree as 1)
    tree_of_strings = fill_tree<string>({"Hello","world!", "CPP", "IS", "FUN!"});
    /*            Hello
                  /   \
              world!   FUN
               / \ 
            CPP   IS 
    */
// ==================================

    SUBCASE("Iterators General check") {
        test_iterators(tree_of_ints);
        test_iterators(tree_of_doubles);
        test_iterators(tree_of_strings);
    }

    SUBCASE("Iteration orders - Manual check"){
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

TEST_CASE("Test 2: Add Methods (3-Node trees)") {

    srand(0);

    vector<int> rand_ints(100);
    vector<double> rand_doubles(100);
    vector<string> rand_strings = {"Hello, ", "world! ", "This ", "is ", "a ", "binary ", "tree ", "test!"};
    for(unsigned int i = 0; i < rand_ints.size(); i++) {
        rand_ints.at(i) = rand()%10;
        rand_doubles.at(i) = (double)(rand_ints.at(i)/5.0) + 1;
    }

    test_add_methods<int>(rand_ints);
    test_add_methods<double>(rand_doubles);
    test_add_methods<string>(rand_strings);
}