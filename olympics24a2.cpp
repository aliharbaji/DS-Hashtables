#include "olympics24a2.h"
#include <cmath>



//olympics_t::olympics_t(): teams(), teamsWithWinsOrStrength(), idGenerator(1), teamsByRank(), teamsByStrength()
//{
//    // default constructor
//}

olympics_t::olympics_t(): teams(make_shared<Hashtable<Team>>()), teamsByStrength(make_shared<STree<Team>>())
{
    // default constructor
}

olympics_t::~olympics_t() = default;


StatusType olympics_t::add_team(int teamId)
{



    if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if(teams->contains(teamId)){
        return StatusType::FAILURE;
    }

    try{
        teams->insert(teamId);
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
    auto team = teams->find(teamId);
    if(!team){
        return StatusType::FAILURE;
    }

    try{
        // unnecessary I think. Removing the team means the pointers to that team and therefore that team's players are no longer accessible so they're destructed.
        // team->removeAllPlayers(); // this removes all the players from the team in O(k) time complexity
        teams->remove(teamId); // this removes the team from the table, and the team's destructor is called
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
    auto team = teams->find(teamId);


    if(team == nullptr){
        return StatusType::FAILURE;
    }

    try{

        teamsByStrength->remove(teamId, team->getStrength()); // O(logn)
//        team->addPlayer(idGenerator, playerStrength);
        team->addPlayer(playerStrength);
        teamsByStrength->insert(team); // O(logn)

//        idGenerator++;



//        teamsByRank.insert(team); // O(logn)
//        teamsWithWinsOrStrength.insert(team); // O(logn)



    }catch(exception& e){
        // TODO: check if this removes the player for all the trees
//        team->removePlayer(idGenerator);
        team->removePlayer();
        // *****************************


        // *****************************
        return StatusType::ALLOCATION_ERROR;
    }

//    idGenerator++;
	return StatusType::SUCCESS;
}

// TODO: make sure to update the highestRank in case of removal of a player in the highest ranked team
// this should run in O(logn + log(k)) time complexity
StatusType olympics_t::remove_newest_player(int teamId)
{
	if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    auto team = teams->find(teamId); // O(logn)
    if(team == nullptr || team->getSize() == 0){
        return StatusType::FAILURE;
    }

    try{
        teamsByStrength->remove(teamId, team->getStrength()); // O(logn)
        team->removePlayer(); // O(logk) this also updates the strengthPlayer
        teamsByStrength->insert(team); // O(logn)
    }catch (exception& e){
        // if the player could not be removed, roll back the changes
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

// this runs in O(logn)
// TODO: make sure to remove and reinsert the winning team ???
//TODO: addWinsToTeam's implementation already removes and reinserts the team while updating wins.
output_t<int> olympics_t::play_match(int teamId1, int teamId2)
{
    if(teamId1 == teamId2 || teamId1 <= 0 || teamId2 <= 0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    auto team1 = teams->find(teamId1);
    auto team2 = teams->find(teamId2);


    if(team1 == nullptr || team2 == nullptr || team1->getSize() == 0 || team2->getSize() == 0){
        return output_t<int>(StatusType::FAILURE);
    }

    int team1Strength = team1->getStrength();
    int team2Strength = team2->getStrength();

    if(team1Strength > team2Strength) {
        teamsByStrength->addWinsToTeam(teamId1, team1Strength, 1);
        return output_t<int>(teamId1);


    }else if(team1Strength < team2Strength){
        teamsByStrength->addWinsToTeam(teamId2, team2Strength, 1);
        return output_t<int>(teamId2);

    }else{ // in case of a tie, the team with the lower ID wins
        if(teamId1 < teamId2) {
            teamsByStrength->addWinsToTeam(teamId1, team1Strength, 1);
            return output_t<int>(team1->getID());
        }else{
            teamsByStrength->addWinsToTeam(teamId2, team2Strength, 1);
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
    auto team = teams->find(teamId);
    if(team == nullptr){
        return output_t<int>(StatusType::FAILURE);
    }

    //separated to cases based on whether the team has ever had a player added before. If a team never had a player added before then it doesn't exist in the teams str tree.
    //if it ever had a player added then it should exist in the team str tree. An empty team can exist in a strTree(only if we inserted players then removed all of them).
    // and in that case it remembers how many wins it had. Maybe the numOfWin's bug is solved now? Wishful thinking probably.
    int strength = team->getStrength();
    bool exist = teamsByStrength->contains(teamId, strength);
    if (!exist) return output_t<int>(0); //if a team was always empty it can't have wins because it can't play matches while empty.
    else return output_t<int>(teamsByStrength->getTeamWins(teamId, strength));
}

// this should work in O(1) time complexity
output_t<int> olympics_t::get_highest_ranked_team(){
    if(teams->getSize() == 0){
        return output_t<int>(-1);
    }
    return output_t<int>(teamsByStrength->getHighestRank());
}


StatusType olympics_t::unite_teams(int teamId1, int teamId2)
{
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) return StatusType::INVALID_INPUT;
	auto team1 = teams->find(teamId1);
    auto team2 = teams->find(teamId2);

    if (!team1 || !team2) return StatusType::FAILURE;

    if (!team2->getSize()) return StatusType::SUCCESS; //if team2 is empty do nothing.
    remove_team(teamId2);
    //TODO: WE HAVE TO MOVE IDGENERATOR TO TEAM! each team separately manages ids instead of globally. starts at 1 and caps at team's size.
    //After that we don't need to make new players and it simplifies.
    //TODO: just did that, but I don't think it should cap at team's since, because if we add 3 players {1,2,3}
    // and remove player 2 and then add another player we ge this {1,3,3} which contains 3 twice. which could complicate things. correct me if I'm wrong.
    //TODO: you can't remove player 2 because he's not the last one that was added. You always remove the player with id = size.

    try {
        teamsByStrength->remove(teamId1,team1->getStrength());
        team1->uniteWith(team2);
        teamsByStrength->insert(team1);
    }
    catch(bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }


    return StatusType::SUCCESS;
}

output_t<int> olympics_t::play_tournament(int lowPower, int highPower)
{

    if (lowPower <= 0 || highPower <= 0 || lowPower >= highPower) return output_t<int>(StatusType::INVALID_INPUT);
    auto upperTeam = teamsByStrength->findHighestRankedLEStrength(highPower);
    auto lowerTeam = teamsByStrength->findLowestRankedGEStrength(lowPower);

    if (!upperTeam || !lowerTeam) return output_t<int>(StatusType::FAILURE); //no team with less equal highPower or no team with greater equal lowPower
    int upperTeamRank = teamsByStrength->getRank(upperTeam->getID(), upperTeam->getStrength());
    int lowerTeamRank = teamsByStrength->getRank(lowerTeam->getID(), lowerTeam->getStrength());

    if (upperTeamRank < lowerTeamRank || upperTeamRank == -1 || lowerTeamRank == -1) return output_t<int>(StatusType::FAILURE);
    // there is a team with more strength than lowPower but its strength is greater than highPower or such teams don't exist.
    //
    if (upperTeamRank == lowerTeamRank) return output_t<int>(upperTeam->getID());
    int numOfParticipants = upperTeamRank - lowerTeamRank + 1;
    double logResult = log2(numOfParticipants);
    double roundedResult = static_cast<int>(logResult);

    const double epsilon = 1e-6;
    if (std::fabs(logResult - roundedResult) > epsilon) return output_t<int>(StatusType::FAILURE);

    //TODO: should work even with 2 teams but maybe it's still better to just call play match in that scenario for simplicity.
    //log(i) times loop
    while (numOfParticipants >= 2){
        auto lowestRankWinner = teamsByStrength->getKthSmallest(lowerTeamRank + numOfParticipants/2);
        teamsByStrength->addWins(lowestRankWinner->getStrength(), upperTeam->getStrength(), 1);// log(n)
        numOfParticipants /= 2;
    }
    //log(i) * log(n) overall

    return output_t<int>(upperTeam->getID());


}
