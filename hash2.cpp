#include <cstdlib>
#include <iostream>
const int TABLE_SIZE = 128;

class HashEntry {
    typedef pair <int, int> coord;

    private:
        int key;
        int value;
        HashEntry* n_hash;  /* Colisio en el hash */
        HashEntry* n_group; /* Seguent element del grup */

    public:
        HashEntry(int key) {
                this->key = key;
                this->value = 1;
        }
    
        int getKey() {
                return key;
        }
    
        int getValue() {
                return value;
        }

        /*
         * col·lisió a la Taula de Hash.
         */
        void addSynonym(int key) {
            this->n_hash = new HashEntry(key);
        }

        int addOne() {
            return (this->value += 1);
        }

        HashEntry* getNext() {
            return n_hash;
        }
        

};
 
 
class HashMap {
private:
      HashEntry **table;

public:
      HashMap() {
            table = new HashEntry*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
                  table[i] = NULL;
      }
 
      int get(int key) {
            int hash = (key % TABLE_SIZE);
            HashEntry* n_h = table[hash];

            while (n_h != NULL && n_h->getKey() != key)
                n_h = n_h->getNext();
            if (n_h != NULL)
                return table[hash]->getValue();
            return -1;
      }
 

      void put(int key, int value) {
            int hash = (key % TABLE_SIZE);
            HashEntry* n_h = table[hash];
            if (table[hash] == NULL) {
                table[hash] = new HashEntry(key);
            } else {
                while (n_h->getNext() != NULL && n_h->getKey() != key)
                    n_h = n_h->getNext();

                if (n_h->getKey() == key) {
                    n_h->addOne();
                } else {
                    n_h->addSynonym(key);
                }
            }                  
      }     

      void showTable() {
            for (int i = 0; i < TABLE_SIZE; i++)
                std::cout << i << ":" << table[i] << ", ";
      }
 
      ~HashMap() {
            for (int i = 0; i < TABLE_SIZE; i++)
                  if (table[i] != NULL)
                        delete table[i];
            delete[] table;
      }
};


int main() {
std::cout << "B";
HashMap* h = new HashMap();
h->put(1, 2);
std::cout << "A";
h->put(2, 3);
h->put(2, 3);
h->put(2, 3);
h->put(2, 3);
h->put(3, 3);
std::cout << "B";
std::cout << "A";

std::cout << h->get(1);
std::cout << h->get(2);
std::cout << h->get(3);
//h->showTable();
}
