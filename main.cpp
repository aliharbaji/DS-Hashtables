#include "Hashtable.h"
#include <iostream>
#include "Team.h"
#include "Player.h"
#include "olympics24a2.h"

// include tests
#include "Tests/resizingUpAndDown.h"
#include "Tests/test2.h"
#include "Tests/test3.h"
#include "Tests/test4.h"
using namespace std;

int main() {
    cout << "Testing the olympics_t class (set x to the test number you want to run)" << endl << endl;
    int x = 0;

    switch (3) {
        case 0: // ALL TESTS
            testResizingUpAndDown();
            test2();
            test3();
            test4();
            break;
        case 1: // TEST1 (a test for resizing up and down) PASS
            testResizingUpAndDown();
            break;
        case 2: // TEST2 this is a big test but I tried to keep it commented as much as possible, it works properly up until the stars *** appear
            test2();
            break;
        case 3: // TEST3 (a small test for playing matches and removing players) PASS
            test3();
            break;
        case 4: // TEST4 (empty teams) PASS
            test4();
            break;
        default:
            break;
    }



    return 0;
}

