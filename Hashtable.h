//
// Created by allih on 15/03/2024.
//

#ifndef WET2_DS_HASHTABLE_H
#define WET2_DS_HASHTABLE_H

#include <iostream>
#include <cmath>
#include <memory>
#include "Tree.h"


using namespace std;

const int DEFAULT_CAPACITY = 101;

template <class T>
class Hashtable {
private:

    shared_ptr<Tree<T>>* table; // table of trees. Unique pointer to an array of unique pointer to trees.
    int size;
    int capacity;
    float load_factor; // maybe it is a good idea to increment this field when removing an element and counting
    //int total_elements_added;
    // this might be useful in the future when we want to give an id to each ID-less player
    // maybe this should be a static field of the class, so that we can give an id to each player that is added to the table


    void resizeUp() {
        int new_capacity = 2 * capacity + 1;
//        unique_ptr<shared_ptr<Tree<T>>[]> newTable(new shared_ptr<Tree<T>>[new_capacity]());
        auto newTable = new shared_ptr<Tree<T>>[new_capacity];

        for (int i = 0; i < new_capacity; i++) {
            newTable[i] = make_shared<Tree<T>>();
        }

        int old_capacity = capacity;
        capacity = new_capacity; // changing the rehash function


        int index = 0;
        for (int i = 0; i < old_capacity; i++) {
            if (table[i]->getSize() == 0) continue;
            shared_ptr<T>* temp = nullptr;

            try{
                temp = table[i]->returnSortedArrayOfElements();
            }catch (std::bad_alloc& e){
                // free the memory allocated for the newTable
//                newTable.reset();
                delete[] newTable;
                throw;
            }

            for (int j = 0; j < table[i]->getSize(); j++) {
                int hashed_index = hash(temp[j]->getID());
                newTable[hashed_index]->insert(temp[j]);
                index++;
            }
            delete[] temp;
        }


//        for(int i = 0; i < old_capacity; i++){
//            table[i].reset();
//        }

//        table = std::move(newTable);
        delete[] table;
        table = newTable;
    }



    void resizeDown() {
        int new_capacity = std::max(DEFAULT_CAPACITY, capacity / 2);
        auto newTable = new shared_ptr<Tree<T>>[new_capacity];

        for (int i = 0; i < new_capacity; i++) {
            newTable[i] = make_shared<Tree<T>>();
        }

        int old_capacity = capacity;
        capacity = new_capacity; // changing the rehash function


        int index = 0;
        for (int i = 0; i < old_capacity; i++) {
            if (table[i]->getSize() == 0) continue;
            shared_ptr<T>* temp = nullptr;

            try{
                temp = table[i]->returnSortedArrayOfElements();
            }catch (std::bad_alloc& e){
                // free the memory allocated for the newTable
//                newTable.reset();
                delete[] newTable;
                throw;
            }

            for (int j = 0; j < table[i]->getSize(); j++) {
                int hashed_index = hash(temp[j]->getID());
                newTable[hashed_index]->insert(temp[j]);
                index++;
            }
            delete[] temp;
        }



//        for(int i = 0; i < old_capacity; i++){
//            table[i].reset();
//        }
//        table = std::move(newTable);
        delete[] table;
        table = newTable;
    }

public:
    Hashtable(): size(0), capacity(DEFAULT_CAPACITY), load_factor(0.0f) {
//        table = make_unique<shared_ptr<Tree<T>>[]>(DEFAULT_CAPACITY);
        table = new shared_ptr<Tree<T>>[capacity];
        for (int i = 0; i < DEFAULT_CAPACITY; ++i) {
            table[i] = make_shared<Tree<T>>();
        }
    }


    ~Hashtable() {
        if(table == nullptr) return;
        delete[] table;
    }


    const shared_ptr<Tree<T>>& operator[](int index) const{
        // return the team at index
        return table[index];
    }


    shared_ptr<Tree<T>>& operator[](int index){
        // return the team at index
        return table[index];
    }

    int hash(int key){
        return key % capacity; // mod capacity hash function
    }

    bool insert(int key){

        int index = hash(key);
        // make a T item with key and add to index

        // might throw bad_alloc, so we need to catch it
        shared_ptr<T> item_ptr = make_shared<T>(key);
        // maybe add an if statement here to check if the item is already in the tree???
        if (table[index]->insert(item_ptr)) {
            size++;
            //total_elements_added++;
            // update load factor
            load_factor = size * 1.0f / capacity * 1.0f; //
            rehash();
            return true;
        }

        return false;

    }

    bool insert(shared_ptr<T> item_ptr){

        int index = hash(item_ptr->getID());
        // make a T item with key and add to index


        // maybe add an if statement here to check if the item is already in the tree???
        if (table[index]->insert(item_ptr)) {
            size++;
            //total_elements_added++;
            // update load factor
            load_factor = size * 1.0f / capacity * 1.0f;

            return true;
        }

        return false;

    }

    bool remove(int key){
        int index = hash(key);
        if(table[index]->remove(key)){
            size--;
            load_factor = size * 1.0f / capacity * 1.0f ;
            rehash();
            return true;
        }
        return false;

    }



//    void resizeDown(){
//        int new_capacity = capacity / 2 + 1;
//
//        unique_ptr<Tree<T>[]> newTable(new Tree<T>[new_capacity]());
//
//        for(int i = 0; i < capacity; i++){
//            if(table[i].getSize() > 0){
//                newTable[i] = table[i];
//            }
//        }
//        table = std::move(newTable);
//        capacity = new_capacity;
//    }


    void rehash(){

        if(load_factor > 0.75) {
            resizeUp();
        } else if(load_factor < 0.25){
            if(capacity == DEFAULT_CAPACITY) return;
            resizeDown();
        }
    }

    int getSize(){
        return size;
    }

    int getCapacity(){
        return capacity;
    }


    void printHashTable(){
        for(int i = 0; i < capacity; i++) {
            cout << *table[i] << " ";
        }
        cout << "***: size: " << size << " capacity: " << capacity << " load factor: " << load_factor;
        cout << endl;
    }

    bool contains(int key){
        int index = hash(key);
        return table[index]->contains(key);
    }

    //maybe this function can be the overloaded operator [].
    shared_ptr<T> find(int key){
        int index = hash(key);


        return table[index]->find(key);

//        return table[index]->find(key);
    }

    //int getTotalElementsAdded(){
    //   return total_elements_added;
    //}
};

#endif //WET2_DS_HASHTABLE_H
