#include "Hashtable.h"
#include <iostream>
#include "Team.h"
#include "Player.h"
#include "olympics24a2.h"

using namespace std;

int main()
{
    cout << "Just remember to resize and rehash the table when needed + check TODO" << endl;
    cout << "We also still need to add an extra field in the Trees' nodes, for play_tournament" << endl;
    cout << "We should also make sure that the way we are calculating the strength of each team is correct,"
            " I have a feeling that it is not" << endl;
    cout << "Testing the olympics_t class" << endl;

    olympics_t olympics;

    cout << "highest ranked team's rank should be -1: " << olympics.get_highest_ranked_team().ans() << endl;
    olympics.add_team(11);
    cout << "highest ranked team's rank should be 0: " << olympics.get_highest_ranked_team().ans() << endl;
    olympics.add_team(22);
    olympics.add_team(31);

    olympics.add_team(69);
    olympics.add_team(420);

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

//    olympics.printTeams();

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


    cout << "Team11: ";
    olympics.printTeam(11);
    cout << endl;
    cout << "Team22: ";
    olympics.printTeam(22);
    cout << endl;
    cout << "Team31: ";
    olympics.printTeam(31);
    cout << endl;
    cout << "Team69: ";
    olympics.printTeam(69);
    cout << endl;
    cout << "Team420: ";
    olympics.printTeam(420);
    cout << endl;

    cout << endl;
    cout << "playing match between team 69 and team 420, 69 should win:" << endl;
    olympics.play_match(69, 420);

    cout << "Team69 now has : " << olympics.num_wins_for_team(69).ans() << " wins." << endl;
    cout << "Team420 now has : " << olympics.num_wins_for_team(420).ans() << " wins." << endl;
    cout << endl;
    cout << endl;

    cout << "********************************************" << endl;
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


    cout << "playing match between team 1 and team 2, 1 should win" << endl;
    olympics2.play_match(1, 2);

    cout << "Team1 wins : " << olympics2.num_wins_for_team(1).ans() << endl;
    cout << "Team2 wins : " << olympics2.num_wins_for_team(2).ans() << endl;
    cout << endl;
    cout << "playing match between team 1 and team 2 again, nothing should change" << endl;
    olympics2.play_match(1, 1);
    cout << "Team1 wins : " << olympics2.num_wins_for_team(1).ans() << endl;
    cout << "Team2 wins : " << olympics2.num_wins_for_team(2).ans() << endl;


    cout << "********************end of test************************" << endl;
//    return 0; // end of test1

    // start of test2
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
    cout << "median strength player in team with strengths (2, 4, 3, 3, 6) is " << s2.getKthSmallest(s2.getSize() / 2 + 1)->getStrength() << endl;
    cout << "the median strength should be 4 in team (2, 3, 3, 4, 6)" << endl;
    cout << "this seems to be a logic error regarding the median strength of a team with players of same strength" << endl;
    cout << "looks like we're going to change the way we calculate the rank of"
            "each node or maybe add a strength tree with no duplications?"  << endl;
    cout << "will work on this later" << endl;
    cout << "*Just fixed this test, but will keep comments here for future reference*" << endl;
    cout << "********************end of test2************************" << endl;

    return 0; // end of test2



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
