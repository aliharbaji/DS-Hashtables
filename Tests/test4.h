//
// Created by allih on 25/03/2024.
//

#ifndef WET2_DS_TEST4_H
#define WET2_DS_TEST4_H
#include "../olympics24a2.h"

void test4(){
    olympics_t oly;
    oly.add_team(1);
    oly.add_team(2);

    oly.play_match(1, 2);

//    cout << "team 1 rank: " << oly.get_team_rank(1).ans() << endl;
//    cout << "team 2 rank: " << oly.get_team_rank(2).ans() << endl;

    cout << "team 1 wins: " << oly.num_wins_for_team(1).ans() << endl;
    cout << "team 2 wins: " << oly.num_wins_for_team(1).ans() << endl;
}
#endif //WET2_DS_TEST4_H
