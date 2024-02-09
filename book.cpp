#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"
#include "book.h"
#include "util.h"
using namespace std;

Book::Book(const std::string name, double price, int qty, std::string isbn, std::string author)
  : Product::Product("book", name, price, qty)
{
  isbn_ = isbn;
  author_ = author;
}

set<string> Book::keywords() const {
  set<string> returnSet = parseStringToWords(author_);
  set<string> tempAdd = parseStringToWords(name_);
  returnSet = setUnion(returnSet, tempAdd);
  returnSet.insert(isbn_);
  return returnSet;
}

std::string Book::displayString() const {
  return name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
}

void Book::dump(std::ostream& os) const {
  os << "book" << "\n" << name_ << "\n" << getPrice() << "\n" << getQty() << "\n" << isbn_ << "\n" << author_ << "\n";
}