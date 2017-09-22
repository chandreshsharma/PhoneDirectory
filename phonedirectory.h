
#if !defined(_PHONE_DIRECTORY_H_)

#define _PHONE_DIRECTORY_H_

#include <iostream>
#include <string>
#include <map>

/************************************************************************************************************************************
Author:     Chandresh Sharma
email:		chandresh.sharma@gmail.com

Created:    14/04/2016

Platform:   Linux  3.16.0-30-generic
Compiler:   gcc version 4.8.2 (Ubuntu 4.8.2-19ubuntu1)
*************************************************************************************************************************************/

enum PhoneType {HOME, OFFICE, CELL, OTHER};     // Since the PhoneType is created as an enum its scalable to add new types.

// The data structure needs to store the person name, phone number, for each record.
//
// Since the search would normally be based on a person name, we have selected
// the person name as the key. Though the class methods also provides a mechanism for search using the phone number.
// The phone number and phone type are tightly coupled together hence a pair of number and type
// form the value.

typedef std::pair <std::string, PhoneType> StrToPTPair;             // Pair to store the phone number and type.
                 // The phone number is stored using a string since it might include symbols like +, -, (, ).
                 // For the sake of simplicity we dont have a check to validate numbers and permissible symbols.

typedef std::multimap <std::string, StrToPTPair> StrToPairMM;
typedef std::multimap <std::string, StrToPTPair>::iterator MMIter;


class PhoneDirectory
{
public:
    void insert(std::string name, std::string number, PhoneType=HOME);

    void getInfoFromName(std::string name);
    void getInfoFromNumber(std::string phoneNumber);

    void populate();
    void dump();

protected:

    StrToPairMM _store;

    bool phoneTypeOK(PhoneType phoneType)
    {
        return !((phoneType < HOME) || (phoneType > OTHER));
    }

    std::string getPhoneTypeStr(PhoneType phoneType)
    {
        switch(phoneType)
        {
            case HOME:
                return "Home";
            case OFFICE:
                return "Office";
            case CELL:
                return "Cellular";
            case OTHER:
            default:
                return "Other";
        }
    }

    void printRecord(MMIter iter)
    {
        std::cout   << "[" << (std::distance(_store.begin(), iter) + 1) << ". " << iter->first 
                    << ", " << iter->second.first << ", " << getPhoneTypeStr(iter->second.second)  << " ]\n" << std::endl;
    }
#if 0
    bool phoneNumberMatches(std::string number)
    {
        
    }
#endif
};

#endif
