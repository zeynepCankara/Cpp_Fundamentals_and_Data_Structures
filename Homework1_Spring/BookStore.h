//
//  BookStore.h, Header file
//
//  @Author: Zeynep Cankara
//  @Homework: 1
//  @Course: CS201
//  @Description: Creates BookStore objects which contains book objects.

#ifndef __BOOKSTORE_H
#define __BOOKSTORE_H

#include "Book.hpp"
class BookStore{
public:
    BookStore();
    BookStore( const BookStore& bsToCopy );
    ~BookStore();
    BookStore& operator=( const BookStore& right );
    Book& operator[]( const string title );
    void addBook( const string bookTitle, const double bookPrice );
    void removeBook( const string bookTitle );
private:
    Book* books;
    // A dynamically created array of book objects
    int bookNo;
    // Number of the books in the bookstore system
    // Overloaded global function for << is declared as friend
    friend ostream& operator<<( ostream& out, const BookStore& b );
};
#endif
