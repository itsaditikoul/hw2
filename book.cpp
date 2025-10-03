#include "book.h"
using namespace std;

Book::Book(const std::string& name, double price, int qty, 
            const std::string& isbn, const std::string& author)
      : Product("book", name, price, qty), isbn_(isbn), author_(author) {}

set<string> Book::keywords() const {
  set<string> keys = parseStringToWords(name_);
  set<string> auth = parseStringToWords(author_);
  keys = setUnion(keys,auth);
  keys.insert(isbn_); // bc isbn is supp to be used verbatim


  return keys;
}

string Book::displayString() const {
  string result = name_ + "\n";
  result += "Author: " + author_ + "ISBN: " + isbn_ + "\n";
  result += std::to_string(price_) + " " + std::to_string(qty_) + " left.";


  return result;
}



void Book::dump(ostream& os) const {
  // book then name then price then qty then isbn then author
  os <<"book"<<"\n"<<name_<<"\n"<<price_<<"\n"<< qty_<<"\n"<<isbn_<<"\n"<<author_<<endl;

}