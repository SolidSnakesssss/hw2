#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    //Create new set
    std::set<T> newSet;

    //Iterates through set s1
    for (typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it)
    {
        //Adds key to newSet if both s1 and s2 have that key
        if (s2.find(*it) != s2.end())
        {
            newSet.insert(*it);
        }
    }

    //returns the new set
    return newSet;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    //Create new set
    std::set<T> newSet = s2;

    //Iterates through set s1
    for (typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it)
    {
        //Adds the key to newSet if it is not in set s2
        if (s2.find(*it) == s2.end())
        {
            newSet.insert(*it);
        }
    }

    //returns the new set
    return newSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string& ltrim(std::string& s);

// Removes any trailing whitespace
std::string& rtrim(std::string& s);

// Removes leading and trailing whitespace
std::string& trim(std::string& s);
#endif