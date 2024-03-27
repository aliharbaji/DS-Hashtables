//
// Created by omar_ on 16/02/2024.
//

#include "Team.h"
#include <iostream>



//int Team::getMedals() const {
//    return medals;
//}

int Team::getStrength() const {
    if(!strengthPlayer || players->getSize() == 0) return 0;
    return strengthPlayer->getStrength() * numberOfPlayers;
}

//TODO: should change it so that team doesn't take playerID as a parameter but generates playerID based on numberOfPlayers.

bool Team::addPlayer(int playerStrength) {
    shared_ptr<Player> contestant = make_shared<Player>(++numberOfPlayers, playerStrength);
    if(!players->insert(contestant) || !playersByStrength->insert(contestant)) return false;


    strengthPlayer = playersByStrength->getKthSmallest(numberOfPlayers/2 + 1); // O(logk)
    return true;
}


// O(logk)
void Team::removePlayer() {
    auto playerID = players->getMax()->getID();
    auto playerStrength = players->getMax()->getStrength();
    if(!players->remove(playerID) || !playersByStrength->remove(playerID, playerStrength)) return;
    numberOfPlayers--;
    // find strength player again
    if(numberOfPlayers == 0){
        strengthPlayer = nullptr;
        return;
    }
    strengthPlayer = playersByStrength->getKthSmallest(numberOfPlayers/2 + 1); // O(logk)
}

int Team::getSize() const {
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

void Team::insert_ptr(const shared_ptr<Player>& player) {
    players->insert(player);
    playersByStrength->insert(player);
    numberOfPlayers++;
    strengthPlayer = playersByStrength->getKthSmallest(numberOfPlayers/2 + 1);
}

shared_ptr<Player> Team::findPlayer(int playerID) {
    return players->find(playerID);
}

// you can delete this method I was testing something

// TODO: the usage of these function needs to be done through STree in the Olympics method. The STree has a method which does this while updating the extras.
/*
void Team::addWin() {
    numOfWins++;
}

// TODO: fix to sum-up extra fields
int Team::getNumberOfWins() const {
    return numOfWins;
}
*/

shared_ptr<Player>* Team::returnedSortedArrayOfElementsByStrength(){
    return playersByStrength->returnSortedArrayOfElements();
}

shared_ptr<Player>* Team::returnedSortedArrayOfElementsByID(){
    return players->returnSortedArrayOfElements();
}

void Team::uniteWith(shared_ptr<Team> team2){
    int team1Size = numberOfPlayers;
    int team2Size = team2->getSize();
    int newSize = team2Size + team1Size;

    auto team2Arr = team2->returnedSortedArrayOfElementsByID();
    auto team1Arr = returnedSortedArrayOfElementsByID();
    auto mergedArr = new shared_ptr<Player>[team1Size + team2Size];
    auto team2StrArr = team2->returnedSortedArrayOfElementsByStrength();
    auto team1StrArr = returnedSortedArrayOfElementsByStrength();
    auto mergedStrArr = new shared_ptr<Player>[team1Size + team2Size];


    for (unsigned long long i = 0; i < team1Size; i++){
        mergedArr[i] = team1Arr[i];
    }

    for (unsigned long long i = 0; i < team2Size; i++){
        team2Arr[i]->id = team1Size + i + 1;
        mergedArr[team1Size + i] = team2Arr[i];
    }





    int i = 0, j = 0, k = 0;


    while (i < team1Size && j < team2Size) {
        if (team1StrArr[i]->getStrength() <= team2StrArr[j]->getStrength()) {
            mergedStrArr[k++] = team1StrArr[i++];
        } else {
            mergedStrArr[k++] = team2StrArr[j++];
        }
    }
    while (i < team1Size) {
        mergedStrArr[k++] = team1StrArr[i++];
    }
    while (j < team2Size) {
        mergedStrArr[k++] = team2StrArr[j++];
    }

    numberOfPlayers += team2Size;

    players = make_shared<Tree<Player>>(mergedArr, numberOfPlayers);
    playersByStrength = make_shared<PSTree<Player>>(mergedStrArr, numberOfPlayers);

    strengthPlayer = playersByStrength->getKthSmallest(numberOfPlayers/2 + 1);

    delete[] team1Arr;
    delete[] team2Arr;
    delete[] team1StrArr;
    delete[] team2StrArr;
    delete[] mergedArr;
    delete[] mergedStrArr;

}



