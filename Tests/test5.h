//the stack overflow example for many rotations. The tree seems balanced and the maxRanks are correct at the end of the sequence.

olympics_t olympics;
olympics.add_team(50);
olympics.add_team(25);
olympics.add_team(75);
olympics.add_team(15);
olympics.add_team(40);
olympics.add_team(60);
olympics.add_team(80);
olympics.add_team(35);
olympics.add_team(55);
olympics.add_team(65);
olympics.add_team(90);
olympics.add_team(62);

olympics.add_player(50, 50);
olympics.add_player(25, 25);
olympics.add_player(75, 75);
olympics.add_player(15, 15);
olympics.add_player(40, 40);
olympics.add_player(60, 60);
olympics.add_player(80, 80);
olympics.add_player(35, 35);
olympics.add_player(55, 55);
olympics.add_player(65, 65);
olympics.add_player(90, 90);
olympics.add_player(62, 62);

olympics.printTeamTree();

olympics.remove_team(15);
olympics.printTeamTree();
