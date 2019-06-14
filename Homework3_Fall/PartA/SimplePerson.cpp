//
//  SimplePerson.cpp
//  Homework03
//
//  Engineer: Zeynep Cankara
//  Course CS201 Section02 Homework03
//  Copyright © 2018 Zeynep Cankara. All rights reserved.
//

#include "SimplePerson.h"
#include <string>
// for printing tests
#include <iostream>
using namespace std;


// Default Constructor
Person::Person(const string name){
    this->name = name;
}

/**
 * @brief Destructor
 */
Person::~Person(){
    // do not have dynamically allocated data members
}

/**
 * @brief Copy Constructor
 * @param personToCopy Person object pass by reference
 */
Person::Person ( const Person &personToCopy ){
    this->name = personToCopy.name;
}

/**
 * @brief Overloaded assignment operator
 * @param right Person object pass by reference
 */
void Person::operator=( const Person &right ){
    // avoid self assignment
    if (this != &right) {
        this->name = right.name;
    }
}

/**
 * @brief Getter function for name
 */
string Person::getName(){
    return this->name;
}

