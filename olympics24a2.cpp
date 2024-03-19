#include "olympics24a2.h"

olympics_t::olympics_t()
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

StatusType olympics_t::remove_team(int teamId)
{
	if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(!teams.contains(teamId)){
        return StatusType::FAILURE;
    }
    try{
        teams.remove(teamId);
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
    auto team = teams.find(teamId);
    if(team == nullptr || team->getNumberOfPlayers() == 0){
        return StatusType::FAILURE;
    }

    try{
        // remove the player from the team and the trees
        int playerID = playersByOrder.getMax()->getID();
        team->removePlayer(playerID);
        playersByOrder.remove(playerID);
        auto player = playersByOrder.find(playerID);
        playersByStrength.remove(playerID, player->getStrength());
    }catch (exception& e){
        // if the player could not be removed, roll back the changes
        // TODO: check if this is necessary
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

output_t<int> olympics_t::play_match(int teamId1, int teamId2)
{
    // TODO: Your code goes here
    return 2008;
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
