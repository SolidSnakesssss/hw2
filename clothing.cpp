#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand)
    : Product(category, name, price, qty), size_(size), brand_(brand)
{
}

Clothing::~Clothing()
{
}

std::string Clothing::getSize() const
{
    return size_;
}

std::string Clothing::getBrand() const
{
    return brand_;
}

std::set<std::string> Clothing::keywords() const
{
    //Declare new sets
    set<string> newSet, tempSet;
    
    //Converts book info into lowercase
    string lowerName = convToLower(name_);
    string lowerCategory = convToLower(category_);
    string lowerSize = convToLower(size_);
    string lowerBrand = convToLower(brand_);

    tempSet = parseStringToWords(lowerCategory);
    newSet = setUnion(newSet, tempSet);

    tempSet = parseStringToWords(lowerName);
    newSet = setUnion(newSet, tempSet);

    tempSet = parseStringToWords(lowerSize);
    newSet = setUnion(newSet, tempSet);

    tempSet = parseStringToWords(lowerBrand);
    newSet = setUnion(newSet, tempSet);

    //returns the set of keywords, newSet
    return newSet;
}

std::string Clothing::displayString() const
{
    string clothingInfo = "", stringPrice, stringQuantity;

    ostringstream numbConv;

    numbConv << price_;
    stringPrice = numbConv.str();

    numbConv << qty_;
    stringQuantity = numbConv.str();

    clothingInfo += "Category: " + category_ + "\n";
    clothingInfo += "Name: " + name_ + "\n";
    clothingInfo += "Price: $" + stringPrice + "\n";
    clothingInfo += "Quantity: " + stringQuantity + "\n";
    clothingInfo += "Size: " + size_ + "\n";
    clothingInfo += "Brand: " + brand_ + "\n";

    return clothingInfo;
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ 
    << "\n" << qty_ << size_ << "\n" << brand_ << "\n" << endl;
}