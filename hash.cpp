
#include "hash.h"


HashEntry::HashEntry(const int x, const int y): x(x), y(y) 
{
  this->value = 1;
  this->n_hash = NULL;
}


HashEntry& operator+(HashEntry &h, const int value)
{
  h.value += value;
  return h;
}

ostream& operator<<(ostream &co, const HashEntry &h)
{
  co << "X => " << h.x << " Y=> " << h.y;
  co << " Value => " << h.value << endl;
  return co;
}


int HashEntry::getValue() const
{
  return this->value;
}


HashEntry* HashEntry::getNext()
{
  return this->n_hash;
}


void HashEntry::addSynonym(HashEntry *n)
{
  this->n_hash = n;
}

int HashEntry::getX() const
{
  return this->x;
}

int HashEntry::getY() const
{
  return this->y;
}


void HashEntry::setValue(const int val)
{
  this->value = val;
}

/**********************************************************/

HashMap::HashMap() 
{
    for (int i = 0; i < TABLE_SIZE; i++)
        this->table[i] = NULL;
    this->Mx = 0;
    this->My = 0;
    this->mx = 0;
    this->my = 0;
}


int HashMap::getMx() const
{
  return this->Mx;
}

int HashMap::getMy() const
{
  return this->My;
}

int HashMap::getMinx() const
{
  return this->mx;
}

int HashMap::getMiny() const
{
  return this->my;
}


void HashMap::put(const int x, const int y) 
{
  int hash = abs(x * y) % TABLE_SIZE;
  HashEntry *n, *p;
  if (x > this->Mx) this->Mx = x;
  if (y > this->My) this->My = y;

  if (x < this->mx) this->mx = x;
  if (y < this->my) this->my = y;

  if (this->table[hash] == NULL) {
    this->table[hash] = new HashEntry(x, y);
  } 
  else{
    n = this->table[hash];
    p = n;
    while (n != NULL){
      if (n->getX() == x
          && n->getY() == y){
        *n = *n + 1;
        return;
      }
      p = n;
      n = n->getNext();
    }
    HashEntry *j = new HashEntry(x, y);
    p->addSynonym(j);
  }
}                


int HashMap::getValue(const int x, const int y)
{
  int hash = abs(x * y) % TABLE_SIZE;
  HashEntry *n;
  if (this->table[hash] == NULL) {
    return 0;
  } 
  else{
    n = this->table[hash];
    while (n  != NULL ){
      if (n->getX() == x
          && n->getY() == y){
        return n->getValue();
      }
      n = n->getNext();
    }
    return 0;
  }
}                


void HashMap::setValue(const int x, const int y)
{
  int hash = abs(x * y) % TABLE_SIZE;
  HashEntry *n;
  if (this->table[hash] != NULL) {
    n = this->table[hash];
    while (n  != NULL ){
      if (n->getX() == x
          && n->getY() == y){
          n->setValue(0);
          break;
      }
      n = n->getNext();
    }
  }
}              


ostream& operator<<(ostream& co, const HashMap &h)
{
  HashEntry *p;   
  for (int i = 0; i < TABLE_SIZE; i++){
    p = h.table[i];
    while (p != NULL){
      co << *p;
      p = p->getNext();
    }
  }
  return co;
}

HashMap::~HashMap() 
{
    delete[] table;
}



