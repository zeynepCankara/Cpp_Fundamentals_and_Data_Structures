//
//  Person.hpp
//  Homework03PartB
//
//  Created by Zeynep Cankara on 15.12.2018.
//  Copyright © 2018 Zeynep Cankara. All rights reserved.
//



#ifndef __PERSON_H
#define __PERSON_H
#include <string>
#include "Phone.h"
using namespace std;

class Person{
public:
    // Compiler sense this as multiple default constructor
    //Person();
    Person( const string name = "" );
    ~Person();
    Person( const Person& personToCopy );
    void operator=( const Person &right );
    string getName();
    bool addPhone( const int areaCode, const int number );
    bool removePhone( const int areaCode, const int number );
    void displayPhoneNumbers();
    // MY METHODS (out of problem description)
    // clear phones a person have
    void clearPhones();
    int getNumberOfPhones();
    // check a phone is already in the list
    bool inPhoneList( const int areaCode, const int number );
    // check person have phones with the specified area code
    bool haveAreaCode( const int areaCode);
    // display phone numbers with the area code
    void displayPhoneNumbersAreaCode( const int areaCode );
    
private:
    struct PhoneNode {
        Phone p;
        PhoneNode* next;
    };
    PhoneNode *head;
    string name;
    PhoneNode* findPhone( const int areaCode, const int number );
    // number of phones a person have
    int numberOfPhones;
};
#endif
