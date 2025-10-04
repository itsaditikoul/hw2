#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include <map>
#include <set>
#include <vector>
#include <string>

class MyDataStore : public DataStore{
public: 
// constr and deconstr first
  MyDataStore();
  ~MyDataStore();

  //inherited stuff from original datastore w virtuals
  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search( std::vector<std::string>& terms,int type);
  void dump(std::ostream& ofile);

  // extra stuff from menu commands
  void addToCart(const std::string& username, Product* p);
  void viewCart(const std::string& username) const;
  void buyCart(const std::string& username);
  




private:
  //storage
  std::vector<Product*> products_;
  std::map<std::string, User*> users_; //username->User*

  //fast search
  std::map<std::string, std::set<Product*>> keywordMap_;

  //carts per user
  std::map<std::string, std::vector<Product*>> carts_;

  //helper
  std::string convLower(const std::string& s) const;
};

#endif