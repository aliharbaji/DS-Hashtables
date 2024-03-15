#include <iostream>
#include "Hashtable.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Hashtable<int> h;

    h.insert(10);
    h.insert(22);
    h.insert(32);
    h.insert(42);
    h.remove(32);
    h.insert(52);
    h.insert(62);
    h.insert(72);
    h.insert(82);
    h.remove(82);
    h.remove(72);
    h.remove(62);
    h.getSize();
    cout << "this gives out an infinite loop because of the hash function we are using."
            " We are using a mod capacity hash function" << endl;
    cout << "index of 10: " << h.indexOf(10) << endl;
    cout << "index of 22: " << h.indexOf(22) << endl;
    cout << "index of 32: " << h.indexOf(32) << endl;
    cout << "index of 42: " << h.indexOf(42) << endl;

    h.printHashTable();
    return 0;
}
