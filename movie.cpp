#include "movie.h"
using namespace std;

Movie::Movie(const std::string& name, double price, int qty, 
            const std::string& genre, const std::string& rating)
      : Product("movie", name, price, qty), genre_(genre), rating_(rating) {}

set<string> Movie::keywords() const {
  set<string> keys = parseStringToWords(name_);
  keys.insert(genre_); // genre  also used verbatim

  return keys;
}

string Movie::displayString() const {
  string result = name_ + "\n";
  result += "Genre: " + genre_ + "Rating: " + rating_ + "\n";
  result += std::to_string(price_) + " " + std::to_string(qty_) + " left.";


  return result;
}



void Movie::dump(ostream& os) const {
  // movie then name then price then qty then genre then rating
  os <<"Movie"<<"\n"<<name_<<"\n"<<price_<<"\n"<< qty_<<"\n"<<genre_<<"\n"<<rating_<<endl;

}