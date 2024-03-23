//
// Created by omar_ on 23/03/2024.
//

#ifndef WET2_DS_SSNode_H
#define WET2_DS_SSNode_H
//
// Created by allih on 09/02/2024.
//

#include <memory>

using namespace std;
#include "memory"

//I made a different node class for strength tree because we only need the extra/maxRankTeam fields in the strength tree.
// we have no way to upkeep these fields in a tree which doesn't contain these fields.
//basically every node would contain an extra field for the amount of wins just like the vaccines examples
//the numofwins field in team might be redundant because we should be able to calculate the num of wins by the extra field.
template <class T>
class SNode{
private:
    template<typename U> friend class STree;

public:
    shared_ptr<T> data;
    int height;
    int size; //We need to know the size of each subtree for efficiently dividing the tree into subtrees.
    shared_ptr<SNode<T>> left, right;
    shared_ptr<SNode<T>> parent;
    shared_ptr<SNode<T>> maxRankTeam; //contains the maxRankTeam in the node's subtree.
    int extra; //need to upkeep this during insert/removal in strength tree
    //need to upkeep this during insert/removal tree(doesn't hurt complexity of the tree). For the get highest_ranked_team function
    // we would simply return the maxRankTeam at the root node. O(1).

    explicit SNode(shared_ptr<T> data): data(data),  height(0), size(1),
                              left(nullptr), right(nullptr), parent(), maxRankTeam(nullptr), extra(0){}

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
        if(maxRankTeam == nullptr) return 0;
        return maxRankTeam->data->getRank();
    }

};


#endif //WET2_DS_SSNode_H
