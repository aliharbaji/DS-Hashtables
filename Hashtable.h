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

const int DEFAULT_CAPACITY = 11;

template <class T>
class Hashtable {
private:
    //TODO: need to reconsider this I think. It's better to have an array of pointers to the trees instead of holding the tree objects in the array itself.
    unique_ptr<shared_ptr<Tree<T>>[]> table; // table of trees. Unique pointer to an array of unique pointer to trees.
    int size;
    int capacity;
    float load_factor; // maybe it is a good idea to increment this field when removing an element and counting
    int total_elements_added;
    // this might be useful in the future when we want to give an id to each ID-less player
    // maybe this should be a static field of the class, so that we can give an id to each player that is added to the table



    // TODO: ask omar if this works in the required time complexity
    void resizeUp(){
        int new_capacity = capacity * 2 + 1;
        unique_ptr<shared_ptr<Tree<T>>[]> newTable(new shared_ptr<Tree<T>>[new_capacity]());

        for(int i = 0; i < new_capacity; i++){
            newTable[i] = make_shared<Tree<T>>();
        }
        // TODO: add try catch block here
        auto arr = new shared_ptr<T>[size];

        int index = 0;
        for(int i = 0; i < capacity; i++){ // O(capacity) time complexity
            if(table[i]->getSize() == 0) continue;
            auto temp = table[i]->returnSortedArrayOfElements(); // works in O(n_of_team_i) time complexity
            for(int j = 0; j < table[i]->getSize(); j++){ // O(n_of_team_i) time complexity
                arr[index] = temp[j];
                index++;
            }
            delete[] temp;
        }

        capacity = new_capacity; // changing the rehash function

        if(index != size) {
            cerr << "index: " << index << " size: " << size << endl;
            throw std::runtime_error("index is not equal to size");
        }
        for(int i = 0; i < index; i++){
            int hashed_index = hash(arr[i]->getID());
            newTable[hashed_index]->insert(arr[i]);
        }
        delete[] arr;
        table = std::move(newTable);
    }

    // TODO: ask omar if this works in the required time complexity
    void resizeDown() {
        int new_capacity = std::max(DEFAULT_CAPACITY, capacity / 2);
        unique_ptr<shared_ptr<Tree<T>>[]> newTable(new shared_ptr<Tree<T>>[new_capacity]());

        for(int i = 0; i < new_capacity; i++) {
            newTable[i] = make_shared<Tree<T>>();
        }

        // TODO: add try catch block here
        auto arr = new shared_ptr<T>[size];
        int index = 0;
        for(int i = 0; i < capacity; i++){ // O(capacity) time complexity
            if(table[i]->getSize() == 0) continue;
            auto temp = table[i]->returnSortedArrayOfElements(); // works in O(n_of_team_i) time complexity
            for(int j = 0; j < table[i]->getSize(); j++){ // O(n_of_team_i) time complexity
                arr[index] = temp[j];
                index++;
            }
            delete[] temp;
        }

        if(index != size) {
            cerr << "index: " << index << " size: " << size << endl;
            throw std::runtime_error("index is not equal to size");
        }

        capacity = new_capacity; // changing the rehash function

        for(int i = 0; i < index; i++) {
            int hashed_index = hash(arr[i]->getID());
            newTable[hashed_index]->insert(arr[i]);
        }

        delete[] arr;
        table = std::move(newTable);
    }


public:
    Hashtable(): size(0), capacity(DEFAULT_CAPACITY), load_factor(0.0f), total_elements_added(0) {
        table = make_unique<shared_ptr<Tree<T>>[]>(DEFAULT_CAPACITY);
        for (int i = 0; i < DEFAULT_CAPACITY; ++i) {
            table[i] = make_shared<Tree<T>>();
        }
    }


    ~Hashtable() = default;


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
        // TODO: resize up when needed (probably depending on the load factor?)
        rehash();
        int index = hash(key);
        // make a T item with key and add to index

        // might throw bad_alloc, so we need to catch it TODO: check if this is necessary
        shared_ptr<T> item_ptr = make_shared<T>(key);
        // maybe add an if statement here to check if the item is already in the tree???
        if (table[index]->insert(item_ptr)) {
            size++;
            total_elements_added++;
            // update load factor
            load_factor = size * 1.0f / capacity * 1.0f; //
            return true;
        }

        return false;

    }

    bool remove(int key){
        rehash();
        int index = hash(key);
        if(table[index]->remove(key)){
            size--;
            load_factor = size * 1.0f / capacity * 1.0f ;
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
            cout << "++++++++++++++++++++++++++++resizing up+++++++++++++++++++++++++++++++++" << endl;
            resizeUp();
        } else if(load_factor < 0.25){
            if(capacity == DEFAULT_CAPACITY) return;
            cout << "----------------------------resizing down----------------------------------" << endl;
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

    int getTotalElementsAdded(){
        return total_elements_added;
    }
};

#endif //WET2_DS_HASHTABLE_H
