//
// Created by allih on 14/02/2024.
//

#ifndef AVLTREES_ITEM_H
#define AVLTREES_ITEM_H

#include "node.h"
#include "Tree.h"

class Item {
    unsigned long long ID;
public:
    explicit Item(int ID) : ID(ID) {}

    int getID() const {
        return ID;
    }
    friend class Tree<Item>;
    virtual ~Item() = default;
};



#endif //AVLTREES_ITEM_H
