#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include "util.h"
#include <set>
#include <string>

class Movie : public Product {
public:
    // movie shld have name, price, qty, genre, rating 

    Clothing(const std::string& name, double price, int qty, 
              const std::string& genre, const std::string& rating);

    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

private:
    std::string genre_;
    std::string rating_;

};

#endif