#ifndef TESTS_TEST2_H
#define TESTS_TEST2_H

#include "../olympics24a2.h"

#include <iostream>
using namespace std;

int test2() {
    olympics_t olympics;

    cout << "highest ranked team's rank should be -1: " << olympics.get_highest_ranked_team().ans() << endl;
    olympics.add_team(11);
    cout << "highest ranked team's rank should be 0: " << olympics.get_highest_ranked_team().ans() << endl;
    olympics.add_team(22);
    olympics.add_team(31);

    olympics.add_team(69);
    olympics.add_team(420);



    // spamming add_team till the load factor is greater than 2.5
    olympics.add_team(1);
    olympics.add_team(2);
    olympics.add_team(3);

    cout << "before resizing the table" << endl;
    olympics.printTeams();


    olympics.add_team(4);
    cout << endl;

    cout << "after resizing the table" << endl;
    olympics.printTeams();

    olympics.add_team(5);


    cout << "after resizing down the table" << endl;
    olympics.remove_team(5);
    olympics.remove_team(4);
    olympics.remove_team(3);
    olympics.remove_team(2);
    olympics.remove_team(1);


    olympics.printTeams();

//    olympics.add_team(6);
//    olympics.add_team(7);
//    olympics.add_team(8);
//    olympics.add_team(9);
//    olympics.add_team(10);
//    olympics.add_team(11);
//    olympics.add_team(12);
//    olympics.add_team(13);

    //

    cout << endl;
    olympics.remove_team(11111111);

    cout << endl << endl;
    cout << "adding players to the teams" << endl;
    // team 69 and 420 should have the strengths 30 and 20 respectively according to what the
    // staff wrote in the description of play_match
    olympics.add_player(69, 1);
    olympics.add_player(69, 3);
    olympics.add_player(69, 3);
    olympics.add_player(69, 5);
    olympics.add_player(69, 7);
    olympics.add_player(69, 8);

    olympics.add_player(420, 2);
    olympics.add_player(420, 4);
    olympics.add_player(420, 3);
    olympics.add_player(420, 6);
    olympics.add_player(420, 6);



    olympics.add_player(11, 11);
    olympics.add_player(11, 33);
    olympics.add_player(11, 33);

    olympics.add_player(22, 22);
    olympics.add_player(22, 44);
    olympics.add_player(22, 66);

    olympics.add_player(31, 31);
    olympics.add_player(31, 31);

    olympics.printTeams();
    cout << endl;

    cout << "adding team 77" << endl;
    olympics.add_team(77);
    cout << "adding team 88" << endl;
    olympics.add_team(88);
    cout << "adding team 99" << endl;
    olympics.add_team(99);
    cout << "adding team 100" << endl;
    olympics.add_team(100);
    cout << "adding team 101" << endl;

    cout << "PRINTING TEAMS AFTER REHASH" << endl;
    olympics.printTeams();


    cout << "printing all the teams" << endl;
    olympics.printTeam(11);

    olympics.printTeam(22);

    olympics.printTeam(31);

    olympics.printTeam(69);

    olympics.printTeam(420);
    cout << "***************************************" << endl;

    cout << "removing 2 newest players from team 420" << endl;
    olympics.remove_newest_player(420);
    olympics.remove_newest_player(420);
    olympics.printTeam(420);

    cout << endl;
    cout << "playing match between team 69 and team 420, 69 should win:" << endl;
    olympics.play_match(69, 420);

    cout << "Team69 now has : " << olympics.num_wins_for_team(69).ans() << " wins." << endl;
    cout << "Team420 now has : " << olympics.num_wins_for_team(420).ans() << " wins." << endl;
    cout << endl;
    cout << endl;

    // TODO: Omar, check if this test is working after you've done your changes
    cout << "********************After Omar finishes his changes to SNode, this should work properly************************" << endl;
    cout << "This test is failing... (look at the last few lines when removing team 420 from the olympics, "
            "the new highest ranked team should be updated and should definitely should have an ID that is not 420)" << endl;
    cout << "we are probably not updating the teamsByRank tree correctly in play_match and add_player" << endl;
    cout << "highest ranked team's rank is (which is incorrect) : " << olympics.get_highest_ranked_team().ans() << endl;
    cout << "removing the newest player from team 22" << endl;
    olympics.remove_newest_player(22);
    cout << "highest ranked team's rank is: " << olympics.get_highest_ranked_team().ans() << endl;
    cout << "removing the newest player from team 22 again" << endl;
    olympics.remove_newest_player(22);
    cout << "highest ranked team's rank is: " << olympics.get_highest_ranked_team().ans() << endl;

    cout << "removing the newest player from team 11" << endl;
    olympics.remove_newest_player(11);
    cout << "highest ranked team's rank is: " << olympics.get_highest_ranked_team().ans() << endl;
    cout << "removing the newest player from team 11 again" << endl;
    olympics.remove_newest_player(11);
    cout << "highest ranked team's rank is: " << olympics.get_highest_ranked_team().ans() << endl;

    cout << "removing the newest player from team 22 again" << endl;
    olympics.remove_newest_player(22);
    cout << "highest ranked team's rank is: " << olympics.get_highest_ranked_team().ans() << endl;

    cout << "removing the newest player from team 31" << endl;
    olympics.remove_newest_player(31);
    cout << "highest ranked team's rank is: " << olympics.get_highest_ranked_team().ans() << endl;

    cout << "removing the newest player from team 31" << endl;
    olympics.remove_newest_player(31);
    cout << "highest ranked team's rank is: " << olympics.get_highest_ranked_team().ans() << endl;

    cout << "removing the newest player from team 69" << endl;
    olympics.remove_newest_player(69);
    cout << "highest ranked team's rank is: " << olympics.get_highest_ranked_team().ans() << endl;
    cout << endl;
    cout << "everything seems to be working fine up until this point..." << endl;
    cout << "*************removing team 420" << endl;
    olympics.remove_team(420);

    cout << "*************highest ranked team's rank is: " << olympics.get_highest_ranked_team().ans() << endl;
    cout << "but we just removed team 420, so the highest ranked team should be team 69 probably" << endl;

    return 0;
}


#endif //TESTS_TEST2_H