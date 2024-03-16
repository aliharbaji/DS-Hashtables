//
// Created by omar_ on 16/02/2024.
//

#include "Team.h"
#include <iostream>



//int Team::getMedals() const {
//    return medals;
//}

int Team::getStrength() const {
    return strength;
}


bool Team::addPlayer(int playerID, int playerStrength) {
    shared_ptr<Player> contestant = make_shared<Player>(playerID, playerStrength);
    if(! players.insert(contestant)) return false;
//    strength += playerStrength;
    numberOfPlayers++;
    return true;
}

void Team::removePlayer(int playerID) {
    if(!players.remove(playerID)) return;
    numberOfPlayers--;
}

int Team::getNumberOfPlayers() const {
    return numberOfPlayers;
}


void Team::printTeam() const {
    players.inorderPrint(players.root, cout);
}
