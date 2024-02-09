#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"
#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const std::string name, double price, int qty, std::string size, std::string brand)
  : Product::Product("clothing", name, price, qty) 
{
  size_ = size;
  brand_ = brand;
}

set<string> Clothing::keywords() const {
  set<string> returnSet = parseStringToWords(brand_);
  set<string> tempSet = parseStringToWords(name_);
  returnSet = setUnion(returnSet, tempSet);
  return returnSet;
}

string Clothing::displayString() const {
  return name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
}

void Clothing::dump(std::ostream& os) const {
  os << "clothing" << "\n" << name_ << "\n" << getPrice() << "\n" << getQty() << "\n" << size_ << "\n" << brand_ << "\n";
}