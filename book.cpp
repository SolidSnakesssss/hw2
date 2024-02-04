#include "book.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author)
    : Product(category, name, price, qty), ISBN_(ISBN), author_(author)
{
}

Book::~Book()
{
}

std::string Book::getISBN() const
{
    return ISBN_;
}

std::string Book::getAuthor() const
{
    return author_;
}

std::set<std::string> Book::keywords() const
{
    //Declare new sets
    set<string> newSet, tempSet;

    //Converts book info into lowercase
    string lowerName = convToLower(name_);
    string lowerCategory = convToLower(category_);
    string lowerAuthor = convToLower(author_);

    //parse ISBN into a keyword
    tempSet = parseStringToWords(ISBN_);
    newSet = setUnion(newSet, tempSet);

    tempSet = parseStringToWords(lowerCategory);
    newSet = setUnion(newSet, tempSet);

    tempSet = parseStringToWords(lowerName);
    newSet = setUnion(newSet, tempSet);

    tempSet = parseStringToWords(lowerAuthor);
    newSet = setUnion(newSet, tempSet);

    return newSet;
}

std::string Book::displayString() const
{
    string bookInfo = "", stringPrice, stringQuantity;

    ostringstream numbConvPrice;
    ostringstream numbConvQuant;

    numbConvPrice << price_;
    stringPrice = numbConvPrice.str();

    numbConvQuant << qty_;
    stringQuantity = numbConvQuant.str();

    bookInfo += "Category: " + category_ + "\n";
    bookInfo += "Name: " + name_ + "\n";
    bookInfo += "Price: $" + stringPrice + "\n";
    bookInfo += "Quantity: " + stringQuantity + "\n";
    bookInfo += "ISBN: " + ISBN_ + "\n";
    bookInfo += "Author " + author_ + "\n";

    //cout << bookInfo << endl;
    return bookInfo;
}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << author_ << "\n" << endl;
}