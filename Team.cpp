//
// Created by omar_ on 16/02/2024.
//

#include "Team.h"
#include <iostream>



//int Team::getMedals() const {
//    return medals;
//}

int Team::getStrength() const {
    return strength;
}

















////Did a small change. Because before contestant removing himself from the team doesn't mean the team got updated. Seems fine.
//void Tea m: :  uniteTeamsIntoThis(shared_ptr<Team> otherTeam){
//
//    int numOfContestants = otherTeam->getNumberOfContestants();
//    shared_ptr<Contestant>* arr;
//    try {
//        arr = copyTeamIntoArrayAndUpdateContestants(otherTeam);
//    } catch (exception& e) {
//        throw e;
//    }
//    for (int i = 0; i < numOfContestants; i++) {
//        if (arr[i]->isActiveInTeam(this->getID())) continue;
//        addContestant(arr[i]);
//    }
//    delete[] arr;
//    //contestant->addTeam(shared_from_this()); //argument is method which converts the "this" pointer into shared_ptr
//}


//void Team::print(){
//    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
//    cout<<"Team ID: "<<getID()<<endl;
//    cout<<"PreOrder: [";
//    recursivePrintPreOrder(strengths->root);
//    cout<<"]"<<endl;
//    cout<<"InOrder: [";
//    recursivePrintInOrder(strengths->root);
//    cout<<"]"<<endl;
//    cout<<"Team strength: "<<getStrength()<<endl;
//    cout<<"Austerity measure(implemented now): "<<getAusMeasure()<<endl;
//    cout<<"Team Size: "<<strengths->getSize()<<endl;
//    cout<<"Sport: "<<(int)getSport()<<endl;
//    cout<<"Country ID: "<<getCountryID()<<endl;
//    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
//
//
//}
