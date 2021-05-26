#pragma once
#include <iostream>
#include <map>

namespace ariel {    

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
            
            class iterator { // in_order, SHOULD BE CONST OR NOT?
                private:
                    Node* curr_node_ptr;
                public:
                    iterator(Node* n = nullptr):curr_node_ptr(n) {}
                    
                    iterator& operator++ (){
                        // std::cout << "*k " << curr_node_ptr->val << std::endl;
                        return *this;
                    }
                    iterator operator++ (int a){
                        iterator t{curr_node_ptr};
                        // std::cout << "*t " << *t << std::endl;
                        return t;
                    }

                    bool operator!= (const iterator& other){return false;}
                    const T& operator* () const {return curr_node_ptr->val;}
                    const T* operator->() const { return &(curr_node_ptr->val); }
                    // friend std::ostream& operator <<(std::ostream& os, const iterator& it) {return os << "*it = " << curr_node_ptr << std::endl;}
            };

            Node* root;

        public:
            BinaryTree():root(nullptr){}
            BinaryTree<T>& add_root(const T& v){
                if(root == nullptr) root = new Node(v);
                else {
                    root->val = v;
                }
                return *this;
            }
            BinaryTree<T>& add_left(const T& v1, const T& v2){return *this;}
            BinaryTree<T>& add_right(const T& v1, const T& v2){return *this;}
            
            
            iterator begin_preorder(){return iterator{root};}
            iterator end_preorder(){return end();} 

            iterator begin_inorder(){return iterator{root};}
            iterator end_inorder(){return end();}

            iterator begin_postorder(){return iterator{root};}
            iterator end_postorder(){return end();}
            
            iterator begin() {return iterator{root};}
            iterator end() {return iterator{nullptr};}
            
            friend std::ostream& operator <<(std::ostream& os, const BinaryTree& tree) {
                return os << "Printing tree... " << std::endl;
            }

    };
};