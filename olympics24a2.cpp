#include "olympics24a2.h"

olympics_t::olympics_t(): teams(), playersByOrder(), playersByStrength(), teamsByWins(), idGenerator(1)
{
    // default constructor
}

olympics_t::~olympics_t()
{
    // default destructor
}


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
StatusType olympics_t::remove_team(int teamId)
{
	if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(!teams.contains(teamId)){
        return StatusType::FAILURE;
    }
    try{
        teams.remove(teamId); // this removes the team from the table, and the team's destructor is called with the destructor of each player
    }catch (exception& e) {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType olympics_t::add_player(int teamId, int playerStrength)
{
    if(teamId <= 0 || playerStrength <= 0){
        return StatusType::INVALID_INPUT;
    }

    // find the team
    auto team = teams.find(teamId);
    // TODO: for the future, I think that we should remove the team, update it and re-add it

    if(team == nullptr){
        return StatusType::FAILURE;
    }

    try{
        team->addPlayer(idGenerator, playerStrength);
        // make a player and add it to the playersByOrder tree
        auto player_ptr = make_shared<Player>(idGenerator, playerStrength);
        playersByOrder.insert(player_ptr);
        playersByStrength.insert(player_ptr);

    }catch(exception& e){
        // if the player could not be added, roll back the changes
        // this does not sit right with me, TODO: check if this is necessary
        team->removePlayer(idGenerator);
        playersByOrder.remove(idGenerator);
        return StatusType::ALLOCATION_ERROR;
    }

    idGenerator++;
	return StatusType::SUCCESS;
}

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
        int playerID = playersByOrder.getMax()->getID(); // O(logk)
        team->removePlayer(playerID); // O(logk)
        auto player = playersByOrder.find(playerID); // O(logk)
        playersByOrder.remove(playerID); // O(logk)
        playersByStrength.remove(playerID, player->getStrength()); // O(logn)
    }catch (exception& e){
        // if the player could not be removed, roll back the changes
        // TODO: check if rolling back the changes is necessary
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

// this runs in O(logn)
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

    int team1Strength = playerStrongerThanHalf1->getStrength() * team1->getNumberOfPlayers();
    int team2Strength = playerStrongerThanHalf2->getStrength() * team2->getNumberOfPlayers();

    if(team1Strength > team2Strength) {
        team1->addWin();
        return output_t<int>(team1->getID());
    }else if(team1Strength < team2Strength){
        team2->addWin();
        return output_t<int>(team2->getID());
    }else{ // in case of a tie, the team with the lower ID wins
        if(team1->getID() < team2->getID()) {
            team1->addWin();
            return output_t<int>(team1->getID());
        }else{
            team2->addWin();
            return output_t<int>(team2->getID());
        }
    }
}

output_t<int> olympics_t::num_wins_for_team(int teamId)
{
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

output_t<int> olympics_t::get_highest_ranked_team()
{
	// TODO: Your code goes here
    return 42;
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
