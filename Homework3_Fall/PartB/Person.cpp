//
//  Person.cpp
//  Homework03 PartB
//
//  Engineer: Zeynep Cankara
//  Copyright © 2018 Zeynep Cankara. All rights reserved.
//
#include <iostream>
#include "Person.h"
using namespace std;



// Constructor
Person::Person(const string name){
    this->name = name;
    this->head = NULL;
    this->numberOfPhones = 0;
}

/**
 * @brief Destructor
 */
Person::~Person(){
    // deallocate if Person contains phones
    if (this->head != NULL) {
        PhoneNode *cur = this->head;
        while (cur != NULL) {
            // hold the node
            PhoneNode *hold = cur;
            cur = cur->next;
            delete hold;
        }
        this->head = NULL;
        this->numberOfPhones = 0;
    }
}

/**
 * @brief Clear phones a person have
 */
void Person::clearPhones(){
    // deallocate if Person contains phones
    if (this->head != NULL) {
        PhoneNode *cur = this->head;
        while (cur != NULL) {
            // hold the node
            PhoneNode *hold = cur;
            cur = cur->next;
            delete hold;
        }
        this->head = NULL;
        this->numberOfPhones = 0;
    }
}

/**
 * @brief Copy Constructor
 * @param personToCopy desired object to copy
 */
Person::Person( const Person& personToCopy )
:name(personToCopy.name){
    // check if phones are empty or not
    this->numberOfPhones = personToCopy.numberOfPhones;
    if (personToCopy.head == NULL) {
        this->head = NULL;
    } else {
        // copying the first phone node
        this->head = new PhoneNode;
        this->head->p = personToCopy.head->p;
        // rest of the list
        PhoneNode *tailPhone = this->head;
        for (PhoneNode *cur = personToCopy.head->next; cur != NULL; cur = cur->next) {
            tailPhone->next = new PhoneNode;
            tailPhone = tailPhone->next;
            tailPhone->p = cur->p;
        }
        tailPhone->next = NULL;
    }
    // END
}


/**
 * @brief Overloaded assignment operator
 * @param right desired object to assign
 */
void Person::operator=( const Person &right ){
    // avoid self-assignment
    if (this != &right) {
        // names will be same
        this->name = right.name;
        // same number of phones
        this->numberOfPhones = right.numberOfPhones;
        // de-allocate dynamically allocated memory
        if (this->head  != NULL) {
            PhoneNode *cur = this->head;
            while (cur != NULL) {
                // hold the data
                PhoneNode *hold = cur;
                // advance the iterator
                cur = cur->next;
                //remove the node
                delete hold;
            }
        }
        // stable state
        this->head = NULL;
        // start assignment
        this->head = right.head;
        if (head != NULL){
            // pointer to phone to assign
            PhoneNode *cur = head;
            // add the first node
            PhoneNode *pNode = new PhoneNode;
            pNode->p = cur->p;
            pNode->next = NULL;
            this->head = pNode;
            // capture the original list
            PhoneNode *tail = this->head;
            cur = cur->next;
            while (cur != NULL) {
                PhoneNode *pNode = new PhoneNode;
                pNode->p = cur->p;
                tail->next = pNode;
                tail = tail->next;
                cur = cur->next;
            }
            // consistent state
            tail->next = NULL;
        }
    }
}

/**
 * @brief Getter function for name
 */
string Person::getName(){
    return this->name;
}

/**
 * @brief Finds the phone and returns a pointer to the phone
 * @param areaCode of the phone to find in the list
 * @param number of the phone to find in the list
 * @return cur pointer to the PhoneNode
 */
Person::PhoneNode* Person::findPhone( const int areaCode, const int number ){
    // check person contains any phones
    if(this->numberOfPhones > 0){
        // iterate through the linked list
        PhoneNode *cur = this->head;
        
        while(cur != NULL){
            if((cur->p.getAreaCode() == areaCode) && (cur->p.getNumber() == number)){
                return cur;
            }
            cur = cur->next;
        }
        // phone not found
        return NULL;
    } else {
        // empty list
        return NULL;
    }
}


/**
 * @brief Add a phone to the person
 * @param areaCode of the phone to add in the list
 * @param number of the phone to add in the list
 * @return added bool indicating person is added to the phone book or not
 */

bool Person::addPhone( const int areaCode, const int number ){
    // boolean flag to check a phone added or not
    bool added = false;
    // check if phone in the linkedlist
    if (findPhone(areaCode, number) != NULL) {
        // person already have the phone number
        // display error message
        cout << "ERROR: Person already have the phone number: (+" << areaCode << ")" << number << endl;
        return added;
    }
    // list empty checkpoint
    if (this->head == NULL) {
        PhoneNode *pNode = new PhoneNode;
        this->numberOfPhones++;
        pNode->p = Phone(areaCode, number);
        pNode->next = NULL;
        this->head = pNode;
        return !added;
    }
    // add to the head O(1)
    this->numberOfPhones++;
    PhoneNode *pNode = new PhoneNode;
    pNode->next = this->head;
    pNode->p = Phone(areaCode, number);
    this->head = pNode;
    return !added;
}


/**
 * @brief Remove a phone number from the person
 * @param areaCode of the phone to remove from the list
 * @param number of the phone to remove from the list
 * @return removed bool indicating phone number is removed or not
 */
bool Person::removePhone( const int areaCode, const int number ){
    // boolean flag indicating whether a person can be removed from the list
    bool removed = false;
    // check if person has the phone
    if (findPhone(areaCode, number) == NULL) {
        // person do not have the phone
        // display error message
        cout << "ERROR: Person do not have the phone number: (+" << areaCode << ")" << number << endl;
        return removed;
    } else {
        // person have the phone
        PhoneNode *cur = this->head;
        // check for the head node
        if ((cur->p.getAreaCode() == areaCode) && (cur->p.getNumber() == number)) {
            // hold the node's reference
            PhoneNode *holdPtr = cur;
            head = head->next;
            this->numberOfPhones--;
            delete holdPtr;
            // now inform the reader you removed the node
            removed = true;
            return removed;
        }
        // take care of the rest of the list
        while (cur->next != NULL) {
            if ((cur->next->p.getAreaCode() == areaCode) && (cur->next->p.getNumber() == number)) {
                // remove the phone number
                // hold the 2 next pointer's reference
                PhoneNode *next = cur->next->next;
                // deallocate the deleted node
                this->numberOfPhones--;
                delete cur->next;
                cur->next = next;
                // now inform the reader you removed the node
                removed = true;
                return removed;
            } else {
                cur = cur->next;
            }
        }
        // code won't reach here
        cout << "--ERROR--" << endl;
        return removed;
    }
}

/**
 * @brief Prints the phone numbers a person have
 */
void Person::displayPhoneNumbers(){
    // iterator pointer for traverse the linkedlist
    PhoneNode * cur = this->head;
    if(this->head != NULL){
        while (cur != NULL) {
            cout << "Phone number: " << cur->p.getAreaCode() << ", " << cur->p.getNumber() << endl;
            cur = cur->next;
        }
    } else {
        // empty list
        cout << "--EMPTY--" << endl;
    }
}

/**
 * @brief Getter function for number of phones a Person have
 */
int Person::getNumberOfPhones(){
    return this->numberOfPhones;
}

/**
 * @brief Check is a phone is already in the list
 * @param areaCode of the phone to remove from the list
 * @param number of the phone to remove from the list
 * @return flag indicates person have the phone number or not (false if not have)
 */
bool Person::inPhoneList( const int areaCode, const int number ){
    bool flag = false;
    // check person contains any phones
    if(this->numberOfPhones > 0){
        // iterate through the linked list
        PhoneNode *cur = this->head;
        
        while(cur != NULL){
            if((cur->p.getAreaCode() == areaCode) && (cur->p.getNumber() == number)){
                // person have the phone number
                return !flag;
            }
            cur = cur->next;
        }
        // phone not found
        return flag;
    } else {
        // empty list
        return flag;
    }
}

/**
 * @brief Check whether person have phone number with the area code
 * @param areaCode of the phone number
 * @return flag indicates person have the phone number with the area code (false if not have)
 */
bool Person::haveAreaCode(const int areaCode){
    bool flag = false;
    // check person contains any phones
    if(this->numberOfPhones > 0){
        // iterate through the linked list
        PhoneNode *cur = this->head;
        
        while(cur != NULL){
            if(cur->p.getAreaCode() == areaCode){
                // person have the phone number with the area code
                return !flag;
            }
            cur = cur->next;
        }
        // phone not found
        return flag;
    } else {
        // empty list
        return flag;
    }
}

/**
 * @brief Display phone numbers with the specified area code
 * @param areaCode of the phone number
 */
void Person::displayPhoneNumbersAreaCode( const int areaCode ){
    // check if person have phone numbers with the area code
    if (this->haveAreaCode(areaCode)) {
        PhoneNode *cur = this->head;
        while (cur != NULL) {
            // if phone matches with area code print info
            if (cur->p.getAreaCode() == areaCode) {
                // display the information about the phone number with the area code
                cout << "Phone number: " << cur->p.getAreaCode() << ", " << cur->p.getNumber() << endl;
            }
            cur = cur->next;
        }
    }
}
