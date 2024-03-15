//
// Created by allih on 15/03/2024.
//

#ifndef WET2_DS_HASHTABLE_H
#define WET2_DS_HASHTABLE_H

#include <iostream>
#include <math.h>

#include <memory>

using namespace std;

const int OPEN_FOR_INSERTION = -1;
template <class T>
class Hashtable {
private:
    shared_ptr<T[]> table;
    int size;
    int capacity;
    int numOfOpenForInsertion; // maybe it is a good idea to increment this field when removing an element and counting
public:
    Hashtable(): size(0), capacity(10), table (shared_ptr<T[]>(new T[capacity]())){}

    ~Hashtable() = default;

    int hash(T key){
        return key % capacity; // mod capacity hash function
    }

    void insert(T key){
        if(size >= capacity / 2) resize();

        int index = hash(key);
        while(table[index] != 0 && table[index] != OPEN_FOR_INSERTION){
            index = (index + 1) % capacity;
        }
        table[index] = key;
        size++;
    }


    void resize(){

        if(size >= capacity / 2){
            capacity *= 2;
            cout << "resizing up" << endl;
        } else if(size <= capacity / 4) {
            capacity /= 2;
            cout << "resizing down" << endl;
        }

        shared_ptr<T[]> newTable;
        newTable = shared_ptr<T[]>(new T[capacity]());
        int j = 0;

        for(int i = 0; i < size; i++){

            if(table[i] != 0 && table[i] != OPEN_FOR_INSERTION){
                newTable[j] = table[i];
                j++;
            }
        }
        table = newTable;
    }

    int indexOf(T key){
        int index = hash(key);
        while(table[index] != key){
            if(table[index] == 0) return -1;
            index = (index + 1) % capacity;
        }
        return index;
    }

    void rehash() {
        shared_ptr<T[]> newTable = shared_ptr<T[]>(new T[capacity]());

        for (int i = 0; i < capacity; i++) {
            if (table[i] == 0 || table[i] == OPEN_FOR_INSERTION) continue;

            T key = table[i];
            int index = hash(key);
            while (table[index] != 0 && table[index] != OPEN_FOR_INSERTION) {
                index = (index + 1) % capacity;
            }
        }

        table = newTable;
    }



    int getSize(){
        return size;
    }

    void remove(T key){
        if(size == 0) return;
        if(size <= capacity / 4) resize();
        int index = hash(key);
        while(table[index] != key){
            index = (index + 1) % capacity;
        }
        table[index] = OPEN_FOR_INSERTION;
        size--;
    }

    void printHashTable(){
        for(int i = 0; i < capacity; i++) {
            cout << table[i] << " ";
        }
        cout << endl;
    }


};

#endif //WET2_DS_HASHTABLE_H
