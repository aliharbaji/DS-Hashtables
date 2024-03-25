//
// Created by allih on 24/03/2024.
//

#ifndef WET2_DS_PSTREE_H
#define WET2_DS_PSTREE_H
//
// Created by omar_ on 18/02/2024.
//

#include "node.h"
#include <stdexcept>
#include <iostream>


template <typename T>


class PSTree{
    template <typename U> friend class Node;
    friend class Team;
private:
    shared_ptr<Node<T>> root;
    int size;
    shared_ptr<Node<T>> maximum;
    shared_ptr<Node<T>> minimum;
    //Adjusted logic to compare based on strength and in case of strength equality to compare based on ID.

    //necessary for Team
    shared_ptr<Node<T>> findKthSmallest(shared_ptr<Node<T>> node, int k) {
        if (!node || k == 0) return nullptr;

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
        if (node != nullptr) {
            if (node->left != nullptr) {
                clearParents(node->left);
                node->left->parent = nullptr; // Clear the parent pointer
            }
            if (node->right != nullptr) {
                clearParents(node->right);
                node->right->parent = nullptr;
            }
        }
    }

    shared_ptr<Node<T>> insertRecursively(shared_ptr<Node<T>> node, shared_ptr<T> item){
        if (node == nullptr) return make_shared<Node<T>>(item);

        bool isLeft = false, isRight = false;

        if (item->getStrength() < node->getStrength() ||
            (item->getStrength() == node->getStrength() && item->getID() < node->getID())) {
            isLeft = true;
        }

        else if (item->getStrength() > node->getStrength() ||
                   (item->getStrength() == node->getStrength() && item->getID() > node->getID())) {
            isRight = true;
        }

        if (isLeft){
            auto leftChild = insertRecursively(node->left, item);
            node->left = leftChild;
            if (leftChild) leftChild->parent=node;

        }
        else if (isRight){
            auto rightChild = insertRecursively(node->right, item);
            node->right=rightChild;
            if (rightChild) rightChild->parent=node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        //Rotation logic stays the same
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

    //delete now searches based on strength and ID TODO: fix this, it contains a bug
    bool deleteRecursively(shared_ptr<Node<T>>& node, int ID, int strength){
        if (node == nullptr) return false;

        bool isLeft = false, isRight = false;
        bool deleted;

        if (strength < node->getStrength() ||
           (strength == node->getStrength() && ID < node->getID())) {
            isLeft = true;
        }

        else if (strength > node->getStrength() ||
                (strength == node->getStrength() && ID > node->getID())) {
            isRight = true;
        }

        if (isLeft) deleted = deleteRecursively(node->left, ID, strength);
        else if (isRight) deleted = deleteRecursively(node->right, ID, strength);

            // found the node
        else{
            // node has 1 or fewer children
            deleted = true;
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
                deleteRecursively(node->right, minNode->getID(), minNode->getStrength());
            }


        }

        if (node==nullptr) return deleted;

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

        return deleted;


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


    bool containsRecursively(shared_ptr<Node<T>> node, int ID, int strength) const{
        if (node == nullptr) return false;
        bool isLeft = false;

        if (strength < node->getStrength() ||
            (strength == node->getStrength() && ID < node->getID())) {
            isLeft = true;
        }

        if (node->getID() == ID) return true;
        if (isLeft) return containsRecursively(node->left, ID);
        else return containsRecursively(node->right, ID);
    }

    shared_ptr<T> findRecursively(shared_ptr<Node<T>> node, int ID, int strength) const{
        if (node == nullptr) return nullptr;

        bool isLeft = false;
        if (strength < node->getStrength() ||
            (strength == node->getStrength() && ID < node->getID())) {
            isLeft = true;
        }

        if (node->data->getID() == ID) return node->data;
        if (isLeft) return findRecursively(node->left, ID);
        else return findRecursively(node->right, ID);
    }

    int getHeight(shared_ptr<Node<T>> node) const{
        if (node == nullptr) return -1;
        else return node->height;
    }

    shared_ptr<Node<T>> getMinNode(shared_ptr<Node<T>> node){
        if (!node) return nullptr;
        auto current = node;
        while (current->left != nullptr){
            current = current->left;
        }
        return current;
    }
    shared_ptr<Node<T>> getMaxNode(shared_ptr<Node<T>> node){
        if (!node) return nullptr;
        auto current = node;
        while (current->right != nullptr){
            current = current->right;
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

    explicit PSTree() : root(nullptr), size(0), maximum(nullptr), minimum(nullptr){}
    PSTree(const PSTree&) = delete;
    PSTree& operator=(const PSTree&)= delete;
    ~PSTree(){
        clearParents(root);
    }

    PSTree(shared_ptr<T>* arr, int size) : size(size) {
        if(size) root = sortedArrayToAVL(arr, 0, size - 1);
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

    shared_ptr<SNode<T>> findKthSmallest(shared_ptr<SNode<T>> node, int k) {
        if (!node || k == 0) return nullptr;

        int leftSize = node->left ? node->left->size : 0;

        if (k <= leftSize) {
            return findKthSmallest(node->left, k);
        } else if (k == leftSize + 1) {
            return node;
        } else {
            return findKthSmallest(node->right, k - leftSize - 1);
        }
    }

    shared_ptr<T> getKthSmallest(int k) {
        return findKthSmallest(root, k)->data;
    }
    // finds member with ID, returns NULL if he doesn't exist.
    shared_ptr<T> find(const int ID) const{
        return findRecursively(root, ID);
    }

    bool contains(const int ID, const int strength) const{
        return containsRecursively(root, ID, strength);
    }

    // Inserts item. Returns false in case of duplication. True otherwise.
    bool insert(shared_ptr<T> item){
        if(!item) throw logic_error("Cannot insert null item.");
        if (!contains(item->getID(), item->getStrength())) return false;
        root = insertRecursively(root, item);
        size++;
        minimum = getMinNode(root);
        maximum = getMaxNode(root);
        return true;
    }

    bool remove(const int ID, const int strength){
        if (!size) return false;
        if (deleteRecursively(root, ID, strength)) {
            // TODO: I think that we should add an if statement here to check whether or not the deletion was successful,
            //  before updating the size and minimum and maximum.
            //You're absolutely right.
            size--;
            minimum = getMinNode(root);
            maximum = getMaxNode(root);
            return true;
        }
        else return false;
    }

    shared_ptr<T> getMax(){
        if (size) return maximum->data;
        else return nullptr;
    }

    int getMaxStrength(){
        if (size) return maximum->data->getStrength();
        else return 0;
    }

    int getMinStrength(){
        if (size) return maximum->data->getStrength();
        else return 0;
    }

    shared_ptr<T> getMin(){
        if (size) return minimum->data;
        else return nullptr;
    }


    int getSize(shared_ptr<Node<T>> node) const {
        return node ? node->size : 0; // Return 0 if node is nullptr, otherwise node's size
    }

    int getSize() const{
        return size;
    }

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

    void printTree(){
        cout<<"PreOrder: [";
        TreePrintPreOrder(root);
        cout<<"]"<<endl;
        cout<<"InOrder: [";
        TreePrintInOrder(root);
        cout<<"]"<<endl;
    }

    void TreePrintInOrder(shared_ptr<Node<T>> node) {
        if (!node) return;
        TreePrintInOrder(node->left);
        cout<<"("<<"str:"<<node->getStrength()<<", "<<"id: "<<node->getID()<<")";
        TreePrintInOrder(node->right);
    }


    void TreePrintPreOrder(shared_ptr<Node<T>> node) {
        if (!node) return;
        cout<<"("<<"str:"<<node->getStrength()<<", "<<"id: "<<node->getID()<<")";
        TreePrintPreOrder(node->left);
        TreePrintPreOrder(node->right);
    }
};




#endif //WET2_DS_PSTREE_H
