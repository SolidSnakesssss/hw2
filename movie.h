#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include "util.h"
#include <sstream>

class Movie : public Product
{
public:
    Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
    ~Movie();

    std::string getGenre() const;
    std::string getRating() const;
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

private:
    std::string genre_, rating_;
};

#endif