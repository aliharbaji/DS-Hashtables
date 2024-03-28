//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_TEAM_H
#define AVLTREES_TEAM_H


#include "Item.h"
#include "Tree.h"
#include "Player.h"
#include "STree.h"
#include "PSTree.h"
#include <iostream>

class Team : public Item {
    friend class STree<Team>;
    friend class PSTree<Player>;


    shared_ptr<Tree<Player>> players;
    shared_ptr<PSTree<Player>> playersByStrength;
    int numberOfPlayers;
    int numOfWins;
    shared_ptr<Player> strengthPlayer; // this is the player with the median strength

public:
    explicit Team(int teamID)
            : Item(teamID), players(make_shared<Tree<Player>>()), playersByStrength(make_shared<PSTree<Player>>()),
            numberOfPlayers(0), numOfWins(0), strengthPlayer(nullptr)
    {}

    Team(const Team&) = delete;
    Team& operator=(const Team&)= delete;

    int getStrength() const;

    bool addPlayer(int playerID, int playerStrength);

    bool addPlayer(int playerStrength);

    void removePlayer();

    int getSize() const;

    void printTeam() const;

    shared_ptr<Player> getStrengthPlayer();

    shared_ptr<Player>* returnedSortedArrayOfElementsByStrength();

    shared_ptr<Player>* returnedSortedArrayOfElementsByID();

    void addWinAli();
    /*
    void addWin();

    int getNumberOfWins() const;
    */
    void removeAllPlayers();

    shared_ptr<Player> getNewestPlayer() const;

//    unique_ptr<Player[]> getPlayers() const;

    void insert_ptr(const shared_ptr<Player>& player);

    shared_ptr<Player> findPlayer(int playerID);

    void uniteWith(shared_ptr<Team> other);


};


#endif //AVLTREES_TEAM_H