//
//  Phone.cpp
//  Homework03 PartB
//
//  Engineer: Zeynep Cankara 
//  Copyright © 2018 Zeynep Cankara. All rights reserved.
//

#include "Phone.h"

// Default Constructor
Phone::Phone(){
    this->areaCode = 0;
    this->number = 0;
}

// Constructor
Phone::Phone( const int areaCode, const int number ){
    this->areaCode = areaCode;
    this->number = number;
}

// GETTERS

/**
 * @brief Getter function for area code
 */
int Phone::getAreaCode(){
    return this->areaCode;
}

/**
 * @brief Getter function for number
 */
int Phone::getNumber(){
    return this->number;
}

