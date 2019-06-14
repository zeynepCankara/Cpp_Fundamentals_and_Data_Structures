/**
 *  @Author: Zeynep Cankara
 *  @Date: 06.05.2019
 *  @File: Student.cpp
 *  @Course: CS201
 *  @Assignment: Homework03
 *  Spring 2019
 *  @Description: source (.cpp) file for the Student
 *                - Simple student class which will used in library system
 *                - Student store the books they check out from the library in a circular linkedlist
 *                - Implementation details are in the header file
 */

#include "Student.h"
using namespace std;
// default constructor
Student::Student(string sName, int sId){
    id = sId;
    name = sName;
    numberOfBooks = 0;
    sBooksHead = NULL;
    last = NULL;
}

// getters
int Student::getId(){
    return id;
}
string Student::getName(){
    return name;
}
int Student::getNumberOfBook(){
    return numberOfBooks;
}

// add book
// time complexity O(n)
bool Student::addBook(int id, string title, int year){
    // iterate over the list to find the book with given ID
    if (!findBook(id)) {
        // add the book to the head of the collection
        if (sBooksHead == NULL && last == NULL) {
            // no books in the library yet
            BookNode *bNode = new BookNode;
            // no need to worry about memory leak book does not have dynamic alloc data
            bNode->book = Book(id, title, year);
            sBooksHead = bNode;
            last = bNode;
        } else {
            BookNode *bNode = new BookNode;
            // no need to worry about memory leak book does not have dynamic alloc data
            bNode->book = Book(id, title, year);
            bNode->nextBook = sBooksHead;
            sBooksHead = bNode;
        }
        last->nextBook = sBooksHead;
        this->numberOfBooks++;
        return true;
    }
    // bool already in the library
    return false;
}

// delete a book from the student's lit
bool Student::deleteBook(const int id){
    if (!findBook(id)) {
        // book not found
        return false;
    }
    if (!sBooksHead) {
        return false;
    } else {
        // check cases
        // 1. single element
        // 2. delete from head
        // 3. delete from in between
        // 4. delete from last
        BookNode *iterNode = sBooksHead;
        // check the head
        if (iterNode->book.getId() == id) {
            // single element deletion
            if ( numberOfBooks == 1) {
                delete iterNode;
                sBooksHead = NULL;
                last = NULL;
            }
            else {
                sBooksHead =sBooksHead->nextBook;
                last->nextBook = sBooksHead;
                delete iterNode;
                iterNode = NULL; // safe
            }
            numberOfBooks--;
            return true;
        }
        while (iterNode->nextBook != sBooksHead) {
            if (iterNode->nextBook->book.getId() == id) {
                // not a deletion from head
                BookNode *temp = iterNode->nextBook;
                // deletion from last
                if (iterNode->nextBook == last) {
                    iterNode->nextBook = iterNode->nextBook->nextBook;
                    last = iterNode;
                    last->nextBook = sBooksHead;
                } else {
                    // delete from an internal node
                    iterNode->nextBook = iterNode->nextBook->nextBook;
                }
                delete temp;
                temp = NULL;
                numberOfBooks--;
                return true;
            }
            iterNode = iterNode->nextBook;
        }
        return false;
    }
}

// find book only if id's match
// time complexity O(n)
bool Student::findBook(const int id){
    if (!sBooksHead) {
        // student don't take any book from the library
        return false;
    } else {
        // traver through the student's book collection
        BookNode *curNode = sBooksHead;
        // check id of head
        if (id  == curNode->book.getId()) {
            return true;
        }
        curNode = curNode->nextBook;
        while (curNode != sBooksHead) {
            if (id  == curNode->book.getId()) {
                return true;
            }
            curNode = curNode->nextBook;
        }
        return false;
    }
}


// display the books a student has
void Student::showBooks(){
    if (!sBooksHead) {
        // no book in the student's list of books
        return;
    } else {
        BookNode *bNode = sBooksHead;
        do {
            // print the information
            cout << bNode->book.getId() << setw(25) << setfill(' ') << bNode->book.getTitle() << setw(15) << setfill(' ') << bNode->book.getYear()  << setw(25) << setfill(' ') << "Checked out by student " << getId() << endl;
            bNode = bNode->nextBook;
        } while (bNode != sBooksHead);
    }
}

// method for showing books for showStudent() format
void Student::showBooks2(){
    if (!sBooksHead) {
        // no book in the student's list of books
        return;
    } else {
        cout << "Book id" << setw(25) << setfill(' ') << "Book name" << setw(15) << setfill(' ') << "Year"  << endl;
        BookNode *bNode = sBooksHead;
        do {
            // print the information
            cout << bNode->book.getId() << setw(30) << setfill(' ') << bNode->book.getTitle() << setw(15) << setfill(' ') << bNode->book.getYear()  <<  endl;
            bNode = bNode->nextBook;
        } while (bNode != sBooksHead);
    }
}


// node to the book student has
BookNode* Student::getBook(int id){
    if (!sBooksHead) {
        // no student so book not taken by any student
        return NULL;
    } else {
        // iterate through the circular book (not checked out) list
        BookNode *iterNode = sBooksHead;
        do {
            if (iterNode->book.getId() == id) {
                return iterNode;
            }
            iterNode = iterNode->nextBook;
        } while (iterNode != sBooksHead);
        return NULL;
    }
}

// head node to the student lsit
BookNode* Student::getHeadBook(){
    return sBooksHead;
}


// deallocate the book list of the students
void Student::clearBooks(){
    BookNode *iterNode = sBooksHead;
    while (numberOfBooks > 0) {
        BookNode *temp = iterNode;
        iterNode = iterNode->nextBook;
        numberOfBooks--;
        temp->nextBook = NULL; // safe
        delete temp; // deallocate
        temp = NULL;
    }
    sBooksHead = NULL;
    last = NULL;
}
