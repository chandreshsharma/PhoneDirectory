#include "phonedirectory.h"

/************************************************************************************************************************************
Author:     Chandresh Sharma     
Created:    14/04/2016

Platform:   Linux  3.16.0-30-generic
Compiler:   gcc version 4.8.2 (Ubuntu 4.8.2-19ubuntu1)
*************************************************************************************************************************************/

// The program aims to add few records to the phone database and
// then search the database and fetch the records matching either
// the person's name or the phone number

int main()
{
    PhoneDirectory ph1; // Create the phone data store.

    ph1.insert("Chandresh", "+91 5566778899", CELL);
    ph1.insert("Sharma", "(022)(223344556)", HOME);

    ph1.insert("Sam", "789-897-778", HOME);
    ph1.insert("Sam", "(123)-456 789", (PhoneType)4); // Attempt to insert an incorrect PhoneType

    ph1.populate();
    ph1.dump();

    ph1.getInfoFromName("FFFfF");
    ph1.getInfoFromName("BbBBb");
    ph1.getInfoFromName("CCCcC");

    ph1.getInfoFromNumber("111111111");
    ph1.getInfoFromNumber("555555555");
    ph1.getInfoFromNumber("(022)(223344556)");
 
    return 0;
}
