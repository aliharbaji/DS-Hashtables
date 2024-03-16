//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_TEAM_H
#define AVLTREES_TEAM_H


#include "item.h"
#include "tree.h"


#include <iostream>

class Contestant;
class Country;


class Team : public Item {
    int strength;
public:
    explicit Team(int teamID)
            : Item(teamID), strength(0)
    {}

    Team(const Team&) = delete;
    Team& operator=(const Team&)= delete;

    int getStrength() const;
};


#endif //AVLTREES_TEAM_H