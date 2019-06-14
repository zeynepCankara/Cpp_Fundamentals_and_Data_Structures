//
//  PhoneBook.hpp
//  Homework03PartB
//
//  Created by Zeynep Cankara on 15.12.2018.
//  Copyright © 2018 Zeynep Cankara. All rights reserved.
//


#include <stdio.h>


#ifndef __PHONEBOOK_H
#define __PHONEBOOK_H
#include <string>
#include "Person.h"
using namespace std;
class PhoneBook {
public:
    PhoneBook();
    ~PhoneBook();
    PhoneBook( const PhoneBook& systemToCopy );
    void operator=( const PhoneBook &right );
    bool addPerson( string name );
    bool removePerson( string name );
    bool addPhone( string personName, int areaCode, int number );
    bool removePhone( string personName, int areaCode, int number );
    void displayPerson( string name );
    void displayAreaCode( int areaCode );
    void displayPeople();
private:
    struct Node {
        Person t;
        Node* next;
    };
    Node *head;
    int numberOfPeople;
    Node* findPerson( string name );
};
#endif
