#include "Hashtable.h"
#include <iostream>
#include "Team.h"
#include "Player.h"

using namespace std;

int main()
{
    Hashtable<Team> h;
    Player p1(1, 1);
    Team t1(1);

    t1.addPlayer(1, 1);
    t1.addPlayer(2, 2);
    t1.addPlayer(3, 3);
    t1.addPlayer(4, 4);

    t1.printTeam();

    cout << endl;
    cout << "********************************************" << endl;
    cout << "p1 strength: " << p1.getStrength() << endl;
    h.insert(0);
    h.insert(22);
    h.insert(33);

    h.insert(32);
    h.insert(42);
    h.insert(52);
    h.insert(62);
    h.insert(72);
    h.insert(82);
    h.insert(92);
    h.insert(102);
    h.insert(112);


    h.printHashTable();
    cout << endl;

    cout << "removing 0" << endl;
    h.remove(0);

    h.printHashTable();
    cout << endl;

    cout << "removing 72" << endl;
    h.remove(72);

    h.printHashTable();
    cout << endl;

//    h.resizeUp();
//
//    h.getCapacity();
//
//    h.printHashTable();
//    cout << endl;

//    h.remove(82);
//    h.remove(72);
//    h.remove(62);
//    h.getSize();
//
//    cout << "this gives out an infinite loop because of the hash function we are using."
//            " We are using a mod capacity hash function" << endl;
//    cout << "index of 10: " << h.indexOf(10) << endl;
//    cout << "index of 22: " << h.indexOf(22) << endl;
//    cout << "index of 32: " << h.indexOf(32) << endl;
//    cout << "index of 42: " << h.indexOf(42) << endl;

    return 0;
}
