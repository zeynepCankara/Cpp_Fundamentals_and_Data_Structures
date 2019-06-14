/**
 *  @Author: Zeynep Cankara
 *  @Date: 06.05.2019
 *  @File: Book.cpp
 *  @Course: CS201
 *  @Assignment: Homework03
 *  Spring 2019
 *  @Description: source (.cpp) file for the Book Class
 *                - Implementation file for Simple book class
 */

#include "Book.h"
using namespace std;
// CONSTRUCTOR
Book::Book(int bookId, string bookTitle, int bookYear){
    this->bookId = bookId;
    this->title = bookTitle;
    this->year = bookYear;
}

// GETTERS
string Book::getTitle(){
    return this->title;
}
int Book::getYear(){
    return this->year;
}
int Book::getId(){
    return this->bookId;
}
