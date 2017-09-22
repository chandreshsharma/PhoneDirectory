
/*
Let's say you needed to store (in code/memory instead of a database) a group of people and their phone numbers. 
Further extend the example with the idea that a person can have multiple phone numbers and that each phone number has a type (cell, home, etc.). 
What data structure(s) or classes might you design to store this information? 

Write code that shows creation of, insertion into, and lookup from this dataset. 
Loookup should be able to be done by name or by phone number (i.e. reverse lookup). 
Be sure to handle the case where the two people with the same name are in the phone book. 
Comment on your choice of container and demonstrate that it is a good fit. Keep in mind that this is likely the only written code sample you will provide for us. 
*/

/*************************************
Assumptions:
1. A person can have more than one phone.
2. Include the possibility that there may exist more than one person with the same name,
   i.e. same name but different numbers.
3. More than 1 person can have the same number (People staying together), same phone number,
   with different names.

**************************************/

/************************************************************************************************************************************
Author:     Chandresh Sharma
email:		chandresh.sharma@gmail.com

Created:    14/04/2016

Platform:   Linux  3.16.0-30-generic
Compiler:   gcc version 4.8.2 (Ubuntu 4.8.2-19ubuntu1)
*************************************************************************************************************************************/

#include <algorithm>
#include "phonedirectory.h"


// Member functions

void PhoneDirectory::insert(std::string name, std::string phoneNumber, PhoneType phoneType)
{
    if( !phoneTypeOK(phoneType) )
    {
        std::cerr << "Error specifying phone type, ignoring input !!" << std::endl;
        return;
    }
    else
    {
#if defined(DEBUG)
        std::cout << " Adding" << name << ", " << phoneNumber << ", " << phoneType << " to directory " << std::endl;
#endif

        // Store the names in lower case.
        //
        // We use the name as the key for the database for the search operations.
        // For the search, the std::string treats the same string in different case as different strings.
        // Since we wish to print all the records with the same name, this would aid in the same.
        //
        // Also it helps since the multimap automatically sorts records, the same strings would
        // be together in the database.

        std::transform(name.begin(), name.end(), name.begin(), tolower);
        _store.insert(StrToPairMM::value_type( name, std::pair<std::string, PhoneType> (phoneNumber, phoneType ) ) );
    }
}

// @@@EXPLORE
// For the PhoneDirectory::insert() function in case space was not a constraint, and the primary objective was a quick search
// we would have maintained another map of type std::multimap < std::string phoneNumber, std::string Name> StrToStrMM.
//
// Each insertion in the StrToPairMM _store, would also store a value in the StrToStrMM with the phoneNumber as the Key.
// This would help in the reverse lookup, where the person name needs to be searched based on the phone number.
// This would result in extra code, but the results would be that much faster.
// Although the maintenance of the code would have to be taken care of.


void PhoneDirectory::getInfoFromName(std::string name)
{
    std::cout << "\nPrinting records with name: \"" << name << "\"" << std::endl;
    std::cout << "-----------------------------------------------------\n" << std::endl;

    std::transform(name.begin(), name.end(), name.begin(), tolower);
    MMIter iter = _store.find(name);

    while(iter != _store.end())
    {
        printRecord(iter);

        std::string key     = iter->first;
        std::string nextKey = (++iter)->first;

        if( key.compare(nextKey) )  // This is a multimap, which is an ordered set.
            iter = _store.end();    // In case the next key is not the same, we can stop the iteration.
    }
}

// The method to find the records based on the phonenumber has a complexity of O(n),
// since all the records would need to be searched.
// Another option would have been(as mentioned above) to save the Maps contents in another map
// OR ordered multiset so that the elements are sorted and retrieval is faster.
// However using the same too; the sort would have taken some time, and would really be effective
// if the sort and the lookup is less than O(n).

void PhoneDirectory::getInfoFromNumber(std::string phoneNumber)
{
    std::cout << "\nPrinting records with phone number: [" << phoneNumber << "]" << std::endl;
    std::cout << "-----------------------------------------------------\n" << std::endl;

    for (MMIter iter = _store.begin(); iter != _store.end(); ++iter) // O(n) complexity, see if this can be improved
    {
        if(iter->second.first == phoneNumber)
            printRecord(iter);
    }
}

// Method to create a list of dummy records.

void PhoneDirectory::populate()
{
    // Store a list of dummy records
    insert( "CCCCC", "333333333", CELL);
    insert( "AAAAA", "111111111", HOME);
    insert( "FFFFF", "666666666", OTHER);
    insert( "BBBBB", "222222222", OFFICE);
    insert( "EEEEE", "555555555", HOME);
    insert( "HHHHH", "888888888", CELL);
    insert( "BBBBB", "121212121", OFFICE);
    insert( "GGGGG", "777777777", HOME);
    insert( "FfFff", "343434343", OTHER);
    insert( "DDDDD", "444444444", OFFICE);
    insert( "IIIII", "999999999", HOME);
    insert( "A1A1A", "111111111", HOME);
    insert( "fffff", "232323232", OTHER);
    insert( "ABABA", "222222222", OFFICE);
    insert( "HELLO", "111111111", HOME);
    insert( "EMEME", "555555555", HOME);
}

// Print contents of data store.
void PhoneDirectory::dump()
{
//    unsigned int index = 0;

    std::cout << "\n Printing directory contents ... \n" << std::endl;

    for(MMIter iter = _store.begin(); iter != _store.end(); ++iter)
    {
        printRecord(iter);
    }
}

