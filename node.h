//
// Created by allih on 09/02/2024.
//

#include <memory>

#ifndef AVLTREES_NODE_H
using namespace std;
#define AVLTREES_NODE_H
#include "memory"


template <class T>
class Node{
private:
    template<typename U> friend class Tree;

public:
    shared_ptr<T> data;
    int height;
    int size; //We need to know the size of each subtree for efficiently dividing the tree into subtrees.
    shared_ptr<Node<T>> left, right;
    shared_ptr<Node<T>> parent;

    Node(shared_ptr<T> data): data(data),  height(0), size(1),
    left(nullptr), right(nullptr), parent(){}

    int getID() const {
        return data->getID();
    }

    int getStrength() const{
        return data->getStrength();
    }

    int getBF() const{
        int leftHeight = (left != nullptr) ? left->height : -1;
        int rightHeight = (right != nullptr) ? right->height : -1;
        int bf = leftHeight - rightHeight;
        return bf;
    }

    int getRank() const{
        return data->getRank();
    }

};


#endif //AVLTREES_NODE_H