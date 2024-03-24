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
    if(!players->insert(contestant) || !playersByStrength->insert(contestant)) return false;
    numberOfPlayers++;

    // TODO I have a feeling that in a case of 1 or 2 players in the team, this will not work as expected,
    // I might be wrong though
    strengthPlayer = playersByStrength->getKthSmallest(numberOfPlayers/2 + 1); // O(logk)
//    cout << "++++++++++++++++++++++++++++++++++++++++++++++++strength is " << strengthPlayer->getStrength() << endl;
    return true;
}

// O(logk)
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
    cout << "Team " << this->getID() << ": ";
    players->inorderPrint(players->root, cout);
    cout << "Strength: " << this->getStrength() << endl;
}

shared_ptr<Player> Team::getStrengthPlayer() {
    if (numberOfPlayers == 0) return nullptr;
    return strengthPlayer;
}

//
//TODO: addWin needs to be a method in Olympics class. Because when you add a win to the team you need to update the extras in STree and maxRankTeam.
//TODO: I will make a method for STree addWin(id, str) --O(logn) which will update the winning team and you can call it from olympics.
//TODO: I will also make a method in the STree getTeamWins(id, str) --O(logn) which will calculate the wins for the team based on the extras.

/*void Team::addWin() {
    numberOfWins++;
}

int Team::getNumberOfWins() const {
    return numberOfWins;
}
// TODO: this has to be changed to work with extras field I think
int Team::getRank() const {
    if (numberOfPlayers == 0) return numberOfPlayers;
    return numberOfWins + this->getStrength();
}
*/

// TODO: ask Omar if this is the right way to remove all players from a team
void Team::removeAllPlayers() {
    players = make_shared<Tree<Player>>();
    playersByStrength = make_shared<PSTree<Player>>();
    numberOfPlayers = 0;
    strengthPlayer = nullptr;
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

void Team::addWin() {
    numOfWins++;
}

// TODO: fix to sum-up extra fields
int Team::getNumberOfWins() const {
    return numOfWins;
}




