#include "mydatastore.h"
#include <iostream>
#include <cctype>
using namespace std;

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {
  // free mem from prod and users
  for ( Product* p : products_) {
    delete p;
  }

  for(auto& u : users_) {
    delete u.second;
  }
}

// add prod + update keywords
void MyDataStore::addProduct(Product* p) {
  products_.push_back(p);
  set<string> keys = p->keywords() ;



  for(string k : keys){
    k=convToLower(k);
    keywordMap_(k).insert(p);
  }
}

// add user
void MyDataStore::addUser(User* u) {
  string uname=convToLower(u->getName());
  users_[uname] = u ;

}

//search using keywods 
vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
  vector<Product*> results;

  if(terms.empty()) return results;


  // norm 1st term
  string first = convToLower(terms[0]);
  set<Product*> res= keywordMap_[first];
  for ( size_t i = 1 ; i < terms.size();i++) {
    string t =convToLower(terms[i]);

    if(type==0) { // AND
      res = setIntersection(res, keywordMap_[t]);
    }

    else { // OR
      res = setUnion(res, keywordMap_[t]);
    }
  }

  for(Product* p : res) {
    results.push_back(p);
  }



  return results;
}

//db->file
void MyDataStore::dump(ostream& ofile) {
  ofile << "<products>" << endl;
  for (Product* p : products_) {
    p->dump(ofile);
  }
  ofile << "</products>" << endl;




  ofile << "<users>" << endl;
  for (auto& kv : users_) {
    kv.second->dump(ofile);

  }
  ofile<<"</users>"<<endl;
}

// add to cart 
void MyDataStore::addToCart(const string& username, Product* p) {
  string uname = convToLower(username);
  if ( users_.find(uname) == users_.end() ){
    cout<< "Invalid request" << endl;
    return;
  }
  carts_[uname].push_back(p);
}

//view cart
void MyDataStore::viewCart(const string& uername) const {
  string uname = convToLower(username);
  auto it = carts_.find(uname);
  if(users_.find(uname) == users_.end()){
    cout << "Invalid username" <<endl;
    return;
  }

  if ( it == carts_.end() || it->second.empty() ) {
    return;
  }
  int idx=1;
  for(Product* p : it->second){
    cout<<"Item "<<idx<<": " << endl ;
    cout<< p->displayString() << endl;
    idx++;
  }
}




// buy cart
void MyDataStore::buyCart(const string& username) {
  string uname=convToLower(username);
  if(users_.find(uname) == users_.end() ) {
    cout << "Invalid username" << endl;
    return;
  }

  vector<Product*>& cart = carts_[uname];
  User* user = users_[uname];
  vector<Product*> remaining;

  for(Product* p : cart){
    if (p->getQty() > 0 && user->getBalance() >= p->getPrice()) {
      p->subtractQty(1);
      user->deductAmount(p->getPrice());
    }
    else {
      remaining.push_back(p); // cant buy so keep in cart
    }
  }

  cart = remaining;
}


//helper
string MyDataStore::convLower(const string& s) const {
  string out = s;
  for ( char& c : out) c = tolower(c);
  return out;
}