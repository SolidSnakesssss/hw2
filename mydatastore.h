#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "util.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "product.h"
#include <map>
#include <set>
#include <iostream> //Debugging Purposes

class MyDataStore : public DataStore
{
public:
    ~MyDataStore();

    void addProduct(Product* p);

    void addUser(User* u);

    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    void dump(std::ostream& ofile);

    void addProductToMap(Product* p);

    void addToCart(std::string username, Product* index, int itemID);

    void displayCart(std::string username);

    void buyUserCart(std::string username);

    std::vector<Product*> intersectionReturn(std::vector<std::string>& terms);
    std::vector<Product*> unionReturn(std::vector<std::string>& terms);


private:
    std::set<Product*> products_;
    std::set<User*> users_;
    std::set<std::string> userSet_;
    std::map<std::string, std::set<Product*>> productMap;
    std::map<std::string, std::vector<Product*>> cart;
    std::map<std::string, User*> userMap;
};

#endif