#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <functional> //Added so I could test code
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    string potentialKeyWords = "", newKeyWord = "";

    //Refine rawWords
    trim(rawWords);
    convToLower(rawWords);

    //New set for the keywords
    std::set<std::string> keyWords;

    //Creates a stringstream for parsing
    istringstream rawData(rawWords);

    //Creates the new keywords
    while (rawData >> potentialKeyWords)
    {
        //Initializes wordSize with the size of the current word in potentialKeyWords
        size_t wordSize = potentialKeyWords.length(), numberOfLettersTracker = 0;

        //skips the word if the length is less than 2
        if (wordSize < 2) continue;

        //Checks for IBRN based on the format in database.txt
        else if (wordSize == 15)
        {
            if (potentialKeyWords[3] == '-' && potentialKeyWords[13] == '-')
            {
                //cout << "ISBN: " << potentialKeyWords << endl;
                keyWords.insert(potentialKeyWords);
                continue;
            }
        }

        //Checks and creates new keywords
        for (char& punctuationCheck : potentialKeyWords)
        {
            numberOfLettersTracker++;
            //Checks for punctuations
            if (isalpha(punctuationCheck) || isdigit(punctuationCheck))
            {
                //cout << "Current Char: " << punctuationCheck << endl;
                newKeyWord += punctuationCheck;
            }

            //Checks if newKeyWord is empty
            else if (!newKeyWord.empty())
            {
                //Adds a new key if newKeyWord is a valid length
                if (newKeyWord.length() >= 2)
                {
                    //cout << newKeyWord << endl;
                    keyWords.insert(newKeyWord);
                }

                //Resets newKeyWord
                newKeyWord = "";

                continue;
            }

            if (numberOfLettersTracker == potentialKeyWords.length() && (punctuationCheck == potentialKeyWords[potentialKeyWords.length() - 1]))
            {
                //Adds a new key if newKeyWord is a valid length
                if (newKeyWord.length() >= 2)
                {
                   // cout << newKeyWord << endl;
                    keyWords.insert(newKeyWord);
                }

                //Resets newKeyWord
                newKeyWord = "";
                numberOfLettersTracker = 0;
            }
        }
    }

    //returns the new set
    return keyWords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

 // Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
 // trim from start
std::string& ltrim(std::string& s) {
    s.erase(s.begin(),
        std::find_if(s.begin(),
            s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string& rtrim(std::string& s) {
    s.erase(
        std::find_if(s.rbegin(),
            s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
        s.end());
    return s;
}

// trim from both ends
std::string& trim(std::string& s) {
    return ltrim(rtrim(s));
}