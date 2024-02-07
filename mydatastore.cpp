#include "mydatastore.h"

using namespace std;

void MyDataStore::addProduct(Product* p)
{
    addProductToMap(p);
    products_.insert(p);
    //products_.push_back(p);
}

void MyDataStore::addUser(User* u)
{
    userSet_.insert(convToLower(u->getName()));
    userMap[convToLower(u->getName())] = u;
}

void MyDataStore::addProductToMap(Product* p)
{
    //Retrieves the keywords of the product
    set<string> keyWords = p->keywords();

    //Maps the products to the appropriate keys(key terms)
    for(set<string>::iterator it = keyWords.begin(); it != keyWords.end(); ++it)
    {
        productMap[*it].insert(p);
    }
}

/**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
*/
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    vector<Product*> results;

    if (type == 0)
    {
        results = intersectionReturn(terms);
        return results;
    }

    else if(type == 1)
    {
        results = unionReturn(terms);
        return results;
    }

    else return results;
}

//Finds the intersection of the search results
std::vector<Product*> MyDataStore::intersectionReturn(std::vector<std::string>& terms)
{
    vector<Product*> productReturn;
    set<Product*> totalProducts;
    //bool firstPass = true;

    //Checks if the map has any keys with the same term
    for(vector<string>::iterator it = terms.begin(); it != terms.end(); ++it)
    {
        //Checks if the term is in the product map
        map<std::string, set<Product*>>::iterator it1 = productMap.find(*it);

        //Executes when the term is found
        if (it1 != productMap.end())
        {
            //Creates a new set to equal the set of productMap(*it)
            std::set<Product*>& productSet = productMap[*it];
            set<Product*> tempProductsSet;

            //Adds products to the tempProductSet
            for (Product* product : productSet)
            {
                //cout << product->getName() << endl;
                tempProductsSet.insert(product);
            }

            //Gets wthe intersection of the current totalProducts and tempProductSet returning a new set
            //with only common products
            if (totalProducts.empty())
            {
                totalProducts = tempProductsSet;
                //firstPass = false;
            }
            
            /*
            else if(tempProductsSet.empty())
            {
                totalProducts.clear();
                //firstPass = true;
            }
            */

            else
            {
                totalProducts = setIntersection(totalProducts, tempProductsSet);
            }
        }

        else
        {
            totalProducts.clear();
            break;
        }
    }

    for(set<Product*>::iterator it = totalProducts.begin(); it != totalProducts.end(); ++it)
    {
        productReturn.push_back(*it);
    }

    //returns the product vector
    return productReturn;
}

//Finds the union of the searc results
std::vector<Product*> MyDataStore::unionReturn(std::vector<std::string>& terms)
{
    vector<Product*> productReturn;
    set<Product*> totalProducts;

    //cout << "Taco" << endl;

    //Checks if the map has any keys with the same term
    for(vector<string>::iterator it = terms.begin(); it != terms.end(); ++it)
    {
        //Checks if the term is in the product map
        map<std::string, set<Product*>>::iterator it1 = productMap.find(*it);

        //Executes when the term is found
        if (it1 != productMap.end())
        {
            //Creates a new set to equal the set of productMap(*it)
            std::set<Product*>& productSet = productMap[*it];
            set<Product*> tempProductsSet;

            //Adds products to the tempProductSet
            for (Product* product : productSet)
            {
                tempProductsSet.insert(product);
            }

            //Gets wthe Union of the current totalProducts and tempProductSet returning a new set
            //with only common products
            totalProducts = setUnion(totalProducts, tempProductsSet);
        }
    }

    for(set<Product*>::iterator it = totalProducts.begin(); it != totalProducts.end(); ++it)
    {
        productReturn.push_back(*it);
    }

    //returns the product vector
    return productReturn;
}

void MyDataStore::addToCart(std::string username, Product* index, int itemID)
{
    string usernameLower = convToLower(username);
    set<string>::iterator validUser  = userSet_.find(usernameLower);

    if(validUser == userSet_.end())
    {
        cout << "Invalid request" << endl;
        return;
    }

    else if(itemID == 0)
    {
        cout << "Invalid request" << endl;
        return;
    }
    
    cart[username].push_back(index);
}

void MyDataStore::displayCart(std::string username)
{
    string usernameLower = convToLower(username);
    int count = 0;

    set<string>::iterator validUser  = userSet_.find(usernameLower);

    if(validUser == userSet_.end())
    {
        cout << "Invalid username" << endl;
        return;
    }

    for(vector<Product*>::iterator it = cart[usernameLower].begin(); it != cart[usernameLower].end(); ++it)
    {
        Product* temp = *it;
        cout <<  "Item #" << ++count << ": " << temp->getName() << endl;
    }
}


//Buys Items from the user's cart (Do not need to implement item removal)
void MyDataStore::buyUserCart(std::string username)
{
    string usernameLower = convToLower(username);

    set<string>::iterator validUser  = userSet_.find(usernameLower);

    if(validUser == userSet_.end())
    {
        cout << "Invalid username" << endl;
        return;
    }

    User* tempUser = userMap[usernameLower];

    //cout << tempUser->getName() << " Before: " << tempUser->getBalance() << endl;

    for(vector<Product*>::iterator it = cart[usernameLower].begin(); it != cart[usernameLower].end(); ++it)
    {
        Product* tempProduct = *it;

        if(tempProduct->getQty() > 0)
        {
            if(tempUser->getBalance() >= tempProduct->getPrice())
            {
                tempUser->deductAmount(tempProduct->getPrice());
                tempProduct->subtractQty(1);
            }

            else continue;
        }

        else continue;
    }

    //cout << tempUser->getName() << " After: " << tempUser->getBalance() << endl;
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>\n";

    for(set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it)
    {
        Product* temp = *it;
        temp->dump(ofile);
    }

    ofile << "<users>\n";

    for(set<User*>::iterator it = users_.begin(); it != users_.end(); ++it)
    {
        User* temp = *it;
        temp->dump(ofile);
    }
}