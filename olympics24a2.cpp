#include "olympics24a2.h"

//olympics_t::olympics_t(): teams(), teamsWithWinsOrStrength(), idGenerator(1), teamsByRank(), teamsByStrength()
//{
//    // default constructor
//}

olympics_t::olympics_t(): teams(), idGenerator(1), teamsByStrength(make_shared<STree<Team>>())
{
    // default constructor
}

olympics_t::~olympics_t() = default;


StatusType olympics_t::add_team(int teamId)
{

    // TODO: make sure this works in O(1) time complexity

    if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(teams.contains(teamId)){
        return StatusType::FAILURE;
    }

    try{
        teams.insert(teamId);
    }catch(bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

// TODO: make sure this works in O(logn + k) time complexity
// TODO: make sure to update the highestRank in case of removal of the team with the highest rank
StatusType olympics_t::remove_team(int teamId)
{
	if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    auto team = teams.find(teamId);
    if(!team){
        return StatusType::FAILURE;
    }

    try{
        team->removeAllPlayers(); // this removes all the players from the team in O(k) time complexity
        teams.remove(teamId); // this removes the team from the table, and the team's destructor is called
        teamsByStrength->remove(teamId, team->getStrength());

    }catch (exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

//  this works in O(logn + log(k)) time complexity
StatusType olympics_t::add_player(int teamId, int playerStrength)
{
    if(teamId <= 0 || playerStrength <= 0){
        return StatusType::INVALID_INPUT;
    }

    // find the team
    auto team = teams.find(teamId);


    if(team == nullptr){
        return StatusType::FAILURE;
    }

    try{

        teamsByStrength->remove(teamId, team->getStrength()); // O(logn)
        team->addPlayer(idGenerator, playerStrength);
        teamsByStrength->insert(team); // O(logn)

        idGenerator++;



//        teamsByRank.insert(team); // O(logn)
//        teamsWithWinsOrStrength.insert(team); // O(logn)



    }catch(exception& e){
        // TODO: check if this removes the player for all the trees
        team->removePlayer(idGenerator);
        // TODO: ask Omar if it's necessary  to remove the player for teamByStrength and teamByRank
        // *****************************


        // *****************************
        return StatusType::ALLOCATION_ERROR;
    }

    idGenerator++;
	return StatusType::SUCCESS;
}

// TODO: make sure to update the highestRank in case of removal of a player in the highest ranked team
// this should run in O(logn + log(k)) time complexity
StatusType olympics_t::remove_newest_player(int teamId)
{
	if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    auto team = teams.find(teamId); // O(logn)
    if(team == nullptr || team->getNumberOfPlayers() == 0){
        return StatusType::FAILURE;
    }

    try{
        // remove the player from the team and the trees
        int playerID = team->getNewestPlayer()->getID(); // O(1)

        teamsByStrength->remove(teamId, team->getStrength()); // O(logn)

        team->removePlayer(playerID); // O(logk) this also updates the strengthPlayer

        teamsByStrength->insert(team); // O(logn)
    }catch (exception& e){
        // if the player could not be removed, roll back the changes
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

// this runs in O(logn)
// TODO: make sure to remove and reinsert the winning team ???
output_t<int> olympics_t::play_match(int teamId1, int teamId2)
{
    auto team1 = teams.find(teamId1);
    auto team2 = teams.find(teamId2);

    if(team1 == nullptr || team2 == nullptr || team1->getNumberOfPlayers() == 0 || team2->getNumberOfPlayers() == 0){
        return output_t<int>(StatusType::FAILURE);
    }

    if(team1->getID() == team2->getID() || team1->getID() <= 0 || team2->getID() <= 0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    // TODO: this calculation should be maintained in other functions!! I already did that but will keep this TODO just in case
    // fixed it to work in O(1) time complexity
    auto playerStrongerThanHalf1 = team1->getStrengthPlayer();
    auto playerStrongerThanHalf2 = team2->getStrengthPlayer();
//    cout << endl;
//    cout << "Team1's strength player is " << playerStrongerThanHalf1->getStrength() << endl;
//    cout << "Team2's strength player is " << playerStrongerThanHalf2->getStrength() << endl;
    int team1Strength = playerStrongerThanHalf1->getStrength() * team1->getNumberOfPlayers();
    int team2Strength = playerStrongerThanHalf2->getStrength() * team2->getNumberOfPlayers();
//    cout << endl;
//    cout << "Team1's strength is " << team1Strength << endl;
//    cout << "Team2's strength is " << team2Strength << endl;
    if(team1Strength > team2Strength) {
        team1->addWin();
//        if(team1->getNumberOfWins() == 1){
//            teamsWithWinsOrStrength.insert(team1); // O(logn)
//        }
        return output_t<int>(team1->getID());
    }else if(team1Strength < team2Strength){
        team2->addWin();
//        if(team2->getNumberOfWins() == 1){
//            teamsWithWinsOrStrength.insert(team2); // O(logn)
//        }
        return output_t<int>(team2->getID());
    }else{ // in case of a tie, the team with the lower ID wins
        if(team1->getID() < team2->getID()) {
            team1->addWin();
//            if(team1->getNumberOfWins() == 1){
//                teamsWithWinsOrStrength.insert(team1); // O(logn)
//            }
            return output_t<int>(team1->getID());
        }else{
            team2->addWin();
//            if(team2->getNumberOfWins() == 1){
//                teamsWithWinsOrStrength.insert(team2); // O(logn)
//            }
            return output_t<int>(team2->getID());
        }
    }
}

// this works in O(logn) (should also sum up the extra fields)
output_t<int> olympics_t::num_wins_for_team(int teamId)
{
    if(teamId <= 0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    auto team = teams.find(teamId);
    if(team == nullptr){
        return output_t<int>(StatusType::FAILURE);
    }

    return output_t<int>(team->getNumberOfWins());
}

// this should work in O(1) time complexity
output_t<int> olympics_t::get_highest_ranked_team(){
    if(teams.getSize() == 0){
        return output_t<int>(-1);
    }

    int highestRank = teamsByStrength->getHighestRank(); // O(1)

    return output_t<int>(highestRank);
}


StatusType olympics_t::unite_teams(int teamId1, int teamId2)
{
	// TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> olympics_t::play_tournament(int lowPower, int highPower)
{
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}
