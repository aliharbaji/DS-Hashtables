//
// Created by allih on 16/03/2024.
//

#ifndef WET2_DS_PLAYER_H
#define WET2_DS_PLAYER_H

#include "Item.h"


class Player : public Item{
    int strength;
public:
    explicit Player(int playerID, int strength)
            : Item(playerID), strength(strength){}

    Player(const Player&) = default;
    Player& operator=(const Player&)= default;

    int getStrength() const {
        return strength;
    }

    int getRank() const { // added just in case it is probably redundant
        return strength;
    }


};


#endif //WET2_DS_PLAYER_H
