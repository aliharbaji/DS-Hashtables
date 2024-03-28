//
// Created by allih on 16/03/2024.
//

#ifndef WET2_DS_PLAYER_H
#define WET2_DS_PLAYER_H

#include "Item.h"


class Player {
    friend class Team;
    int id;
    int strength;
public:
    explicit Player(int id, int strength)
            : id(id), strength(strength){}

    Player(const Player&) = default;
    Player& operator=(const Player&)= default;

    int getStrength() const {
        return strength;
    }

    int getRank() const { // added just in case it is probably redundant
        return strength;
    }

    int getID() const{
        return id;
    }


};


#endif //WET2_DS_PLAYER_H
