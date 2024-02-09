#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "datastore.h"
#include "util.h"
#include <map>
#include <queue>

class MyDataStore : public DataStore {

public:
  MyDataStore();
  ~MyDataStore();
  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);
  //figure out if I should convert to string from User here or somewhere else
  void addToCart(std::string u, Product* p);
  void viewCart(std::string u);
  void buyCart(std::string u);
  
//Change all of this from User* to string??
private:
  //change these to sets or nah?
  std::vector<Product*> productVec;
  std::set<User*> userVec;
  std::map<std::string, std::set<Product*>> searchMap;
  std::map<std::string, std::queue<Product*>> cartMap;

};