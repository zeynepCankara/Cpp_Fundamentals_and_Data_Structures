/**
 *  @Author: Zeynep Cankara
 *  @Date: 19.04.2019
 *  @File: LibrarySystem.hpp
 *  @Course: CS201
 *  @Assignment: Homework03
 *  Spring 2019
 *  @Description: header (.h) file for the library system
 *                - Allows manipulations on the virtual library
 *                - Implementation details of helper methods in this file
 */


#ifndef LibrarySystem_h
#define LibrarySystem_h


#include <string> // for string
#include <iostream> // cout() method
#include <iomanip> // setw() method
#include "Book.h"
#include "Student.h"
using namespace std;
class LibrarySystem {
public:
    // assignment methods ===== * * * * * *
    LibrarySystem();
    ~LibrarySystem();
    void addBook( const int bookId, const string name, const int year );
    void deleteBook( const int bookId );
    void addStudent( const int studentId, const string name );
    void deleteStudent( const int studentId );
    void checkoutBook( const int bookId, const int studentId );
    void returnBook( const int bookId );
    void showAllBook();
    void showBook( const int bookId );
    void showStudent( const int studentId );
private:
    // circular linkedlist for storing students
    struct StudentNode {
        Student student;
        StudentNode* nextStudent;
        StudentNode *precedeStudent;
    };
    // for unchecked out book
    BookNode *bookHead;
    int booksNotCheckedOut;
    BookNode *bookLast;
    // for students who check out from the library
    StudentNode *studentHead;
    int booksCheckedOut;
    StudentNode *studentLast;
    // also store number of student
    int numberOfStudents;
    // my helper methods ====== * * * * *
    /**
     * @brief Checks whether a book with a given ID checked out by a student
     * @param id ID of the book to check
     */
    bool findCheckedOutBook(int id);
    /**
     * @brief Checks whether a book with a given ID present within the library
     * @param id ID of the book to check
     */
    bool findNotCheckedOutBook(int id);
    /**
     * @brief Deletes a book from not checked out list
     * @param id ID of the book to check
     */
    bool deleteNotCheckedOutBook(int id);
    /**
     * @brief Checks whether a student is in the library system
     * @param id ID of the student to check
     */
    bool findStudent(int id);
    /**
     * @brief removes the first element of the books list
     */
    void deleteFromHead();
    /**
     * @brief Finds student and get the pointer pointing to the student
     */
    StudentNode* getStudent(int id);
    /**
     * @brief Finds book with id and get the pointer pointing to the book
     */
    BookNode* getBook(int id);
    /**
     * @brief Finds book with id and returns the id of the student
     */
    int findCheckedOutBookStudent(int id);
    /**
     * @brief removes the first element of the student list
     */
    void deleteStudentFromHead();
};

// =========== =========== =========== //
#endif
