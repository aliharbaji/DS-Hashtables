//
// Created by omar_ on 16/02/2024.
//

#include "Team.h"
#include <iostream>



//int Team::getMedals() const {
//    return medals;
//}

int Team::getStrength() const {
    if(numberOfPlayers == 0) return 0;
    return strengthPlayer->getStrength() * numberOfPlayers;
}


bool Team::addPlayer(int playerID, int playerStrength) {
    shared_ptr<Player> contestant = make_shared<Player>(playerID, playerStrength);
    if(! players->insert(contestant) || !playersByStrength->insert(contestant)) return false;
    numberOfPlayers++;

    // TODO I have a feeling that in a case of 1 or 2 players in the team, this will not work as expected,
    // I might be wrong though
    strengthPlayer = playersByStrength->getKthSmallest(numberOfPlayers/2 + 1); // O(logk)
//    cout << "strength is " << strengthPlayer->getStrength() << endl;
    return true;
}

// logk
void Team::removePlayer(int playerID) {
    auto player = players->find(playerID);
    if(player == nullptr) return;
    if(!players->remove(playerID) || !playersByStrength->remove(playerID, player->getStrength())) return;
    numberOfPlayers--;
    // find strength player again
    if(numberOfPlayers == 0){
        strengthPlayer = nullptr;
        return;
    }
    strengthPlayer = playersByStrength->getKthSmallest(numberOfPlayers/2 + 1); // O(logk)
}

int Team::getNumberOfPlayers() const {
    return numberOfPlayers;
}


void Team::printTeam() const {
    players->inorderPrint(players->root, cout);
}

shared_ptr<Player> Team::getStrengthPlayer() {
    if (numberOfPlayers == 0) return nullptr;
    return strengthPlayer;
}

void Team::addWin() {
    numberOfWins++;
}

int Team::getNumberOfWins() const {
    return numberOfWins;
}

int Team::getRank() const {
    if (numberOfPlayers == 0) return numberOfPlayers;
    return numberOfWins + this->getStrength();
}


// TODO: ask Omar if this is the right way to remove all players from a team
void Team::removeAllPlayers() {
    //
    players = make_shared<Tree<Player>>();
    playersByStrength = make_shared<STree<Player>>();
    numberOfPlayers = 0;
    strengthPlayer = nullptr;
    numberOfWins = 0;
}

shared_ptr<Player> Team::getNewestPlayer() const {
    auto player = players->getMax();
    return player;
}

void Team::insert_ptr(shared_ptr<Player> player) {
    players->insert(player);
    playersByStrength->insert(player);
    numberOfPlayers++;
    strengthPlayer = playersByStrength->getKthSmallest(numberOfPlayers/2 + 1);
}

shared_ptr<Player> Team::findPlayer(int playerID) {
    return players->find(playerID);
}




