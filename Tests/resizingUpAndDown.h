//
// Created by allih on 24/03/2024.
//

#ifndef TESTS_RESIZINGUPANDDOWN_H
#define TESTS_RESIZINGUPANDDOWN_H

#include "../olympics24a2.h"

#include <iostream>
using namespace std;

int testResizingUpAndDown() {
    olympics_t olympics69;
    olympics69.add_team(1);
    olympics69.add_team(12);
    olympics69.add_team(23);
    olympics69.add_team(4);
    olympics69.add_team(5);
    olympics69.add_team(6);
    olympics69.add_team(7);
    olympics69.add_team(8);
    olympics69.add_team(9);
    cout << "BEFORE RESIZING UP" << endl;
    olympics69.printTeams();

    olympics69.add_team(10);
    cout << "AFTER RESIZING UP" << endl;
    olympics69.printTeams();

    cout << endl;
    cout << "removing 10" << endl;
    olympics69.remove_team(10);
    cout << "removing 9" << endl;
    olympics69.remove_team(9);
    cout << "removing 8" << endl;
    olympics69.remove_team(8);
    cout << "removing 7" << endl;
    olympics69.remove_team(7);
    cout << "removing 6" << endl;
    olympics69.remove_team(6);
    cout << "removing 5" << endl;
    olympics69.remove_team(5);

    cout << "AFTER RESIZING DOWN" << endl;
    olympics69.printTeams();
    return 0;
}


#endif //WET2_DS_RESIZINGUPANDDOWN_H
