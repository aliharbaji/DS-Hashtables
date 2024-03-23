// 
// 234218 Data Structures 1.
// Semester: 2024A (winter).
// Wet Exercise #2.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef OLYMPICSA2_H_
#define OLYMPICSA2_H_

#include "wet2util.h"
#include "Hashtable.h"
#include "Team.h"
#include "STree.h"
#include "Tree.h"



class olympics_t {
private:
	//
	// Here you may add anything you want
	//
    //TODO: I think these are better as smart pointers because in unite we'll probably have to create new HashTable and Tree
    //TODO: if they're pointers we can easily change these fields to point to the newly created datastructures and the old ones
    //TODO: will be destroyed automatically. instead of having to write assignment operator, move, copy, etc...
	Hashtable<Team> teams;
    STree<Team> teamsByStrength;
//    Tree<Team> teamsWithWinsOrStrength; // this holds all the teams sorted by their ID (probably unnecessary)
//    RTree<Team> teamsByRank; // this holds all the teams sorted by their rank


    // rank = median strength of team's players * number of players in the team + numOfWins (highest team by rank)
    int idGenerator;

public:

    // TODO: delete later:
    void printTeam(int teamId){
        auto team = teams.find(teamId);
        if(!team) return;
        team->printTeam();
    }
    // TODO: delete later
    void printTeams(){
        for(int i = 0; i < teams.getCapacity(); i++){
            cout << "Teams at index " << i << ": ";
            cout << *teams[i] << endl;

        }
    }

    void printStrengthTree(int teamId, int strength){
//        auto teamS = teamsByStrength.find(teamId, strength);
//        teamS->printTeam();
    }
	// <DO-NOT-MODIFY> {

    olympics_t();

	virtual ~olympics_t();

    StatusType add_team(int teamId);

    StatusType remove_team(int teamId);

    StatusType add_player(int teamId, int playerStrength);

    StatusType remove_newest_player(int teamId);

    output_t<int> play_match(int teamId1, int teamId2);

    output_t<int> num_wins_for_team(int teamId);

    output_t<int> get_highest_ranked_team();

    StatusType unite_teams(int teamId1, int teamId2);

    output_t<int> play_tournament(int lowPower, int highPower);


	// } </DO-NOT-MODIFY>
};

#endif // OLYMPICSA2_H_
