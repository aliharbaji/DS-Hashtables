//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_TEAM_H
#define AVLTREES_TEAM_H


#include "Item.h"
#include "Tree.h"
#include "Player.h"
#include "STree.h"

#include <iostream>

class Team : public Item {
    friend class STree<Team>;

    int strength;
    //TODO: these are also better as pointers to trees imo.
    shared_ptr<Tree<Player>> players;
    shared_ptr<STree<Player>> playersByStrength;
    int numberOfPlayers;
    int numOfWins;
    shared_ptr<Player> strengthPlayer; // this is the player with the median strength

public:
    explicit Team(int teamID)
            : Item(teamID), strength(0), players(make_shared<Tree<Player>>()), numOfWins(0), numberOfPlayers(0),
            strengthPlayer(nullptr), playersByStrength(make_shared<STree<Player>>())
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

    void removeAllPlayers();

    shared_ptr<Player> getNewestPlayer() const;

    unique_ptr<Player[]> getPlayers() const;

    void insert_ptr(shared_ptr<Player> player);

    shared_ptr<Player> findPlayer(int playerID);
};


#endif //AVLTREES_TEAM_H