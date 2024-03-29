//
// Created by omar_ on 18/02/2024.
//

#ifndef AVLTREES_STRENGTHTREE_H
#define AVLTREES_STRENGTHTREE_H
//
// Created by allih on 15/02/2024.
//
#include "SNode.h"
#include <stdexcept>
#include <iostream>


template <typename T>

class STree{
    template <typename U> friend class SNode;
    friend class Team;
private:
    shared_ptr<SNode<T>> root;
    unsigned long long size;
    shared_ptr<SNode<T>> maximum;
    shared_ptr<SNode<T>> minimum;
    //Adjusted logic to compare based on strength and in case of strength equality to compare based on ID.

    //necessary for Team
    int maxComp(int a, int b){
        if(a > b) return a;
        return b;
    }


    shared_ptr<SNode<T>> findKthSmallest(shared_ptr<SNode<T>> node, int k, int extraSum = 0) {
        if (!node || k == 0) return nullptr;

        extraSum += node->extra;

        int leftSize = node->left ? node->left->size : 0;

        if (k <= leftSize) {
            return findKthSmallest(node->left, k, extraSum);
        } else if (k == leftSize + 1) {
            node->data->numOfWins = extraSum;
            return node;
        } else {
            return findKthSmallest(node->right, k - leftSize - 1, extraSum);
        }
    }

    void clearParents(std::shared_ptr<SNode<T>> node) {
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

    shared_ptr<SNode<T>> insertRecursively(shared_ptr<SNode<T>> node, shared_ptr<T> item, int  extraSum){
        if (node == nullptr) {
            auto current = make_shared<SNode<T>>(item);

            current->maxRank = (item->getSize()) ? (item->getStrength() + item->numOfWins) : 0;
            current->extra = item->numOfWins - extraSum;
            return current;
        }

        bool isLeft = false, isRight = false;

        extraSum += node->extra;
        node->data->numOfWins = extraSum;



        if (item->getStrength() < node->getStrength() ||
            (item->getStrength() == node->getStrength() && item->getID() > node->getID())) {
            isLeft = true;
        }

        else if (item->getStrength() > node->getStrength() ||
                 (item->getStrength() == node->getStrength() && item->getID() < node->getID())) {
            isRight = true;
        }

        if (isLeft){
            auto leftChild = insertRecursively(node->left, item, extraSum);
            node->left = leftChild;
            if (leftChild) leftChild->parent=node;

        }
        else if (isRight){
            auto rightChild = insertRecursively(node->right, item, extraSum);
            node->right=rightChild;
            if (rightChild) rightChild->parent=node;
        }

        node->height = 1 + maxComp(getHeight(node->left), getHeight(node->right));
        node->size = 1 + getSize(node->left) + getSize(node->right);
        int currRank = (node->data->getSize()) ? (node->getStrength() + node->data->numOfWins) : 0;
        node->maxRank = maxComp(currRank, maxComp(getMaxRank(node->left), getMaxRank(node->right)));

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
            node->left->data->numOfWins = extraSum + node->left->extra;
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
            //RL
        else if (balance < - 1 && getBalance(node->right) > 0){
            node->right->data->numOfWins = extraSum + node->right->extra;
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;

    }

    //delete now searches based on strength and ID
    bool deleteRecursively(shared_ptr<SNode<T>>& node, int ID, int strength, int extraSum){
        if (node == nullptr) return false;

        bool isLeft = false, isRight = false;
        bool deleted;

        extraSum += node->extra;
        node->data->numOfWins = extraSum;


        if (strength < node->getStrength() ||
            (strength == node->getStrength() && ID > node->getID())) {
            isLeft = true;
        }

        else if (strength > node->getStrength() ||
                 (strength == node->getStrength() && ID < node->getID())) {
            isRight = true;
        }

        if (isLeft) deleted = deleteRecursively(node->left, ID, strength, extraSum);
        else if (isRight) deleted = deleteRecursively(node->right, ID, strength, extraSum);

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
                    child->extra += node->extra;
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
                auto minNode = getMinNode(node->right, extraSum);
                int deletedNodeExtra = node->extra;
                node->data = minNode->data;
                int extraDiff = node->data->numOfWins - extraSum;
                node->extra = deletedNodeExtra + extraDiff;
                node->left->extra -= extraDiff;
                node->right->extra -= extraDiff;
                extraSum = node->data->numOfWins;
                deleteRecursively(node->right, minNode->getID(), minNode->getStrength(), extraSum);
            }


        }

        if (node==nullptr) return deleted;

        int currRank = (node->data->getSize()) ? (node->getStrength() + node->data->numOfWins) : 0;
        node->height = 1 + maxComp(getHeight(node->right), getHeight(node->left));
        node->size = 1 + getSize(node->left) + getSize(node->right);
        node->maxRank = maxComp(currRank, maxComp(getMaxRank(node->left), getMaxRank(node->right)));


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
            node->left->data->numOfWins = extraSum + node->left->extra;
            node->left = leftRotate(node->left);
            node = rightRotate(node);
        }
            //RL
        else if (balance < - 1 && getBalance(node->right) > 0){
            node->right->data->numOfWins = extraSum + node->right->extra;
            node->right = rightRotate(node->right);
            node = leftRotate(node);
        }

        return deleted;


    }




    shared_ptr<SNode<T>> rightRotate(shared_ptr<SNode<T>> node){
        auto leftChild = node->left;
        auto subTree = leftChild->right;

        int nodeRank = (node->data->getSize()) ? (node->getStrength() + node->data->numOfWins) : 0;
        int leftChildRank = (leftChild->data->getSize()) ? (leftChild->getStrength() + leftChild->data->numOfWins) : 0;

        //updating extras
        leftChild->extra += node->extra;
        node->extra -= leftChild->extra;
        //rotating
        leftChild->right = node;
        node->left = subTree;

        node->height = 1 + maxComp(getHeight(node->left),getHeight(node->right));
        leftChild->height = 1 + maxComp(getHeight(leftChild->left), getHeight(leftChild->right));
        node->size = 1 + getSize(node->left) + getSize(node->right);
        leftChild->size = 1 + getSize(leftChild->left) + getSize(leftChild->right);
        node->maxRank = maxComp(nodeRank, maxComp(getMaxRank(node->left), getMaxRank(node->right)));
        leftChild->maxRank = maxComp(leftChildRank, maxComp(getMaxRank(leftChild->left), getMaxRank(leftChild->right)));


        if (subTree != nullptr){
            subTree->parent = node;
            subTree->extra -= node->extra;
        }
        leftChild->parent = node->parent;
        node->parent = leftChild;

        // returning the new root.
        return leftChild;

    }

    shared_ptr<SNode<T>> leftRotate(shared_ptr<SNode<T>> node){
        auto rightChild = node->right;
        auto subTree = rightChild->left;

        int nodeRank = (node->data->getSize()) ? (node->getStrength() + node->data->numOfWins) : 0;
        int rightChildRank = (rightChild->data->getSize()) ? (rightChild->getStrength() + rightChild->data->numOfWins) : 0;
        //updating extras
        rightChild->extra += node->extra;
        node->extra -= rightChild->extra;

        //rotating
        rightChild->left = node;
        node->right = subTree;

        node->height = 1 + maxComp(getHeight(node->left), getHeight(node->right));
        rightChild->height = 1 + maxComp(getHeight(rightChild->left), getHeight(rightChild->right));
        node->size = 1 + getSize(node->left) + getSize(node->right);
        rightChild->size = 1 + getSize(rightChild->left) + getSize(rightChild->right);
        node->maxRank = maxComp(nodeRank, maxComp(getMaxRank(node->left), getMaxRank(node->right)));
        rightChild->maxRank = maxComp(rightChildRank, maxComp(getMaxRank(rightChild->left), getMaxRank(rightChild->right)));

        if (subTree != nullptr){
            subTree->parent = node;
            subTree->extra -= node->extra;
        }
        rightChild->parent = node->parent;
        node->parent = rightChild;

        return rightChild;
    }


    bool containsRecursively(shared_ptr<SNode<T>> node, int ID, int strength) const{
        if (node == nullptr) return false;
        bool isLeft = false;

        if (strength < node->getStrength() ||
            (strength == node->getStrength() && ID > node->getID())) {
            isLeft = true;
        }

        if (node->getID() == ID) return true;
        if (isLeft) return containsRecursively(node->left, ID, strength);
        else return containsRecursively(node->right, ID, strength);
    }

    shared_ptr<T> findRecursively(shared_ptr<SNode<T>> node, int ID, int strength, int extraSum) {
        if (node == nullptr) return nullptr;

        extraSum += node->extra;
        node->data->numOfWins = extraSum;
        bool isLeft = false;
        if (strength < node->getStrength() ||
            (strength == node->getStrength() && ID > node->getID())) {
            isLeft = true;
        }

        if (node->data->getID() == ID) return node->data;
        if (isLeft) return findRecursively(node->left, ID, strength, extraSum);
        else return findRecursively(node->right, ID, strength, extraSum);
    }

    int getHeight(shared_ptr<SNode<T>> node) const{
        if (node == nullptr) return -1;
        else return node->height;
    }

    shared_ptr<SNode<T>> getMinNode(shared_ptr<SNode<T>> node, int extraSum){
        if (!node) return nullptr;
        auto current = node;
        extraSum += current->extra;
        while (current->left != nullptr){
            current = current->left;
            extraSum += current->extra;
        }
        current->data->numOfWins = extraSum;
        return current;
    }
    shared_ptr<SNode<T>> getMaxNode(shared_ptr<SNode<T>> node, int extraSum){
        if (!node) return nullptr;
        auto current = node;
        extraSum += current->extra;
        while (current->right != nullptr){
            current = current->right;
            extraSum += current->extra;
        }
        current->data->numOfWins = extraSum;
        return current;
    }

    int getBalance(shared_ptr<SNode<T>> node) const{
        if (node == nullptr) return -1;
        else return node->getBF();
    }

    shared_ptr<SNode<T>> sortedArrayToAVL(shared_ptr<T>* arr, int start, int end) {
        if (start > end)
            return nullptr;

        int mid = start + (end - start) / 2;
        auto node = make_shared<SNode<T>>(arr[mid]);

        node->left = sortedArrayToAVL(arr, start, mid - 1);
        node->right = sortedArrayToAVL(arr, mid + 1, end);

        node->height = 1 + maxComp(getHeight(node->left), getHeight(node->right));
        node->size = 1 + getSize(node->left) + getSize(node->right);

        return node;
    }


public:

    explicit STree() : root(nullptr), size(0), maximum(nullptr), minimum(nullptr){}
    STree(const STree&) = delete;
    STree& operator=(const STree&)= delete;
    ~STree(){
        clearParents(root);
    }

    STree(shared_ptr<T>* arr, int size) : size(size) {
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


    // finds member with ID, returns NULL if he doesn't exist.
    shared_ptr<T> find(const int ID, const int strength) {
        return findRecursively(root, ID, strength, 0);
    }

    bool contains(const int ID, const int strength) const{
        return containsRecursively(root, ID, strength);
    }

    // Inserts item. Returns false in case of duplication. True otherwise.
    bool insert(shared_ptr<T> item){
        if(!item) throw logic_error("Cannot insert null item.");
        if (contains(item->getID(), item->getStrength())) return false; // this had a bug
        root = insertRecursively(root, item, 0);
        size++;
        minimum = getMinNode(root, 0);
        maximum = getMaxNode(root, 0);
        return true;
    }


    bool remove(const int ID, const int strength){
        if (!size) return false;
        if (deleteRecursively(root, ID, strength, 0)) {
            size--;
            minimum = getMinNode(root, 0);
            maximum = getMaxNode(root, 0);
            return true;
        }
        else return false;
    }

    shared_ptr<T> getMax(){
        if (size!=0 && maximum!=nullptr) return maximum->data;
        else return nullptr;
    }

    int getMaxStrength(){
        if (size!=0 && maximum!=nullptr) return maximum->data->getStrength();
        else return 0;
    }

    int getMinStrength(){
        if (size!=0 && minimum!=nullptr) return minimum->data->getStrength();
        else return 0;
    }

    shared_ptr<T> getMin(){
        if (size!=0 && minimum!=nullptr) return minimum->data;
        else return nullptr;
    }


    int getSize(shared_ptr<SNode<T>> node) const {
        return node ? node->size : 0; // Return 0 if node is nullptr, otherwise node's size
    }

    int getMaxRank(shared_ptr<SNode<T>> node) const {
        return node ? node->maxRank : 0;
    }

    int getSize() const{
        return size;
    }

    void inorderAddToArray(shared_ptr<SNode<T>> node, shared_ptr<T>* arr, int& index, int extraSum = 0){
        if (node == nullptr || arr == nullptr) return;
        inorderAddToArray(node->left, arr, index, extraSum + node->extra);

        node->data->numOfWins = extraSum + node->extra;
        arr[index++] = node->data;
        inorderAddToArray(node->right, arr, index, extraSum + node->extra);
    }

    //this function returns a sorted array of the elements in the tree. Needs to be freed once done!
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

    void TreePrintInOrder(shared_ptr<SNode<T>> node, int extraSum = 0) {
        if (!node) return;
        TreePrintInOrder(node->left, extraSum + node->extra);
        cout << "(" << "str:" << node->getStrength() << ", " << "id:" << node->getID() << ", ex:" << node->extra << ", maxR:" << node->maxRank <<")";
        TreePrintInOrder(node->right, extraSum + node->extra);
    }


    void TreePrintPreOrder(shared_ptr<SNode<T>> node, int extraSum = 0) {
        if (!node) return;
        cout<<"("<<"str:"<<node->getStrength()<<", "<<"id:"<<node->getID()<<", ex:"<<node->extra<<", maxR:"<<node->maxRank<<")";
        TreePrintPreOrder(node->left);
        TreePrintPreOrder(node->right);
    }

    shared_ptr<T> getKthSmallest(int k) {
        return findKthSmallest(root, k, 0)->data;
    }

    int getHighestRank() const{
        if(root == nullptr || size == 0) return 0;
        return root->maxRank;
    }

    //adds wins equal to wins amount to the teams with strengths in the range [i,j] inclusive. Similar to vaccines question.
    void auxAddWins(int highPower, int highId, int wins){
        auxAddWinsRecursive(root, highPower, highId, wins, false, 0);
    }


    int auxAddWinsRecursive(shared_ptr<SNode<T>> node, int highPower, int highId, int wins, bool rightStreak, int extraSum){
        if (!node) return 0;

        int maxRank = 0;
        int currRank = 0;
        int subTreeMaxRank = 0;
        int otherSubTreeMaxRank = 0;
        bool isLeft = false;
        bool isRight = false;

        if (highPower < node->getStrength() ||
            (highPower == node->getStrength() && highId > node->getID())) {
            isLeft = true;
        }

        else if (highPower > node->getStrength() ||
                 (highPower == node->getStrength() && highId < node->getID())) {
            isRight = true;
        }

        if (isRight){
            if (!rightStreak) node->extra += wins;

            extraSum += node->extra;

            if (node->left && !rightStreak) otherSubTreeMaxRank = node->left->maxRank + wins;
            else if (node->left) otherSubTreeMaxRank = node->left->maxRank;

            node->data->numOfWins = extraSum;
            currRank = (node->data->getSize()) ? (node->getStrength() + node->data->numOfWins) : 0;
            subTreeMaxRank = auxAddWinsRecursive(node->right, highPower, highId, wins, true, extraSum);
            maxRank = max(currRank, max(subTreeMaxRank, otherSubTreeMaxRank));
            node->maxRank = maxRank;
            return maxRank;

        } else if (isLeft){
            if (rightStreak) node->extra -= wins;

            extraSum += node->extra;
            if (node->right) otherSubTreeMaxRank = node->right->maxRank;
            node->data->numOfWins = extraSum;
            currRank = (node->data->getSize()) ? (node->getStrength() + node->data->numOfWins) : 0;
            subTreeMaxRank = auxAddWinsRecursive(node->left, highPower, highId, wins, false, extraSum);
            maxRank = max(currRank, max(subTreeMaxRank, otherSubTreeMaxRank));
            node->maxRank = maxRank;
            return maxRank;

        } else{
            if (!rightStreak) node->extra += wins;

            extraSum += node->extra;

            if (node->left && !rightStreak) otherSubTreeMaxRank = node->left->maxRank + wins;
            else if (node->left) otherSubTreeMaxRank = node->left->maxRank;

            node->data->numOfWins = extraSum;
            currRank = (node->data->getSize()) ? (node->getStrength() + node->data->numOfWins) : 0;

            if (node->right){
                node->right->extra -= wins;
                subTreeMaxRank = node->right->maxRank;
            }
            maxRank = max(currRank, max(subTreeMaxRank, otherSubTreeMaxRank));
            node->maxRank = maxRank;
            return maxRank;
        }




    }
    void addWins(int lowPower, int lowId, int highPower, int highId, int wins){
        auxAddWins(highPower, highId, wins);
        auxAddWins(lowPower, lowId+1, -wins);
    }


    bool addWinsToTeam(int teamID, int teamStrength, int wins){
        if (!contains(teamID, teamStrength)) return false;
        auto team = find(teamID, teamStrength);

        remove(teamID, teamStrength);
        team->numOfWins++;
        insert(team);

        return true;
    }

    //This implementation might seem confusing at first but the reason we have to find the team first is because when while searching for a team
    //we sum up the extras along the way and then update numOfWins before returning the team..
    // great approach, but how are you updating the extras field along the way? hence, if we want to find the team again, we have to update the extras field.

    //Thanks, searching for a team doesn't change any extras. It just sums up the extras along the way and makes sure that the private field of the team's win count is updated before we return it.
    // That way we can remember how many wins a team had before you remove it and reinsert it.
    int getTeamWins(int teamID, int teamStrength){
        if (!contains(teamID, teamStrength)) throw invalid_argument("team doesn't exist and we're trying to get its wins");
        auto team = find(teamID, teamStrength);
        return team->numOfWins;
    }


    int findRank(shared_ptr<SNode<T>> node, int ID, int strength, int& rank) const{
        if (node == nullptr) return -1;

        if (strength < node->getStrength() || (strength == node->getStrength() && ID > node->getID())) {
            return findRank(node->left, ID, strength, rank);
        }
        else if (strength > node->getStrength() || (strength == node->getStrength() && ID < node->getID())) {
            int leftSize = node->left ? node->left->size : 0;
            rank += leftSize + 1;
            return findRank(node->right, ID, strength, rank);
        }
        else {
            int leftSize = node->left ? node->left->size : 0;
            rank += leftSize + 1;
            //return rank + 1; //fuck this bug lmao I passed rank by reference but returning rank + 1 doesn't update the reference.
            return rank;

        }
    }

    int getRank(int ID, int strength) const{
        int rank = 0;
        int result = findRank(root, ID, strength, rank);
        if (result == -1) {
            return -1;
        }
        return rank;
    }


    shared_ptr<T> findRankedLowestNodeGEStrengthAux(shared_ptr<SNode<T>> node, int strength) {
        if (!node) return nullptr;

        shared_ptr<T> result = nullptr;

        if (node->getStrength() >= strength) {

            result = findRankedLowestNodeGEStrengthAux(node->left, strength);
            if (!result) {
                return node->data;
            }
        } else {

            return findRankedLowestNodeGEStrengthAux(node->right, strength);
        }

        return result;
    }

    shared_ptr<T> findLowestRankedGEStrength(int strength) {
        return findRankedLowestNodeGEStrengthAux(root, strength);
    }


    shared_ptr<T> findHighestRankedNodeLEStrengthAux(shared_ptr<SNode<T>> node, int strength) {
        if (!node) return nullptr;

        shared_ptr<T> result = nullptr;

        if (node->getStrength() <= strength) {

            result = findHighestRankedNodeLEStrengthAux(node->right, strength);
            if (!result) {

                result = node->data;
            }
        } else {
            result = findHighestRankedNodeLEStrengthAux(node->left, strength);
        }

        return result;
    }

    //
    shared_ptr<T> findHighestRankedLEStrength(int strength) {
        return findHighestRankedNodeLEStrengthAux(root, strength);
    }



    shared_ptr<T> findHighestIdWithStrengthAux(shared_ptr<SNode<T>> node, int strength, int extraSum = 0){
        if (!node) return nullptr;

        extraSum += node->extra;
        if (strength > node->getStrength()){
            return findHighestIdWithStrengthAux(node->right, strength);

        } else if (strength < node->getStrength()){
            return findHighestIdWithStrengthAux(node->left, strength);

        } else{
            while (node->left && node->left->getStrength() == strength){
                node = node->left;
                extraSum += node->extra;
            }
        }
            node->data->numOfWins = extraSum;
            return node->data;
    }

    shared_ptr<T> findHighestIdWithStrength(int strength){
        return findHighestIdWithStrengthAux(root, strength);
    }

    shared_ptr<T> findLowestIdWithStrengthAux(shared_ptr<SNode<T>> node, int strength, int extraSum = 0){
        if (!node) return nullptr;

        extraSum += node->extra;
        if (strength > node->getStrength()){
            return findLowestIdWithStrengthAux(node->right, strength);

        } else if (strength < node->getStrength()){
            return findLowestIdWithStrengthAux(node->left, strength);

        } else{
            while (node->right && node->right->getStrength() == strength){
                node = node->right;
                extraSum += node->extra;
            }
        }
        node->data->numOfWins = extraSum;
        return node->data;
    }

    shared_ptr<T> findLowestIdWithStrength(int strength){
        return findLowestIdWithStrengthAux(root, strength);
    }



};


#endif //AVLTREES_STRENGTHTREE_H
