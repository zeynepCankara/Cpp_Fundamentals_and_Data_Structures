/**
 *  @Author: Zeynep Cankara
 *  @Date: 19.04.2019
 *  @File: Student.h
 *  @Course: CS201
 *  @Assignment: Homework03
 *  Spring 2019
 *  @Description: header (.h) file for the Book
 *                - Simple student class which will used in library system
 *                - Student allowed to keep book checked out from the library
 */

#ifndef Student_h
#define Student_h


#include "BookNode.h"
#include <string>
#include <iostream> // cout
#include <iomanip> // setw() method
using namespace std;
class Student {
private:
    // name and id
    string name;
    int id;
    // store books checked bu student in a circular linkedlist
    BookNode *sBooksHead;
    BookNode *last;
    int numberOfBooks;
public:
    // default constructor
    Student(string sName = "", int sId = 0);
    // getters
    int getId();
    string getName();
    int getNumberOfBook();
    /**
     * @brief Find a book in the students book collection
     */
    bool findBook(const int id);

    /**
     * @brief Adds a book with given parameters to the student's collection of books
     *        returns false if adding book is unsuccessful
     *        Always add the book at the head of the linkedlist due to O(1) time complexity
     */
    bool addBook( int id,  string title,  int year);
    /**
     * @brief Displays the books student has
     */
    void showBooks();
    void showBooks2();
    /**
     * @brief Deletes the book with the specified id
     */
    bool deleteBook(const int id);
    /**
     * @brief Pointer to the book
     */
    BookNode* getBook(int id);
    /**
     * @brief Get the head node to iterate through the book list
     */
    BookNode* getHeadBook();
    /**
     * @brief Deallocates the book list of the student
     */
    void clearBooks();
};

// ========== END OF DEF ============== ///
#endif /* Student_hpp */
