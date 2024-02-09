#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"
#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string name, double price, int qty, std::string genre, std::string rating)
  : Product::Product("movie", name, price, qty)
{
  genre_ = genre;
  rating_ = rating;
}

set<string> Movie::keywords() const {
  set<string> returnSet = parseStringToWords(genre_);
  set<string> tempSet = parseStringToWords(name_);
  returnSet = setUnion(returnSet, tempSet);
  return returnSet;
}

string Movie::displayString() const {
  return name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
}

void Movie::dump(std::ostream& os) const {
  os << "movie" << "\n" << name_ << "\n" << getPrice() << "\n" << getQty() << "\n" << genre_ << "\n" << rating_ << "\n";
}