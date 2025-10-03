#include "clothing.h"
using namespace std;

Clothing::Clothing(const std::string& name, double price, int qty, 
            const std::string& size, const std::string& brand)
      : Product("clothing", name, price, qty), size_(size), brand_(brand) {}

set<string> Clothing::keywords() const {
  set<string> keys = parseStringToWords(name_);
  set<string> b = parseStringToWords(brand_);
  keys = setUnion(keys,b);

  return keys;
}

string Clothing::displayString() const {
  string result = name_ + "\n";
  result += "Size: " + size_ + "Brand: " + brand_ + "\n";
  result += std::to_string(price_) + " " + std::to_string(qty_) + " left.";


  return result;
}



void Clothing::dump(ostream& os) const {
  // clotjonig then name then price then qty then size then brand
  os <<"clothing"<<"\n"<<name_<<"\n"<<price_<<"\n"<< qty_<<"\n"<<size_<<"\n"<<brand_<<endl;

}