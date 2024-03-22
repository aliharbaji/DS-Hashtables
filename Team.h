//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_TEAM_H
#define AVLTREES_TEAM_H


#include "item.h"
#include "Tree.h"
#include "Player.h"
#include "strengthtree.h"

#include <iostream>

class Team : public Item {
    int strength;
    Tree<Player> players;
    STree<Player> playersByStrength;
    int numberOfPlayers;
    int numberOfWins;
    shared_ptr<Player> strengthPlayer; // this is the player with the median strength

public:
    explicit Team(int teamID)
            : Item(teamID), strength(0), players(), numberOfPlayers(0),
            numberOfWins(0), strengthPlayer(nullptr)
    {}

    Team(const Team&) = delete;
    Team& operator=(const Team&)= delete;

    int getStrength() const;

    bool addPlayer(int playerID, int playerStrength);

    void removePlayer(int playerID);

    int getNumberOfPlayers() const;

    void printTeam() const;

    shared_ptr<Player> getStrengthPlayer();

    void addWin();

    int getNumberOfWins() const;

    int getRank() const;

    void removeAllPlayers();

    shared_ptr<Player> getNewestPlayer() const;

    unique_ptr<Player[]> getPlayers() const;

    void insert_ptr(shared_ptr<Player> player);

    shared_ptr<Player> findPlayer(int playerID);
};


#endif //AVLTREES_TEAM_H