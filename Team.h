//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_TEAM_H
#define AVLTREES_TEAM_H


#include "item.h"
#include "Tree.h"
#include "Player.h"

#include <iostream>

class Team : public Item {
    int strength;
    Tree<Player> players;
    int numberOfPlayers;
    int numberOfWins;
public:
    explicit Team(int teamID)
            : Item(teamID), strength(0), players(), numberOfPlayers(0), numberOfWins(0)
    {}

    Team(const Team&) = delete;
    Team& operator=(const Team&)= delete;

    int getStrength() const;

    bool addPlayer(int playerID, int playerStrength);

    void removePlayer(int playerID);

    int getNumberOfPlayers() const;

    void printTeam() const ;
};


#endif //AVLTREES_TEAM_H