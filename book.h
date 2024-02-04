#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include "util.h"
#include <sstream>

class Book : public Product
{
public:
    Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author);
    ~Book();

    std::string getISBN() const;
    std::string getAuthor() const;
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

private:
    std::string ISBN_, author_;
};

#endif