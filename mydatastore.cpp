#include "mydatastore.h"

using namespace std;

MyDataStore::~MyDataStore()
{   
    for (set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it)
    {
        delete *it;
    }

    products_.clear();

    for (set<User*>::iterator it = users_.begin(); it !=  users_.end(); ++it)
    {
        delete *it;
    }

    users_.clear();
}

void MyDataStore::addProduct(Product* p)
{
    addProductToMap(p);
    products_.insert(p);
}

void MyDataStore::addUser(User* u)
{
    users_.insert(u);
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

    if (type == 0) results = intersectionReturn(terms);

    else if(type == 1) results = unionReturn(terms);

    return results;
}

//Finds the intersection of the search results
std::vector<Product*> MyDataStore::intersectionReturn(std::vector<std::string>& terms)
{
    vector<Product*> productReturn;
    set<Product*> totalProducts;

    if(terms.empty()) return productReturn;

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

            //Gets wthe intersection of the current totalProducts and tempProductSet returning a new set
            //with only common products
            if (totalProducts.empty())
            {
                totalProducts = tempProductsSet;
            }

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

    if(terms.empty()) return productReturn;

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

    for(deque<Product*>::iterator it = cart[usernameLower].begin(); it != cart[usernameLower].end(); ++it)
    {
        Product* temp = *it;
        cout <<  "Item: " << ++count << endl;
        string info = temp->displayString();
        cout << info << endl;
    }
}


//Buys Items from the user's cart (Do not need to implement item removal)
//Needs to modify so item can be removed from the front
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

    for(deque<Product*>::iterator it = cart[usernameLower].begin(); it != cart[usernameLower].end();)
    {
        Product* tempProduct = *it;

        if(tempProduct->getQty() > 0)
        {
            if(tempUser->getBalance() >= tempProduct->getPrice())
            {
                tempUser->deductAmount(tempProduct->getPrice());
                tempProduct->subtractQty(1);
                it = cart[usernameLower].erase(it);
            }

            else ++it;
        }

        else ++it;
    }
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << endl;

    for(set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it)
    {
        Product* temp = *it;
        temp->dump(ofile);
    }

    ofile << "</products>" << endl;

    ofile << "<users>" << endl;

    for(set<User*>::iterator it = users_.begin(); it != users_.end(); ++it)
    {
        User* temp = *it;
        temp->dump(ofile);
    }

    ofile << "</users>" << endl;
}