//
// Created by allih on 24/03/2024.
//

#ifndef WET2_DS_TEST3_H
#define WET2_DS_TEST3_H

#include "../olympics24a2.h"
int test3(){

    olympics_t olympics2;

    olympics2.add_team(1);
    olympics2.add_team(2);
    olympics2.add_team(3);
    olympics2.add_team(54);
    olympics2.add_team(55);
    olympics2.add_team(6);
    olympics2.add_team(7);
    olympics2.add_team(11);

    //    Team1's player strengths - (1,3,3,5,7,8)
    olympics2.add_player(1, 1); // id 1
    olympics2.add_player(1, 3); // id 2
    olympics2.add_player(1, 3); // id 3
    olympics2.add_player(1, 5); // id 4
    olympics2.add_player(1, 7); // id 5
    olympics2.add_player(1, 8); // id 6


    cout << endl;
    cout << "printing all the hashtable where X at index i means that element i holds no teams" << endl;
    olympics2.printTeams();
    olympics2.remove_team(54);
    cout << endl;
    cout << "removing 54 and printing the table again" << endl;

    olympics2.printTeams();
    cout << endl;
    cout << "Team 1 before removing the newest player: " << endl;
    olympics2.printTeam(1);
    olympics2.remove_newest_player(1);
    cout << "Team 1 after removing the newest player: " << endl;
    olympics2.printTeam(1);

    olympics2.remove_newest_player(3); // this shouldn't do anything

    // Team1's player strengths - (1,3,3,5,7)
    // Team1's strength is 5 * 5 = 25

    olympics2.add_player(2, 2);
    olympics2.add_player(2, 4);
    olympics2.add_player(2, 3);
    olympics2.add_player(2, 6);
    olympics2.add_player(2, 6);
    // Team2's player strengths - (2,3,4,6,6)
    // Team2's strength is 4 * 5 = 20

    olympics2.printTeams();
    cout << "playing match between team 1 and team 2, 2 should win" << endl;
    olympics2.play_match(1, 2);

    cout << "Team1 wins : " << olympics2.num_wins_for_team(1).ans() << endl;
    cout << "Team2 wins : " << olympics2.num_wins_for_team(2).ans() << endl;
    cout << endl;

    cout << "playing match between team 1 and team 1, nothing should change" << endl;
    olympics2.play_match(1, 1);
    cout << "Team1 wins : " << olympics2.num_wins_for_team(1).ans() << endl;
    cout << "Team2 wins : " << olympics2.num_wins_for_team(2).ans() << endl;

    cout << "playing match between team 1 and team 2 again, 2 should win "<< endl;
    olympics2.play_match(1, 2);
    cout << "Team1 wins : " << olympics2.num_wins_for_team(1).ans() << endl;
    cout << "Team2 wins : " << olympics2.num_wins_for_team(2).ans() << endl;

    cout << "removing 2 newest players from team 2" << endl;
    olympics2.remove_newest_player(2);
    olympics2.remove_newest_player(2);
    olympics2.printTeam(2);

    cout << "playing match between team 1 and team 2, 1 should win" << endl;
    olympics2.play_match(1, 2);

    cout << "Team1 wins : " << olympics2.num_wins_for_team(1).ans() << endl;
    cout << "Team2 wins : " << olympics2.num_wins_for_team(2).ans() << endl;

    cout << "********************end of test************************" << endl;
    return 0; // end of test1
}
#endif //WET2_DS_TEST3_H
