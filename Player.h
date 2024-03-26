//
// Created by allih on 16/03/2024.
//

#ifndef WET2_DS_PLAYER_H
#define WET2_DS_PLAYER_H

#include "Item.h"


class Player {
    friend class Team;
    int strength;
    unsigned long long id;
public:
    explicit Player(unsigned long long id, int strength)
            : id(id), strength(strength){}

    Player(const Player&) = default;
    Player& operator=(const Player&)= default;

    int getStrength() const {
        return strength;
    }

    int getRank() const { // added just in case it is probably redundant
        return strength;
    }

    unsigned long long getID() const{
        return id;
    }


};


#endif //WET2_DS_PLAYER_H
