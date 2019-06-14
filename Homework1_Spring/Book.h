//
//  Book.h, Header file
//
//  @Author: Zeynep Cankara
//  @Homework: 1
//  @Course: CS201
//  @Description: Creates Book objects. Practice for dynamically allocated arrays.

#ifndef __BOOK_H
#define __BOOK_H

#include <string>
using namespace std;

class Book{
public:
    Book( const string bookTitle = "", const double bookPrice = 0 );
    Book( const Book& bookToCopy );
    ~Book();
    Book& operator=( const Book& right );
    void addEdition( const int newEditionYear );
    
private:
    string title;            // Title of the book
    double price;            // Price of the book
    int editionNo;            // Number of the editions of the book
    int* editionYears;        // A list of the years of the book's editions
    // Note that each book can have zero or more editions
    
    // BookStore class, which you will implement in Part B is declared as friend
    friend class BookStore;
    
    // Overloaded global functions for >> and << are declared as friend
    friend istream& operator>>( istream& in, Book& b );
    friend ostream& operator<<( ostream& out, const Book& b );
};

#endif

