//
// Created by omar_ on 16/02/2024.
//

#include "Team.h"
#include <iostream>



//int Team::getMedals() const {
//    return medals;
//}

int Team::getStrength() const {
    return strengthPlayer->getStrength() * numberOfPlayers;
}


bool Team::addPlayer(int playerID, int playerStrength) {
    shared_ptr<Player> contestant = make_shared<Player>(playerID, playerStrength);
    if(! players.insert(contestant) || !playersByStrength.insert(contestant)) return false;
    numberOfPlayers++;

    // TODO I have a feeling that in a case of 1 or 2 players in the team, this will not work as expected,
    // I might be wrong though
    strengthPlayer = playersByStrength.getKthSmallest(numberOfPlayers/2 + 1); // O(logk)
//    cout << "strength is " << strengthPlayer->getStrength() << endl;
    return true;
}

void Team::removePlayer(int playerID) {
    auto player = players.find(playerID);
    if(player == nullptr) return;
    if(!players.remove(playerID) || !playersByStrength.remove(playerID, player->getStrength())) return;
    numberOfPlayers--;
}

int Team::getNumberOfPlayers() const {
    return numberOfPlayers;
}


void Team::printTeam() const {
    players.inorderPrint(players.root, cout);
}

shared_ptr<Player> Team::getStrengthPlayer() {
    return strengthPlayer;
}

void Team::addWin() {
    numberOfWins++;
}

int Team::getNumberOfWins() const {
    return numberOfWins;
}

int Team::getRank() const {
    return numberOfWins + this->getStrength();
}



