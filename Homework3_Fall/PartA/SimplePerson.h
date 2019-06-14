//
//  SimplePerson.hpp
//  Homework03
//
//  Created by Zeynep Cankara on 13.12.2018.
//  Copyright © 2018 Zeynep Cankara. All rights reserved.
//



#include <stdio.h>



#ifndef __SIMPLE_PERSON_H
#define __SIMPLE_PERSON_H
#include <string>
using namespace std;
class Person {
public:
    Person( const string name = "" );
    ~Person();
    Person ( const Person &personToCopy );
    void operator=( const Person &right );
    string getName();
private:
    string name;
};
#endif
