#ifndef BinarySearchTree_H
#define BinarySearchTree_H

#include <iostream>
#include <algorithm> 
#include <string> 

using std::cout, std::endl, std::string; 

template <typename T>
class BinarySearchTree {
protected: 
    struct BinaryNode {
        BinaryNode* left;
        BinaryNode* right;
        T           data; 

        BinaryNode() {
            left = right = nullptr; 
        }
        BinaryNode(const T& data_) : data(data_) {
            left = right = nullptr; 
        }
    };

public:
    //default constructor
    BinarySearchTree() = default;
    //Big3 1 -- copy constructor
    BinarySearchTree(const BinarySearchTree&);
    //Big3 2 -- assignment operator 
    BinarySearchTree& operator=(const BinarySearchTree&);
    //Big3 3 -- destructor
    ~BinarySearchTree(); 

    void clear();

    void preOrder(void (*fPointer)(T&));
    void inOrder(void (*fPointer)(T&));
    void postOrder(void (*fPointer)(T&));
    
    int size() const;
    int height() const;    
    int leafCount() const; 
    void print(std::ostream& out = cout) const;    
    bool empty() const; 

    //Binary Tree functions
    void insert(const T&);
    void remove(const T&);
    bool search(const T&);    

protected:
    BinaryNode* root = nullptr;
    
    BinaryNode* recursive_copy(BinaryNode*);
    void recursive_clear(BinaryNode*);
    
    void recursive_preOrder(BinaryNode*, void (*fPointer)(T&));
    void recursive_inOrder(BinaryNode*, void (*fPointer)(T&));
    void recursive_postOrder(BinaryNode*, void (*fPointer)(T&));

    int recursive_size(BinaryNode*) const;
    int recursive_height(BinaryNode*) const;
    int recursive_leafCount(BinaryNode*) const;
    void recursive_print(BinaryNode*, std::ostream&) const;

    //Binary Tree Functions
    //insert and remove, BinaryNode*&, passing a pointer by reference, not referencing a memory address
    //required to change the pointer in the tree
    void recursive_insert(BinaryNode*&, const T&);
    void recursive_remove(BinaryNode*&, const T&); 
    bool recursive_search(BinaryNode*, const T&); 

};

//Big3 1 -- copy constructor
template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& original){
    root = recursive_copy(original.root); 
}

//Big3 2 -- assignment operator 
template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& original) {
    //this = original
    //check for self-assignment
    if (this == &original) return *this; 
    //clear any nodes that are present in this object 
    this.clear(); 
    recursive_copy(original.root); 
    return *this; 
}

//Big3 -- recursive copy
template <typename T>
typename BinarySearchTree<T>::BinaryNode* BinarySearchTree<T>::recursive_copy(BinaryNode* subRoot) {
    if (!subRoot) return nullptr; 
    //preOrder V->L->R
    //V: 
    BinaryNode* copy = new BinaryNode(subRoot->data); 
    //L:
    copy->left = recursive_copy(subRoot->left);
    //R:
    copy->right = recursive_copy(subRoot->right); 
    return copy;   
}

//Big3 3 -- destructor
template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    clear(); 
}

template <typename T>
void BinarySearchTree<T>::clear(){
    //clear in postOrder L->R->V
    recursive_clear(root); 
    root = nullptr; 
}

template <typename T>
void BinarySearchTree<T>::recursive_clear(BinaryNode* subRoot){
    //clear in posOrder l->R->V
    //move through in post order and then delete subRoot. 
    if (subRoot) {
        recursive_clear(subRoot->left); 
        recursive_clear(subRoot->right);
        delete subRoot; 
    }

}

template <typename T>
void BinarySearchTree<T>::preOrder(void (*fPointer)(T&)) {
    //order V->L->R
    recursive_preOrder(root, fPointer);
}

template <typename T>
void BinarySearchTree<T>::recursive_preOrder(BinaryNode* subRoot, void (*fPointer)(T&)) {
    //order V->L->R
    if(subRoot) {
    //do something with fPointer at root->data
    fPointer(subRoot->data);
    //go left
    recursive_preOrder(subRoot->left, fPointer); 
    //go right
    recursive_preOrder(subRoot->right, fPointer); 
    }
}

template <typename T>
void BinarySearchTree<T>::inOrder(void (*fPointer)(T&)) {
    //Order L->V->R
    recursive_inOrder(root, fPointer); 
}

template <typename T>
void BinarySearchTree<T>::recursive_inOrder(BinaryNode* subRoot, void (*fPointer)(T&)) {
    //order L->V->R
    if (subRoot) { 
        recursive_inOrder(subRoot->left, fPointer); 
        fPointer(subRoot->data); 
        recursive_inOrder(subRoot->right, fPointer); 
    }
}

template <typename T>
void BinarySearchTree<T>::postOrder(void (*fPointer)(T&)) {
    //order L->R->V
    recursive_postOrder(root, fPointer); 
}

template <typename T>
void BinarySearchTree<T>::recursive_postOrder(BinaryNode* subRoot, void (*fPointer)(T&)) {
    //order L->R->V
    if (subRoot) {
        recursive_postOrder(subRoot->left, fPointer);
        recursive_postOrder(subRoot->right, fPointer);
        fPointer(subRoot->data);
    }
}

template <typename T>
int BinarySearchTree<T>::size() const {
    return (recursive_size(root));
}

template <typename T>
int BinarySearchTree<T>::recursive_size(BinaryNode* subRoot) const {
    if (!subRoot) return 0;
    return(1 + recursive_size(subRoot->left) + recursive_size(subRoot->right)); 
}

template <typename T>
int BinarySearchTree<T>::height() const {
    return recursive_height(root); 
}

template <typename T>
int BinarySearchTree<T>::recursive_height(BinaryNode* subRoot) const {
    if(!subRoot) return 0; 
    return (1 + std::max(recursive_height(subRoot->left), recursive_height(subRoot->right))); 
} 

template <typename T>
int BinarySearchTree<T>::leafCount() const {
    return recursive_leafCount(root);
}

template <typename T>
int BinarySearchTree<T>::recursive_leafCount(BinaryNode* subRoot) const {
    if (!subRoot){
        return 0;
    }
    if (!subRoot->left && !subRoot->right) return 1;
    return (recursive_leafCount(subRoot->left) + recursive_leafCount(subRoot->right));
}

template <typename T>
bool BinarySearchTree<T>::empty() const {
    return (!root); 
}

template <typename T>
void BinarySearchTree<T>::insert(const T& target) {
    recursive_insert(root, target); 
}

template <typename T>
void BinarySearchTree<T>::recursive_insert(BinaryNode*& subRoot, const T& target){
    if (!subRoot) {
        subRoot = new BinaryNode(target); 
    } else recursive_insert((target < subRoot->data) ? subRoot->left : subRoot->right, target);     
}

template <typename T>
void BinarySearchTree<T>::remove(const T& target) {
    recursive_remove(root, target); 
}

template <typename T>
void BinarySearchTree<T>::recursive_remove(BinaryNode*& subRoot, const T& target) {
    if (!subRoot) return;
    if (target == subRoot->data) {
        //1. no children
        //2. one child (use ternerary to swap left and right based on which one is not null)
        //3. 2 child (predecssor)
    } else recursive_remove((target < subRoot->data) ? subRoot->left : subRoot->right, target); 
} 

template <typename T>
bool BinarySearchTree<T>::search(const T& target){
    return recursive_search(root, target); 
} 

template <typename T>
bool BinarySearchTree<T>::recursive_search(BinaryNode* subRoot, const T& target) {
    if (subRoot) {
        if (target == subRoot->data) 
            return true;
        return recursive_search((target < subRoot->data) ? subRoot->left : subRoot->right, target); 
    }
    return false; 
} 

template <typename T>
void BinarySearchTree<T>::print(std::ostream& out) const {
    if (empty()) {
        out << string(4, ' ') << "----EMPTY TREE----" << endl; 
    } else {
        out << "Printing Tree.....\n" << string(20, '=') << endl;  
        if (root->left == nullptr && root->right == nullptr)
            out << root->data << ": - -" << endl; 
        recursive_print(root, out);
        out << string(20, '=') << endl;
    }
}

template <typename T>
void BinarySearchTree<T>::recursive_print(BinaryNode* subRoot, std::ostream& out) const {
    if (subRoot) {
        if (subRoot->left != nullptr || subRoot->right != nullptr) {
            out << subRoot->data << ": ";
            if (subRoot->left) {
                out << subRoot->left->data << " ";
            } else cout << "- ";
            if (subRoot->right) {
                out << subRoot->right->data << endl;
            } else out << "-" << endl; 
            recursive_print(subRoot->left, out); 
            recursive_print(subRoot->right, out); 
        }
    }
   
}    

#endif