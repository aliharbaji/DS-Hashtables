#include "Hashtable.h"
#include <iostream>
#include "Team.h"
#include "Player.h"
#include "olympics24a2.h"

// include tests
#include "Tests/resizingUpAndDown.h"
#include "Tests/test2.h"
#include "Tests/test3.h"

using namespace std;

int main() {
    cout << "Testing the olympics_t class (uncomment the test you want to see)" << endl;
    // TEST1 (a test for resizing up and down) PASS
    testResizingUpAndDown();

    // TEST2 this is a big test but I tried to keep it commented as much as possible, it works properly up until the stars *** appear
//    test2();

    // TEST3 (a small test for playing matches and removing players) PASS
//    test3();

    return 0;
}

