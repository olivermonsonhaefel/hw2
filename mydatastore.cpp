#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>
#include "datastore.h"
#include "util.h"
#include "mydatastore.h"
#include <map>

/***********
SOMETHING WRONG WITH CART VIEW; PROGRAM CAN'T READ IT
***********/

using namespace std;

MyDataStore::MyDataStore() {
  productVec = {};
  searchMap = {};
  userVec = {};
}
MyDataStore::~MyDataStore() {
  for(Product* p: productVec) {
    delete p;
  }
  for(User* u : userVec) {
    delete u;
  }
}

void MyDataStore::addProduct(Product* p) {
  set<string> tempSet = p->keywords();
  productVec.push_back(p);
  for(string keyword : tempSet) {
    if(searchMap.find(keyword) != searchMap.end()) {
      searchMap[keyword].insert(p);
    }
    else {
      searchMap[keyword] = {p};
    }
  }
}

void MyDataStore::addUser(User* u) {
  userVec.insert(u);
  cartMap[u->getName()] = {};
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
  set<Product*> searchSet = {};
  vector<set<Product*>> vecOsets = {};
  for(int i = 0; i < terms.size(); i++) {
    if(searchMap.find(terms[i]) != searchMap.end()) {
      vecOsets.push_back(searchMap[terms[i]]);
    }
  }
  if(type) {
    for(set<Product*> temp : vecOsets) {
      searchSet = setUnion(searchSet, temp);
    }
  }
  else {
    searchSet = vecOsets[0];
    for(int i = 1; i < vecOsets.size(); i++) {
      searchSet = setIntersection(searchSet, vecOsets[i]);
    }
  }
  vector<Product*> finalReturnVector = {};
  for(Product* p : searchSet) {
    finalReturnVector.push_back(p);
  }
  return finalReturnVector;
}
//Do I do this with the user string or the actual user?
void MyDataStore::addToCart(string u, Product* p) {
  if(cartMap.find(u) == cartMap.end()) {
    cout << "Invalid request" << endl;
    return;
  }
  cartMap[u].push(p);
}
// case insensitive username: use convToLower function in util.cpp
void MyDataStore::viewCart(string u) {
  if(cartMap.find(u) == cartMap.end()) {
    cout << "Invalid username" << endl;
    return;
  }
  queue<Product*> temp = cartMap[u];
  for(int i = 0; temp.size() != 0; i++) {
    cout << "Item " << i+1 << endl;
    cout << temp.front()->displayString() << endl;
    cout << endl;
    temp.pop();
  }
}

void MyDataStore::buyCart(string u) {
  if(cartMap.find(u) == cartMap.end()) {
    cout << "Invalid username" << endl;
    return;
  }
  queue<Product*> temp = cartMap[u];
  queue<Product*> extras = {};
  User* use;
  for(User* us : userVec) {
    if(us->getName() == u) {
      use = us;
      break;
    }
  }
  while(temp.size() != 0) {
    Product* p = temp.front();
    if(use->getBalance() >= p->getPrice() && p->getQty() > 0) {
      p->subtractQty(1);
      use->deductAmount(p->getPrice());
    }
    else {
      extras.push(p);
    }
    temp.pop();
  }
  cartMap[u] = extras;
}
//I think problem is here
void MyDataStore::dump(std::ostream& ofile) {
  ofile << "<products>" << endl;
  for(int i = 0; i < productVec.size(); i++) {
    productVec[i]->dump(ofile);
  }
  ofile <<"</products>" << endl;
  ofile << "<users>" << endl;
  for(User* u : userVec) {
    u->dump(ofile);
  }
  ofile << "</users>" << endl;
}