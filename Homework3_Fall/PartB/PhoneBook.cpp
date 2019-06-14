//
//  PhoneBook.cpp
//  Homework03 PartB
//
//  Engineer: Zeynep Cankara
//  Copyright © 2018 Zeynep Cankara. All rights reserved.
//

#include "PhoneBook.h"
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
    Node *cur = head;
    while (cur != NULL) {
        // hold the next pointer because after deleting cur it will be lost
        Node *toHoldNext = cur->next;
        //clear phone numbers a person have before deleting it
        cur->t.clearPhones();
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
 * @param systemToCopy desired object to copy
 */
PhoneBook::PhoneBook (const PhoneBook& systemToCopy)
:numberOfPeople(systemToCopy.numberOfPeople){
    // check if phone book is empty or not
    if (systemToCopy.head == NULL) {
        this->head = NULL;
    } else {
        // copying the first node
        this->head = new Node;
        this->head->t = systemToCopy.head->t;
        // rest of the list
        Node *newPerson = this->head;
        for (Node *cur = systemToCopy.head->next; cur != NULL; cur = cur->next) {
            newPerson->next = new Node;
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
            Node *cur = this->head;
            while (cur != NULL) {
                // hold the data
                Node *hold = cur;
                // advance the iterator
                cur = cur->next;
                // clear the phone numbers
                hold->t.clearPhones();
                // remove the node
                delete hold;
            }
        }
        // stable state
        this->head = NULL;
        this->numberOfPeople = right.numberOfPeople;
        if (numberOfPeople > 0 ) {
            // pointer to phone book to assign
            Node *cur = right.head;
            // add the first node
            Node *pNode = new Node;
            pNode->t = cur->t;
            pNode->next = NULL;
            this->head = pNode;
            // capture the original list
            Node *tail = this->head;
            cur = cur->next;
            while (cur != NULL) {
                Node *pNode = new Node;
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
 * @return cur pointer to the Node
 */
PhoneBook::Node* PhoneBook::findPerson(string name){
    if(this->numberOfPeople > 0){
        // iterate through the linked list
        Node *cur = this->head;
        
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
        cout << "ERROR: Person " << copyName << " in the phone book!!!" << endl;
        return added;
    }
    // list empty check
    if (numberOfPeople == 0) {
        Node *pNode = new Node;
        pNode->t = Person(copyName);
        pNode->next = NULL;
        this->head = pNode;
        this->numberOfPeople++;
        return !added;
    }
    // add to the head
    Node *pNode = new Node;
    pNode->next = this->head;
    pNode->t = Person(copyName);
    this->head = pNode;
    this->numberOfPeople++;
    return !added;
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
        cout << "ERROR: Person " << copyName << " NOT in the phone book!!!" << endl;
        return removed;
    } else {
        // person exist in the phone book
        Node *cur = this->head;
        // check for the head node
        if (cur->t.getName() == copyName) {
            // hold the node's reference
            Node *holdPtr = cur;
            // decrease the number of people
            this->numberOfPeople--;
            head = head->next;
            // delete the phone numbers before deleting the node
            holdPtr->t.clearPhones();
            delete holdPtr;
        }
        while (cur->next != NULL) {
            if (cur->next->t.getName() == copyName) {
                // remove the person
                // hold the node's reference
                Node *holdPtr = cur->next;
                // decrease the number of people
                this->numberOfPeople--;
                // connect the current pointer's next
                cur->next = cur->next->next;
                // delete the phone numbers before deleting the node
                holdPtr->t.clearPhones();
                // deallocate the deleted node
                delete holdPtr;
                removed = true;
                return removed;
            }
            // advance the pointer
            cur = cur->next;
        }
        // can't remove
        cout << "ERROR: Person " << copyName << " NOT in the phone book!!!" << endl;
        return removed;
    }
}

/**
 * @brief Prints the names of people in the phone book
 */
void PhoneBook::displayPeople(){
    // iterator pointer for traverse the linkedlist
    Node * cur = this->head;
    if(this->numberOfPeople > 0){
        while (cur != NULL) {
            cout << "Person " << cur->t.getName() << ", number of phones " << cur->t.getName()<< " has " << cur->t.getNumberOfPhones() << endl;
            cur = cur->next;
        }
    } else {
        // empty list
        cout << "--EMPTY--" << endl;
    }
}


/**
 * @brief Adds a phone to the person's phone number list
 * @param areaCode of the phone 
 * @param number of the phone
 * @return flag bool indicating a phone is added or not
 */
bool PhoneBook::addPhone( string personName, int areaCode, int number ){
    bool flag = false;
    // convert name to lower case to make case in-sensitive
    string copyName = personName;
    for_each(copyName.begin(), copyName.end(), [](char & c){
        c = ::tolower(c);
    });
    // person not exist in the system
    if (findPerson(copyName) == NULL) {
        // display error message
        cout << "ERROR: Person " << copyName << " not found in the Phone Book" << endl;
        return flag;
    } else {
     // search whether phone number already exist
        Node *person = findPerson(copyName);
        // don't add the phone number if person already have the phone number
        if (person->t.inPhoneList(areaCode, number)) {
            // display error message
            cout << "ERROR: Person " << copyName << " have the phone: (+" << areaCode << ")" << number << endl;
            return flag;
        } else {
            // person do not have the phone number, add the phone number
            person->t.addPhone(areaCode, number);
            return !flag;
        }
    }
}

/**
 * @brief Removes a phone to the person's phone number list
 * @param areaCode of the phone
 * @param number of the phone
 * @return flag bool indicating a phone is added or not
 */
bool PhoneBook::removePhone( string personName, int areaCode, int number ){
    bool flag = false;
    // convert name to lower case to make case in-sensitive
    string copyName = personName;
    for_each(copyName.begin(), copyName.end(), [](char & c){
        c = ::tolower(c);
    });
    // check if person is in the system
    // person not exist in the system
    if (findPerson(copyName) == NULL) {
        // display error message
        cout << "ERROR: Person " << copyName << " not found in the system" << endl;
        return flag;
    } else {
        // search whether phone number already exist
        Node *person = findPerson(copyName);
        // don't remove number if person don't have the phone number
        if (!(person->t.inPhoneList(areaCode, number))) {
            // display error message
            cout << "ERROR: Person " << copyName << " do not have the phone number (+" << areaCode << ")" << number << endl;
            return flag;
        } else {
            // person have the phone number, remove the phone number
            person->t.removePhone(areaCode, number);
            return !flag;
        }
    }
}

/**
 * @brief Displays information about specific person
 * @param name of the person info displayed
 */
void PhoneBook::displayPerson( string name ){
    // convert name to lower case to make case in-sensitive
    string copyName = name;
    for_each(copyName.begin(), copyName.end(), [](char & c){
        c = ::tolower(c);
    });
    cout << "Person " << copyName << endl;
    // check whether person exist in the system
    if (findPerson(copyName) == NULL) {
        cout << "--EMPTY--" << endl;
    } else {
        // display all phone numbers a person have
        Node *person = findPerson(copyName);
        person->t.displayPhoneNumbers();
    }
}

/**
 * @brief Displays information about area code
 * @param areaCode display all people in the system with the area code
 */
void PhoneBook::displayAreaCode( int areaCode ){
    // boolean flag for checking whether you encountered a person having phone number with the area code
    bool flag = false;
    cout << "Area Code: " << areaCode << endl;
    // STEPS
    // iterate through people in the system (if there are any)
    // if person have phones with specified area code display them.
    if (numberOfPeople == 0) {
        // system do not have any people
        cout << "--EMPTY--" << endl;
    } else {
        // display information about people having the phone numbers with the area code
        Node *cur = this->head;
        while (cur != NULL) {
            // check if person have phone numbers with the area code
            if (cur->t.haveAreaCode(areaCode)) {
                // you encountered a person having phone number with the area code
                flag = true;
                // print the person name
                cout << "Person " << cur->t.getName() << endl;
                // display the phone numbers with the area code
                cur->t.displayPhoneNumbersAreaCode(areaCode);
            }
            // advance the pointer
            cur = cur->next;
        }
        // no one in the system have phone number with the area code
        if (flag == false) {
            cout << "--EMPTY--" << endl;
        }
    }
}


