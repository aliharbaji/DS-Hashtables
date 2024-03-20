#include "Hashtable.h"
#include <iostream>
#include "Team.h"
#include "Player.h"
#include "olympics24a2.h"

using namespace std;

int main()
{

    olympics_t olympics2;

    olympics2.add_team(1);
    olympics2.add_team(2);
    olympics2.add_team(3);
    olympics2.add_team(4);
    olympics2.add_team(5);
    olympics2.add_team(6);
    olympics2.add_team(7);

    //    Team1's player strengths - (1,3,3,5,7,8)
    olympics2.add_player(1, 1);
    olympics2.add_player(1, 3);
    olympics2.add_player(1, 3);
    olympics2.add_player(1, 5);
    olympics2.add_player(1, 7);
    olympics2.add_player(1, 8);


    olympics2.printTeams();
    return 0;
    Hashtable<Team> h;
//    cout << h[0].getNumberOfPlayers() << endl;
    Player p1(1, 1);
    Team t1(1);

    STree<Player> sTree;
    // make a player with strength 10
    Player p2(1, 1);
    // make a player with strength 20
    Player p3(3, 3);
    // make a player with strength 30
    Player p4(4, 3);
    // make a player with strength 40
    Player p5(5, 5);
    // make a player with strength 100
    Player p6(6, 7);
    // make a player with strength 5
    Player p7(7, 8);
    // make a player with strength 2
    Player p8(8, 2);
    // make a player with strength 3
    Player p9(9, 3);

//    (1,3,3,5,7,8)

//    auto p1_ptr = shared_ptr<Player>(new Player(p1));
    auto p2_ptr = shared_ptr<Player>(new Player(p2));
    auto p3_ptr = shared_ptr<Player>(new Player(p3));
    auto p4_ptr = shared_ptr<Player>(new Player(p4));
    auto p5_ptr = shared_ptr<Player>(new Player(p5));
    auto p6_ptr = shared_ptr<Player>(new Player(p6));
    auto p7_ptr = shared_ptr<Player>(new Player(p7));
//    auto p8_ptr = shared_ptr<Player>(new Player(p8));
//    auto p9_ptr = shared_ptr<Player>(new Player(p9));
//    sTree.insert(p1_ptr);
    sTree.insert(p2_ptr);
    sTree.insert(p3_ptr);
    sTree.insert(p4_ptr);
    sTree.insert(p5_ptr);
    sTree.insert(p6_ptr);
    sTree.insert(p7_ptr);
//    sTree.insert(p8_ptr);
//    sTree.insert(p9_ptr);
    sTree.printTree();
//    cout << sTree.isBalanced() << endl;
    cout << "median strength player in team with strengths (1, 3, 3, 5, 7, 8) is " << sTree.getKthSmallest(sTree.getSize() / 2 + 1)->getStrength() << endl;
    cout << "********************************************" << endl;

    STree<Player> s2;
    // make players pointers with strengths (2,4,3,6,6)
    auto p10_ptr = shared_ptr<Player>(new Player(10, 2));
    auto p11_ptr = shared_ptr<Player>(new Player(11, 4));
    auto p12_ptr = shared_ptr<Player>(new Player(12, 3));
    auto p13_ptr = shared_ptr<Player>(new Player(13, 6));
    auto p14_ptr = shared_ptr<Player>(new Player(14, 6));
    s2.insert(p10_ptr);
    s2.insert(p11_ptr);
    s2.insert(p12_ptr);
    s2.insert(p13_ptr);
    s2.insert(p14_ptr);
    s2.printTree();
    cout << "median strength player in team with strengths (2, 4, 3, 3, 6) is " << s2.getKthSmallest(sTree.getSize() / 2 + 1)->getStrength() << endl;
    cout << "the median strength should be 4 in team (2, 3, 3, 4, 6)" << endl;
    cout << "this seems to be a logic error regarding the median strength of a team with players of same strength" << endl;
    cout << "looks like we're going to change the way we calculate the rank of"
            "each node or maybe add a strength tree with no duplications?"  << endl;
    cout << "will work on this later" << endl;
    cout << "********************************************" << endl;
    return 0;
    cout << "********************************************" << endl;
    cout << "TEST FOR HASHTABLE" << endl;
    t1.addPlayer(1, 1);
    t1.addPlayer(2, 2);
    t1.addPlayer(3, 3);
    t1.addPlayer(4, 4);

    t1.printTeam();

    cout << endl;
    cout << "********************************************" << endl;
    cout << "p1 strength: " << p1.getStrength() << endl;
    h.insert(1);
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
