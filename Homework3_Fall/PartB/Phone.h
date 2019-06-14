//
//  Phone.hpp
//  Homework03 PartB
//
//  Engineer: Zeynep Cankara
//  Copyright © 2018 Zeynep Cankara. All rights reserved.
//


#include <stdio.h>



#ifndef __PHONE_H
#define __PHONE_H
using namespace std;

class Phone{
public:
    Phone();
    Phone( const int areaCode, const int number );
    int getAreaCode();
    int getNumber();
private:
    int areaCode;
    int number;
};
#endif
