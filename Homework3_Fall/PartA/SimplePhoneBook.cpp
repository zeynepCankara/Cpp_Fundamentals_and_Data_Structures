//
//  SimplePhoneBook.cpp
//  Homework03
//
//  Created by Zeynep Cankara on 13.12.2018.
//  Copyright © 2018 Zeynep Cankara. All rights reserved.
//

#include "SimplePhoneBook.h"
#include <iostream>
// for converting a string to the lower case
#include <algorithm>
using namespace std;

// Default Constructor
PhoneBook::PhoneBook(){
    // initialize the empty phone book
    this->numberOfPeople = 0;

    this->head = NULL;
}

/**
 * @brief Destructor
 */
PhoneBook::~PhoneBook(){
    
    // deallocate the linkedlist
    PersonNode *cur = head;
    while (cur != NULL) {
        // hold the next pointer because after deleting cur it will be lost
        PersonNode *toHoldNext = cur->next;
        delete cur;
        // advance the current pointer
        cur = toHoldNext;
    }
    // state consistancy
    this->head = NULL;
    this->numberOfPeople = 0;
}

/**
 * @brief Copy Constructor
 * @param phoneBookToCopy desired object to copy
 */
PhoneBook::PhoneBook (const PhoneBook& phoneBookToCopy)
:numberOfPeople(phoneBookToCopy.numberOfPeople){
    // check if phone book is empty or not
    if (phoneBookToCopy.head == NULL) {
        this->head = NULL;
    } else {
        // copying the first node
        this->head = new PersonNode;
        this->head->t = phoneBookToCopy.head->t;
        // rest of the list
        PersonNode *newPerson = this->head;
        for (PersonNode *cur = phoneBookToCopy.head->next; cur != NULL; cur = cur->next) {
            newPerson->next = new PersonNode;
            newPerson = newPerson->next;
            newPerson->t = cur->t;
        }
        newPerson->next = NULL;
    }
    // END
}


/**
 * @brief Overloaded assignment operator
 * @param right desired object to assign
 */
void PhoneBook::operator=(const PhoneBook& right){
    // avoid self-assignment
    if (this != &right) {
        // de-allocate dynamically allocated memory
        if (this->numberOfPeople > 0) {
            PersonNode *cur = this->head;
            while (cur != NULL) {
                // hold the data
                PersonNode *hold = cur;
                // advance the iterator
                cur = cur->next;
                //remove the node
                delete hold;
            }
        }
        // stable state
        this->head = NULL;
        this->numberOfPeople = right.numberOfPeople;
        if (numberOfPeople > 0 ) {
            // pointer to phone book to assign
            PersonNode *cur = right.head;
            // add the first node
            PersonNode *pNode = new PersonNode;
            pNode->t = cur->t;
            pNode->next = NULL;
            this->head = pNode;
            // capture the original list
            PersonNode *tail = this->head;
            cur = cur->next;
            while (cur != NULL) {
                PersonNode *pNode = new PersonNode;
                pNode->t = cur->t;
                tail->next = pNode;
                tail = tail->next;
                cur = cur->next;
            }
            tail->next = NULL;
        } else {
            // constant state
            this->head = NULL;
        }
    }
}

/**
 * @brief Finds the person and returns a pointer to the person
 * @param name of the person to find in the list
 * @return cur pointer to the PersonNode
 */
PhoneBook::PersonNode* PhoneBook::findPerson(string name){
    if(this->numberOfPeople > 0){
        // iterate through the linked list
        PersonNode *cur = this->head;
        
        while(cur != NULL){
            if(cur->t.getName() == name){
                return cur;
            }
            cur = cur->next;
        }
        // name not found
        return NULL;
    } else {
        // empty list
        return NULL;
    }
}


/**
 * @brief Add a person to the phone book
 * @param name person to add to the phone book
 * @return added bool indicating person is added to the phone book or not
 */
bool PhoneBook::addPerson(const string name){
    // convert the string to lower case
    // create a copy because it comes as constant
    string copyName = name;
    for_each(copyName.begin(), copyName.end(), [](char & c){
        c = ::tolower(c);
    });
    
    bool added = false;
    // check if person in the linkedlist
    if (findPerson(copyName) != NULL) {
        return added;
    }
    // list empty check
    if (numberOfPeople == 0) {
        PersonNode *pNode = new PersonNode;
        pNode->t = Person(copyName);
        pNode->next = NULL;
        this->head = pNode;
        this->numberOfPeople++;
        return !added;
    }
    // add to the head
    PersonNode *pNode = new PersonNode;
    pNode->next = this->head;
    pNode->t = Person(copyName);
    this->head = pNode;
    this->numberOfPeople++;
    return  !added;
}


/**
 * @brief Remove a person to the phone book
 * @param name of the person you want to remove
 * @return removed bool indicating person is removed or not
 */
bool PhoneBook::removePerson(const string name){
    // boolean flag indicating whether a person can be removed from the list
    bool removed = false;
    // convert name to lower case to make case in-sensitive
    string copyName = name;
    for_each(copyName.begin(), copyName.end(), [](char & c){
        c = ::tolower(c);
    });
    // check if person is in the phone book
    if (findPerson(copyName) == NULL) {
        return removed;
    } else {
        // person exist in the phone book
        PersonNode *cur = this->head;
        // check for the head node
        if (cur->t.getName() == copyName) {
            // hold the node's reference
            PersonNode *holdPtr = cur;
            // decrease the number of people
            this->numberOfPeople--;
            head = head->next;
            delete holdPtr;
        }
        while (cur->next != NULL) {
            if (cur->next->t.getName() == copyName) {
                // remove the person
                // hold the node's reference
                PersonNode *holdPtr = cur->next;
                // decrease the number of people
                this->numberOfPeople--;
                // connect the current pointer's next
                cur->next = cur->next->next;
                // deallocate the deleted node
                delete holdPtr;
                removed = true;
                return removed;
            }
            // advance the pointer
            cur = cur->next;
        }
        return removed;
    }
}


/**
 * @brief Prints the names of people in the phone book
 */
void PhoneBook::displayPeople(){
    // iterator pointer for traverse the linkedlist
    PersonNode * cur = this->head;
    if(this->numberOfPeople > 0){
        while (cur != NULL) {
            cout << "Person " << cur->t.getName() << endl;
            cur = cur->next;
        }
    } else {
        // empty list
        cout << "--EMPTY--" << endl;
    }
}
