#ifndef __hash__
#define __hash__
#include <vector>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#define TABLE_SIZE 4000

using namespace std;


class HashEntry {
    private:
        /* x, y posicio on s'ha trobat l'obstacle.
         * value es quantes vegades s'ha trobat l'obstacle.
         */
        int x;
        int y;
        int value;
        HashEntry* n_hash;  /* Germans de colisio */

    public:

        HashEntry(const int x, const int y);
        int getX() const;
        int getY() const;
        HashEntry* getNext();
        int getValue() const;
        void setValue(const int);
        void addSynonym(HashEntry *n);
        friend HashEntry& operator+(HashEntry &h, const int value);
        friend ostream& operator<<(ostream &co, const HashEntry &h);
};



class HashMap {

    /* Pot pareixer molta cosa pero es
     * simplement un hash
     */
    private:
        HashEntry* table[TABLE_SIZE];
        /* Mx, My obstacle mes llunyà.
         * mx, my obstacle mes proper.
         */
        int Mx;
        int mx;
        int My;
        int my;
    public:
        HashMap();
        ~HashMap();
        void put(const int x, const int y);
        int getMx() const;
        int getMinx() const;
        int getMiny() const;
        int getMy() const;
        int getValue(const int , const int);
        void setValue(const int, const int);
        friend ostream& operator<<(ostream&, const HashMap&);

};


#endif
