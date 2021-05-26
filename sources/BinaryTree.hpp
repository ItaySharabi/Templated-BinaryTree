#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

namespace ariel {    

    enum Traverse{
        PreOrder, InOrder, PostOrder
    };
    template<typename T = int>
    class BinaryTree {
        private:
            struct Node {
                T val;
                Node *left, *right, *parent;
                Node(const T& value):val(value), left(nullptr), right(nullptr), parent(nullptr){} 
                ~Node(){delete left; delete right;} // take care of releasing all nodes
                // friend ostream& operator<< (ostream& os, const Node& node) {return os << val << endl;}
            };
            
            class iterator { 
                private:
                    Node* curr_node_ptr;
                    Traverse order;
                    queue<Node*> q;
                public:

                    void traverse_in_order(Node* root, queue<Node*>& q) {
                        if (root == nullptr) return;
                        traverse_in_order(root->left, q);
                        q.push(root);
                        traverse_in_order(root->right, q);
                    }
                    void traverse_pre_order(Node* root, queue<Node*>& q) {
                        if (root == nullptr) return;
                        q.push(root);
                        traverse_pre_order(root->left, q);
                        traverse_pre_order(root->right, q);
                    }
                    void traverse_post_order(Node* root, queue<Node*>& q) {
                        if (root == nullptr) return;
                        traverse_post_order(root->left, q);
                        traverse_post_order(root->right, q);
                        q.push(root);
                    }

                    iterator(Traverse order, Node* n = nullptr):curr_node_ptr(n), order(order) {
                        if (n == nullptr) return;
                        switch(order) {
                            case Traverse::PreOrder:
                                {cout << "Pre" << endl;
                                traverse_pre_order(curr_node_ptr, q);
                                // q.pop();
                                break;}
                            case Traverse::InOrder:
                                {cout << "In" << endl;
                                traverse_in_order(curr_node_ptr, q);
                                break;}
                            case Traverse::PostOrder:
                                {cout << "Post" << endl;
                                traverse_post_order(curr_node_ptr, q);
                                break;}
                        }
                        q.push(nullptr);
                        curr_node_ptr = q.front();
                        q.pop();
                    }
                    
                    iterator& operator++ (){
                        curr_node_ptr = q.front();
                        q.pop();
                                                                                                   
                        return *this;
                    }
                    // iterator operator++ (int a){
                    //     iterator t{order, curr_node_ptr};
                    //     this->curr_node_ptr = q.front();
                    //     q.pop();
                    //     return t;
                    // }

                    bool operator!= (const iterator& other){return !q.empty();}
                    const T& operator* () const {return curr_node_ptr->val;}
                    const T* operator->() const {return &(curr_node_ptr->val);}
                    // friend std::ostream& operator <<(std::ostream& os, const iterator& it) {return os << "*it = " << curr_node_ptr << std::endl;}
            };

            Node* root;
            map<T, Node*> nodes;

        public:
            BinaryTree():root(nullptr){}
            BinaryTree<T>& add_root(const T& v){
                if(root == nullptr) {
                    root = new Node(v);
                    nodes[v] = root;
                }
                else {
                    root->val = v;
                    // nodes.erase()
                }
                return *this;
            }
        
            BinaryTree<T>& add_left(const T& v1, const T& v2){

                auto t = nodes.find(v1);
                if (t != nodes.end()) {
                    // cout << "has element " << v1 << endl;
                    if(t->second->left != nullptr) {
                        cout << "has a right -> changing values" << endl;
                        t->second->left->val = v2;
                    } else {
                        cout << "does not have left -> creating left child" << endl;
                        t->second->left = new Node(v2);
                        nodes[v2] = t->second->left;
                    }
                } else {
                    throw std::invalid_argument("Cannot find a node with expected value: ");
                }
                // if ()

                // auto it = begin_preorder();
                // Node* curr = root;
                // for (; it != end_preorder(); ++it) {
                //     //root
                //     if (*it == v1){// ... 
                //         // curr->val = v2;
                //         cout << "Found node!" << endl;
                //     }
                //     //left
                //     if (curr->left != nullptr) {curr = curr->left;}
                //     //right
                //     else if (curr->right != nullptr) {curr = curr->right;}
                // }

                return *this;
            }
      
            BinaryTree<T>& add_right(const T& v1, const T& v2){
                auto t = nodes.find(v1);
                if (t != nodes.end()) {
                    // cout << "has element " << v1 << endl;
                    if(t->second->right != nullptr) {
                        cout << "has a right -> changing values" << endl;
                        t->second->right->val = v2;
                    } else {
                        cout << "does not have right -> creating right child" << endl;
                        t->second->right = new Node(v2);
                    }
                } else {
                    throw std::invalid_argument("Cannot find a node with expected value: ");
                }
                return *this;
            }
            
            iterator begin_preorder(){return iterator{Traverse::PreOrder, root};}
            iterator end_preorder(){return iterator{Traverse::PreOrder, nullptr};} 

            iterator begin_inorder(){return iterator{Traverse::InOrder, root};}
            iterator end_inorder(){return iterator{Traverse::InOrder, nullptr};}

            iterator begin_postorder(){return iterator{Traverse::PostOrder, root};}
            iterator end_postorder(){return iterator{Traverse::PostOrder, nullptr};}
            
            iterator begin() {return iterator{Traverse::InOrder, root};}
            iterator end() {return iterator{Traverse::InOrder, nullptr};}
            
            friend std::ostream& operator <<(std::ostream& os, const BinaryTree& tree) {
                return os << "Printing tree... " << std::endl;
            }            
    };
};