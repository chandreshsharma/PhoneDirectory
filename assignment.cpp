
/*
Let's say you needed to store (in code/memory instead of a database) a group of people and their phone numbers. 
Further extend the example with the idea that a person can have multiple phone numbers and that each phone number has a type (cell, home, etc.). 
What data structure(s) or classes might you design to store this information? 

Write code that shows creation of, insertion into, and lookup from this dataset. 
Lookup should be able to be done by name or by phone number (i.e. reverse lookup). 
Be sure to handle the case where the two people with the same name are in the phone book. 
Comment on your choice of container and demonstrate that it is a good fit. Keep in mind that this is likely the only written code sample you will provide for us. 
*/

/*************************************

Assumptions:
1. A person can have more than one phone.
2. Include the possibility that there may exist more than one person with the same name,
   i.e. same name but different numbers.
3. More than 1 person can have the same number (People staying together).

**************************************/

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

enum PhoneType {HOME, OFFICE, CELL, OTHER};     // Since the PhoneType is created as an enum its scalable to add new types.

// The data structure needs to store the person name, phone number, for each record.
//
// Since the search would normally be based on a person name, we have selected
// the person name as the key. Though the structure also providesa mechanism for search using the phone number.
// The phone number and phone type are tightly coupled together hence a pair of number and type
// form the value.

typedef std::pair <std::string, PhoneType> StrToPTPair;             // Pair to store the phone number and type.
                 // The phone number is stored using a string since it might include symbols like +, -, (, ).
                 // For the sake of simplicity we dont have a check to validate numbers and permissible symbols.

typedef std::multimap <std::string, StrToPTPair> StrToStrMM;
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

    StrToStrMM _store;

    bool phoneTypeOK(PhoneType phoneType)
    {
        return !((phoneType < HOME) || (phoneType > OTHER));
    }

    void printRecord(MMIter iter)
    {
        std::cout << "[" << (std::distance(_store.begin(), iter) + 1) << ". " << iter->first << ", " << iter->second.first << ", " << iter->second.second  << " ]" << std::endl;
    }
#if 0
    bool phoneNumberMatches(std::string number)
    {
        
    }
#endif
};

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
        _store.insert(StrToStrMM::value_type( name, std::pair<std::string, PhoneType> (phoneNumber, phoneType ) ) );
    }
}

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

void PhoneDirectory::dump()
{
//    unsigned int index = 0;

    std::cout << "\n Printing directory contents ... \n" << std::endl;

    for(MMIter iter = _store.begin(); iter != _store.end(); ++iter)
    {
        printRecord(iter);
    }
}

void PhoneDirectory::getInfoFromName(std::string name)
{
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

void PhoneDirectory::getInfoFromNumber(std::string phoneNumber)
{
    for (MMIter iter = _store.begin(); iter != _store.end(); ++iter) // O(n) complexity, see if this can be improved
    {
        if(iter->second.first == phoneNumber)
            printRecord(iter);
    }
}

int main()
{
    PhoneDirectory ph1;

    ph1.insert("Sam", "789-897-778", HOME);
    ph1.insert("Sam", "789-897-778", (PhoneType)4);

    ph1.populate();
    ph1.dump();

    ph1.getInfoFromName("FFFfF");
    ph1.getInfoFromName("BbBBb");
    ph1.getInfoFromName("CCCcC");

    ph1.getInfoFromNumber("111111111");
    ph1.getInfoFromNumber("555555555");
 
    return 0;
}
