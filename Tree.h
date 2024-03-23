//
// Created by allih on 15/02/2024.
//
#include "node.h"
#include <stdexcept>
#include <math.h>
#ifndef AVLTREES_TREE_H
template <typename T>

class Tree{
    template <typename U> friend class Node;
    friend class Team;

private:
    shared_ptr<Node<T>> root;
    shared_ptr<Node<T>> maximum;
    shared_ptr<Node<T>> minimum; //this is needed for austerity measure.
    int size;



    //for team algorithms.


    shared_ptr<Node<T>> findKthSmallest(shared_ptr<Node<T>> node, int k) {
//        if (!node || k==0) return nullptr; // Check for null node
        // this is probably a bug, if k==0, we should return the node, not nullptr
        if(!node) return nullptr;
        if (k == 0) return node;

        int leftSize = node->left ? node->left->size : 0;

        if (k <= leftSize) {
            return findKthSmallest(node->left, k);
        } else if (k == leftSize + 1) {
            return node;
        } else {
            return findKthSmallest(node->right, k - leftSize - 1);
        }
    }

    void clearParents(std::shared_ptr<Node<T>> node) {
        if (node != nullptr) { // removed unnecessary if statements
            clearParents(node->left);
            clearParents(node->right);
            node->parent = nullptr;
        }
    }
    //The recursion takes an insertion node as an argument and returns the root of the subtree which may or may not change depending on insert location.
    shared_ptr<Node<T>> insertRecursively(shared_ptr<Node<T>> node, shared_ptr<T> item){
        if (node == nullptr) return make_shared<Node<T>>(item);

        if (item->getID() < node->getID()){
            auto leftChild = insertRecursively(node->left, item);
            node->left = leftChild;
            if (leftChild) leftChild->parent=node;

        }
        else if (item->getID() > node->getID()){
            auto rightChild = insertRecursively(node->right, item);
            node->right=rightChild;
            if (rightChild) rightChild->parent=node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        node->size = 1 + getSize(node->left) + getSize(node->right);

        int balance = getBalance(node);

        //Left-Left Heavy. We rotate the left child to the right swapping its place with the current node.
        if (balance > 1 && getBalance(node->left) >= 0){
            return rightRotate(node);
        }
            //RR
        else if (balance < -1 && getBalance(node->right) <= 0){
            return leftRotate(node);
        }

            //Left-Right Heavy. We rotate the left subtree to the left, then we rotate the current tree to the right.
        else if (balance > 1 && getBalance(node->left) < 0){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
            //RL
        else if (balance < - 1 && getBalance(node->right) > 0){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;

    }

    void deleteRecursively(shared_ptr<Node<T>>& node, int ID){
        if (node == nullptr) return;
        if (ID < node->getID()) deleteRecursively(node->left, ID);
        else if (ID > node->getID()) deleteRecursively(node->right, ID);

            // found the node
        else{
            // node has 1 or fewer children
            if (node->right == nullptr || node->left == nullptr){
                auto child = (node->left == nullptr) ? node->right : node->left;
                // no child case
                if (child == nullptr){
                    if (node->parent != nullptr) {
                        if (node->parent->left == node) node->parent->left = nullptr;
                        else if (node->parent->right == node) node->parent->right = nullptr;
                    }
                    node = nullptr;
                }
                    // 1 child case
                else{
                    child->parent = node->parent;
                    if (node->parent != nullptr) {
                        if (node->parent->left == node) node->parent->left = child;
                        else node->parent->right = child;
                    }
                    node = child;

                    /* probably incorrect approach
                    node->data = child->data;
                    node->left = child->left;
                    node->right = child->right;
                    if (node->left) node->left->parent = node;
                    if (node->right) node->right->parent = node; */
                }
            }
                // 2 child case
            else{
                // find the smallest child in the right subtree to become new root
                auto minNode = getMinNode(node->right);
                node->data = minNode->data;
                deleteRecursively(node->right, minNode->getID());
            }


        }

        if (node==nullptr) return;

        node->height = 1 + max(getHeight(node->right), getHeight(node->left));
        node->size = 1+ getSize(node->left) + getSize(node->right);
        int balance = getBalance(node);

        //Left-Left Heavy. We rotate the left child to the right swapping its place with the current node.
        if (balance > 1 && getBalance(node->left) >= 0){
            node = rightRotate(node);
        }
            //RR
        else if (balance < -1 && getBalance(node->right) <= 0){
            node = leftRotate(node);
        }

            //Left-Right Heavy. We rotate the left subtree to the left, then we rotate the current tree to the right.
        else if (balance > 1 && getBalance(node->left) < 0){
            node->left = leftRotate(node->left);
            node = rightRotate(node);
        }
            //RL
        else if (balance < - 1 && getBalance(node->right) > 0){
            node->right = rightRotate(node->right);
            node = leftRotate(node);
        }


    }



    shared_ptr<Node<T>> rightRotate(shared_ptr<Node<T>> node){
        auto leftChild = node->left;
        auto subTree = leftChild->right;
        //rotating
        leftChild->right = node;
        node->left = subTree;

        node->height = 1 + max(getHeight(node->left),getHeight(node->right));
        leftChild->height = 1 + max(getHeight(leftChild->left), getHeight(leftChild->right));
        node->size = 1 + getSize(node->left) + getSize(node->right);
        leftChild->size = 1 + getSize(leftChild->left) + getSize(leftChild->right);

        if (subTree != nullptr) subTree->parent = node;
        leftChild->parent = node->parent;
        node->parent = leftChild;

        // returning the new root.
        return leftChild;

    }

    shared_ptr<Node<T>> leftRotate(shared_ptr<Node<T>> node){
        auto rightChild = node->right;
        auto subTree = rightChild->left;
        //rotating
        rightChild->left = node;
        node->right = subTree;

        node->height = 1 + max(getHeight(node->left),getHeight(node->right));
        rightChild->height = 1 + max(getHeight(rightChild->left), getHeight(rightChild->right));
        node->size = 1 + getSize(node->left) + getSize(node->right);
        rightChild->size = 1 + getSize(rightChild->left) + getSize(rightChild->right);

        if (subTree != nullptr) subTree->parent = node;
        rightChild->parent = node->parent;
        node->parent = rightChild;

        // returning the new root.
        return rightChild;

    }


    bool containsRecursively(shared_ptr<Node<T>> rootNode, int ID) const{
        if (rootNode == nullptr) return false;
        if (rootNode->data->getID() == ID) return true;
        if (ID < rootNode->data->getID()) return containsRecursively(rootNode->left, ID);
        else return containsRecursively(rootNode->right, ID);
    }

    shared_ptr<T> findRecursively(shared_ptr<Node<T>> node, int ID) const{
        if (node == nullptr) return nullptr;
        if (node->data->getID() == ID) return node->data;
        if (ID < node->data->getID()) return findRecursively(node->left, ID);
        else return findRecursively(node->right, ID);
    }

    int getHeight(shared_ptr<Node<T>> node) const{
        if (node == nullptr) return -1;
        else return node->height;
    }

    shared_ptr<Node<T>> getMaxNode(shared_ptr<Node<T>> node){
        if (!node) return nullptr;
        auto current = node;
        while (current->right != nullptr){
            current = current->right;
        }
        return current;
    }

    shared_ptr<Node<T>> getMinNode(shared_ptr<Node<T>> node){
        if (!node) return nullptr;
        auto current = node;
        while (current->left != nullptr){
            current = current->left;
        }
        return current;
    }

    int getBalance(shared_ptr<Node<T>> node) const{
        if (node == nullptr) return -1;
        else return node->getBF();
    }

    shared_ptr<Node<T>> sortedArrayToAVL(shared_ptr<T>* arr, int start, int end) {
        if (start > end)
            return nullptr;

        int mid = start + (end - start) / 2;
        auto node = make_shared<Node<T>>(arr[mid]);

        node->left = sortedArrayToAVL(arr, start, mid - 1);
        node->right = sortedArrayToAVL(arr, mid + 1, end);

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        node->size = 1 + getSize(node->left) + getSize(node->right);

        return node;
    }



public:

    Tree() : root(nullptr), maximum(nullptr), minimum(nullptr), size(0){}
    //constructor for a tree based on an array and its size.
    Tree(const Tree&) = delete;
    Tree& operator=(const Tree&)= delete;
    ~Tree(){
        clearParents(root);
    }//Necessary to break cyclical pointers and appropriately deallocate memory.

    Tree(shared_ptr<T>* arr, int size) : size(size) {
        if (size) root = sortedArrayToAVL(arr, 0, size - 1);
        else root = nullptr;
        minimum = root;
        while (minimum != nullptr && minimum->left != nullptr) {
            minimum = minimum->left;
        }
        maximum = root;
        while (maximum != nullptr && maximum->right != nullptr) {
            maximum = maximum->right;
        }
    }

    // finds member with ID, returns NULL if he doesn't exist.
    shared_ptr<T> find(const int ID){
        return findRecursively(root, ID);
    }

    bool contains(const int ID) const{
        return containsRecursively(root, ID);
    }

    // Inserts item. Returns false in case of duplication. True otherwise.
    bool insert(shared_ptr<T> item){
        if(!this) throw logic_error("Cannot insert null item.");
        if (contains(item->getID())) return false;

        root = insertRecursively(root, item);
        size++;
        minimum = getMinNode(root);
        maximum = getMaxNode(root);
        return true;
    }

    bool remove(const int ID){
        if (!contains(ID) || root == nullptr) return false;
        deleteRecursively(root, ID);
        size--;
        minimum = getMinNode(root);
        maximum = getMaxNode(root);
        return true;
    }

    // self_explanatory. Returns the data of the biggest member. Returns null in case of empty so careful.
    shared_ptr<T> getMax() const{
        if (size && maximum!=nullptr) return maximum->data;
        else return nullptr;
    }

    shared_ptr<T> getMin() const{
        if (size && minimum!=nullptr) return minimum->data;
        else return nullptr;
    }

    int getSize(shared_ptr<Node<T>> node) const {
        return node ? node->size : 0; // Return 0 if node is nullptr, otherwise node's size aka subtree's size.
    }

    int getSize() const{
        return size;
    }

//    void inorderedDeletion(shared_ptr<Node<T>> root){
//        if(root == nullptr) return;
//        inorderedDeletion(root->left);
//        inorderedDeletion(root->right);
//        this->remove(root->data->getID());
//    }

    // TODO: move to private
    void inorderAddToArray(shared_ptr<Node<T>> node, shared_ptr<T>* arr, int& index){
        if (node == nullptr || arr == nullptr) return;
        inorderAddToArray(node->left, arr, index);
        arr[index++] = node->data;
        inorderAddToArray(node->right, arr, index);
    }
    //this function returns a sorted array of the elements in the tree.
    shared_ptr<T>* returnSortedArrayOfElements(){
        if (size == 0) return nullptr;
        auto arr = new shared_ptr<T>[size];
        int index = 0;
        inorderAddToArray(root, arr, index);
        return arr;
    }

    shared_ptr<T> getKthSmallest(int k) {
        return findKthSmallest(root, k)->data;
    }


    void inorderPrint(shared_ptr<Node<T>> curr, ostream& os) const{
        if(curr){
            inorderPrint(curr->left, os);
            os << string("(ID: ") << curr->getID() << string(" STR: ") << curr->getStrength() << "), ";
            inorderPrint(curr->right, os);
        }
    }

    friend ostream& operator<<(ostream& os, const Tree& tree){
        if(tree.root == nullptr){
            os << std::string("X");
            return os;
        }

        os << std::string("[");
        tree.inorderPrint(tree.root, os);
        os << std::string("]");
        return os;
    }

};
#define AVLTREES_TREE_H

#endif //AVLTREES_TREE_H
