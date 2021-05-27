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
                Node *left, *right/*, *parent*/;
                Node(const T& value):val(value), left(nullptr), right(nullptr)/*, parent(nullptr)*/{} 
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
                                traverse_pre_order(curr_node_ptr, q);
                                break;
                            case Traverse::InOrder:
                                traverse_in_order(curr_node_ptr, q);
                                break;
                            case Traverse::PostOrder:
                                traverse_post_order(curr_node_ptr, q);
                                break;
                        }
                        q.push(nullptr);            // Push last element to avoid an empty stack when pointing to last node.
                        curr_node_ptr = q.front();  // Points to first node in reqeusted traverse order
                        q.pop();                    // pop node out of the queue.
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
                    Node* get_node_ptr()  const {return curr_node_ptr;}
                    // friend std::ostream& operator <<(std::ostream& os, const iterator& it) {return os << "*it = " << curr_node_ptr << std::endl;}
            };

            Node* root;
            // map<T, Node*> nodes;

        public:
            BinaryTree():root(nullptr){}
            BinaryTree<T>& add_root(const T& v){
                if(root == nullptr) {
                    root = new Node(v);
                    // nodes[v] = root;
                }
                else {
                    root->val = v;
                    // nodes.erase()
                }
                return *this;
            }

            Node* get_node_ptr(const T& val, Node* start) {
                if(start == nullptr) return nullptr;

                if(start->val == val) return start;
                return get_node_ptr(val, start->left);
                return get_node_ptr(val, start->right);
            }
        
            BinaryTree<T>& add_left(const T& v1, const T& v2){

                Node* test = get_node_ptr(v1, root);

                if (test != nullptr) {
                    // if found a node with a value v1
                    if (test->left == nullptr) 
                        test->left = new Node(v2);
                    else test->left->val = v2;
                } else {
                    throw std::invalid_argument("Cannot find a node with the specified value");
                }
                // if (test != nullptr) {
                //     cout << "test = " << test->val << endl;
                // }

                // auto it = begin_preorder();
                // Node *candidate;
                // while (it != end_preorder()) {
                //     if (*it == v1) {
                //         candidate = it.get_node_ptr();
                //         break;
                //     }
                //     ++it;
                // }
                // if (candidate != nullptr) {
                //     if (candidate->left == nullptr) {
                //         candidate->left = new Node(v2);
                //     } else candidate->left->val = v2;
                // }
                return *this;
            }
      
            BinaryTree<T>& add_right(const T& v1, const T& v2){

                // Node* test = getNode_ptr(v1, root);

                Node* test = get_node_ptr(v1, root);

                if (test != nullptr) {
                    // if found a node with a value v1
                    if (test->right == nullptr) 
                        test->right = new Node(v2);
                    else test->right->val = v2;
                } else {
                    throw std::invalid_argument("Cannot find a node with the specified value");
                }

                // if (test != nullptr) {
                //     cout << "RIGHT test = " << test->val << endl;
                // }
                // auto it = begin_preorder();
                // Node *candidate;
                // while (it != end_preorder()) {
                //     if (*it == v1) {
                //         candidate = it.get_node_ptr();
                //         break;
                //     }
                //     ++it;
                // }
                // if (candidate != nullptr) {
                //     if (candidate->right == nullptr) {
                //         candidate->right = new Node(v2);
                //     } else candidate->right->val = v2;
                // }
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