#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating)
{
}

Movie::~Movie()
{
}

std::string Movie::getGenre() const
{
    return genre_;
}

std::string Movie::getRating() const
{
    return rating_;
}

std::set<std::string> Movie::keywords() const
{
    //Declare new sets
    set<string> newSet, tempSet;

    //Converts book info into lowercase
    string lowerName = convToLower(name_);
    string lowerCategory = convToLower(category_);
    string lowerGenre = convToLower(genre_);
    string lowerRating = convToLower(rating_);

    //parse genre into a keyword
    tempSet.insert(lowerGenre);
    newSet = setUnion(newSet, tempSet);

    tempSet = parseStringToWords(lowerCategory);
    newSet = setUnion(newSet, tempSet);

    tempSet = parseStringToWords(lowerName);
    newSet = setUnion(newSet, tempSet);

    tempSet = parseStringToWords(lowerRating);
    newSet = setUnion(newSet, tempSet);

    //returns the set of keywords, newSet
    return newSet;
}

std::string Movie::displayString() const
{
    string movieInfo = "", stringPrice, stringQuantity;

    ostringstream numbConvPrice;
    ostringstream numbConvQuant;

    numbConvPrice << price_;
    stringPrice = numbConvPrice.str();

    numbConvQuant << qty_;
    stringQuantity = numbConvQuant.str();

    movieInfo += "Category: " + category_ + "\n";
    movieInfo += "Name: " + name_ + "\n";
    movieInfo += "Price: $" + stringPrice + "\n";
    movieInfo += "Quantity: " + stringQuantity + "\n";
    movieInfo += "Genre: " + genre_ + "\n";
    movieInfo += "Rating: " + rating_ + "\n";

    return movieInfo;
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_
        << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << "\n" << endl;
}