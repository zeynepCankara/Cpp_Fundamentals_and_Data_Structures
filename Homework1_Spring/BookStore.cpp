//
//  BookStore.cpp, Source file
//
//  @Author: Zeynep Cankara
//  @Homework: 1
//  @Course: CS201
//  @Description: Creates BookStore objects which contains book objects.
//  Practice C++ concepts such as dynamic allocation. Overloading operators. Classes...

#include "BookStore.h"
#include <exception> // exceptions
#include <iostream>  // cout
using namespace std;

// Default constructor
BookStore::BookStore(){
    // empty collection
    books = NULL;
    bookNo = 0;
}

// Destructor
BookStore::~BookStore(){
    // avoid memory leaks
    if (books) {
        delete [] books;
        bookNo = 0;
    }
}

// Copy Constructor
BookStore::BookStore(const BookStore& bsToCopy){
    bookNo = bsToCopy.bookNo;
    if (bookNo > 0) {
        // deep copy boook objects
        books = new Book[bookNo];
        for (int i = 0; i < bookNo; i++) {
            books[i] = bsToCopy.books[i];
        }
    } else {
        books = NULL;
        bookNo = 0;
    }
}

// Overload;ed assignment operator
BookStore& BookStore::operator=( const BookStore& right ){
    // their addresses must not be equal
    if (&right != this) {
        // do not need to do dealloc
        if (bookNo < 0) {
            bookNo = right.bookNo;
            books = new Book[bookNo];
        }
        // need to dealloc case
        else if (bookNo != right.bookNo){
            delete [] books;
            books = NULL;
            bookNo = right.bookNo;
            books = new Book[bookNo];
        }
        // their size is equal just copy over
        for (int i = 0; i < bookNo; i++) {
            books[i] = right.books[i];
        }
    }
    // return the object itself
    return *this;
}

// Overloaded [] operaotor
Book& BookStore::operator[]( const string title ){
    // flag indicates whether book with the given title in collection
    int found = -1;
    // check whether book with the given title exists
    if (bookNo > 0) {
        for (int i = 0; i < bookNo; i++) {
            // found the book
            if (books[i].title == title) {
                found = i;
            }
        }
    }
    // throw exception or access the book
    if (found == -1) {
        // throw an exception
        throw out_of_range("Cannot access a non-existing book (" + title + ")");
    } else {
        return books[found];
    }
}

/**
 *  @brief Adds a book to the book store's collection
 *  @param bookTitle title of the new book
 *  @param bookPrice price of the new book
 */
void BookStore::addBook(const string bookTitle, const double bookPrice){
    // try finding the book with the given title
    int found = -1;
    for (int i = 0; i < bookNo; i++) {
        if (books[i].title == bookTitle) {
            found = i;
        }
    }
    if (found == -1) {
        if (bookNo > 0) {
            // create a new array to add the new book in collection
            // increment the book no
            bookNo++;
            // store books in a temporary array
            Book *temp = books;
            books = new Book[bookNo];
            // copy over the previous books
            for (int i = 0; i < bookNo-1; i++) {
                books[i] = temp[i];
            }
            // add the book to the collection
            books[bookNo-1].title = bookTitle;
            books[bookNo-1].price = bookPrice;
            // dealloc previous array
            delete [] temp;
            temp = NULL; // safe guard
        } else {
            // collection does not have any previous books
            bookNo = 1;
            books = new Book[bookNo]; // this automatically creates a book
            books[bookNo-1].title = bookTitle;
            books[bookNo-1].price = bookPrice;
        }
    } else {
        // throw an exception
        throw out_of_range("Cannot add an already existing book (" + bookTitle + ")");
    }
}

/**
 *  @brief Removes Book from the collection
 *  @param bookTitle title of the book to remove
 */
void BookStore::removeBook(const string bookTitle){
    // try finding the book with the given title
    int found = -1;
    for (int i = 0; i < bookNo; i++) {
        if (books[i].title == bookTitle) {
            found = i;
        }
    }
    if (found == -1) {
        // book not found throw an exception
        throw out_of_range("Cannot remove a non-existing book (" + bookTitle + ")");
    } else {
        // check size
        if (bookNo  == 1) {
            // only 1 book
            books[0].editionNo = 0;
            delete [] books[0].editionYears;
            books[0].editionYears = NULL; // safety
            // end of object edition year deletion
            delete [] books;
            bookNo = 0;
            books = NULL;
        } else {
            //remove the book
            bookNo--;
            // temporary array to store the books
            // do not call with bookNo 0
            Book *temp = books;
            books = new Book[bookNo];
            // copy over elements untill the book we want to remove
            int idx = 0;
            for (int i = 0; i < bookNo+1; i++) {
                // skip over the book to remove
                if (i != found) {
                    books[idx++] = temp[i];
                }
                if (i == found) { // weird error for else
                    // i == found delete edition years
                    temp[i].editionNo = 0;
                    delete [] temp[i].editionYears;
                    temp[i].editionYears = NULL; // safety
                }
            }
            // deallocate the memory
            delete [] temp;
            temp = NULL; // safe-guard
        }
    }
}

// Overloaded << operator
ostream& operator<<( ostream& out, const BookStore& b ){
    // print information about every book in the collection
    if (b.bookNo > 0) {
        for (int i = 0; i < b.bookNo; i++) {
            cout << b.books[i] << endl;
        }
    }
    return out;
}
