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
#include "strengthtree.h"
#include "Tree.h"

class olympics_t {
private:
	//
	// Here you may add anything you want
	//
	Hashtable<Team> teams;

    // redundant trees
//    Tree<Player> playersByOrder; // this tree will be used to remove the newest player
//    STree<Player> playersByStrength;


    Tree<Team> teamsWithWinsOrStrength; // this holds all the teams sorted by their ID
    STree<Team> teamsByStrength;
    STree<Team> teamsByRank; // maybe this is the way to go I am still not sure (set the field STree::strength to be the rank of the tree)
    // TODO: I am certain that teamsByRank does not work as expected, I need to fix it

    // rank = median strength of team's players * number of players in the team + numOfWins (highest team by rank)
    int idGenerator;

public:

    // TODO: delete later:
    void printTeam(int teamId){
        auto team = teams.find(teamId);
        team->printTeam();
    }
    // TODO: delete later
    void printTeams(){
        for(int i = 0; i < teams.getCapacity(); i++){
            cout << "Teams at index " << i << ": ";
            cout << teams[i] << endl;

        }
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
