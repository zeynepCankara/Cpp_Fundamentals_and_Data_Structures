/**
 *  @Author: Zeynep Cankara
 *  @Date: 06.05.2019
 *  @File: Book.h
 *  @Course: CS201
 *  @Assignment: Homework03
 *  Spring 2019
 *  @Description: header (.h) file for the Book
 *                - Simple book class which will used in library system and by students
 */

#ifndef Book_h
#define Book_h


#include <string>

using namespace std;
// to make ID's unique
class Book {
private:
    string title;
    int bookId;
    int year;
public:
    // default constructor
    Book(int bookId = 0, string bookTitle = "", int bookYear = 0);
    // No need for a destructor
    // getters
    string getTitle();
    int getYear();
    int getId();
};

#endif /* Book_hpp */
