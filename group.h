#ifndef __hash__
#define __hash__
#include <vector>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#define TABLE_SIZE 4000

using namespace std;


class GroupEntry {
    private:
        int x1;
        int x2;
        int y1;
        int y2;
        int value;
        GroupEntry* n_hash;  /* Germans de colisio */

    public:

        GroupEntry(int x, int y);
        int getX();
        int getY();
        void operator+(int value);
        GroupEntry* getNext();
        int getValue();
        void addSynonym(GroupEntry *n);
        void show();
        void addOne();

};



class GroupMap {
    private:
        GroupEntry **table;
        int Mx;
        int mx;
        int My;
        int my;
    public:
        GroupMap();
        ~GroupMap();
        void put(int x, int y);
        int getMx();
        int getMinx();
        int getMiny();
        int getMy();
        void showTable();
        int getValue(int , int);

};
#endif
