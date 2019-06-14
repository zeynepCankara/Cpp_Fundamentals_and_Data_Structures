/**
 *  @Author: Zeynep Cankara
 *  @Date: 06.05.2019
 *  @File: LibrarySystem.cpp
 *  @Course: CS201
 *  @Assignment: Homework03
 *  Spring 2019
 *  @Description: source (.cpp) file for the library system
 *                - Allows manipulations on the virtual library system
 *                - Implementation details of the helpers given in this source file as well as in the header file
 */

#include "LibrarySystem.h"

// Constructor
LibrarySystem::LibrarySystem(){
    // initialize the linkedlist pointers
    bookHead = NULL;
    bookLast = NULL;
    studentHead = NULL;
    studentLast = NULL;
    // initialize sizes of the 2 lists
    booksNotCheckedOut = 0;
    booksCheckedOut = 0;
    // students in the library system
    numberOfStudents = 0;
}

// destructor
LibrarySystem::~LibrarySystem(){
    // deallocate students and book lists
    // deallocate books list
    while (booksNotCheckedOut > 0) {
        deleteFromHead();
    }
    while (numberOfStudents > 0) {
        deleteStudentFromHead();
    }
}
// ========= HELPERS =========

// Delete books from the head
void LibrarySystem::deleteFromHead(){
    BookNode *temp = bookHead;
    // empty list
    if (!temp) {
        return;
    } else {
        // delete the head element
        bookHead = bookHead->nextBook;
        bookLast->nextBook = bookHead;
        delete temp;
        temp = NULL;
        booksNotCheckedOut--;
    }
}

// Delete students from the head of the list
void LibrarySystem::deleteStudentFromHead(){
    StudentNode *temp = studentHead;
    // empty list
    if (!temp) {
        return;
    } else {
        // delete the head element
        studentHead = studentHead->nextStudent;
        // connecition with the last
        studentHead->precedeStudent = studentLast;
        studentLast->nextStudent = studentHead;
        // call clear books function for temp
        temp->student.clearBooks();
        delete temp;
        temp = NULL;
        numberOfStudents--;
    }
}

// finds the checked out book with the specified id
bool LibrarySystem::findCheckedOutBook(int id){
    // iterate through the students list
    // call students helper function to check whether a student took the book with specified ID
    if (!studentHead) {
        // no student so book not taken by any student
        return false;
    } else {
        // iterate through the circular student list
        StudentNode *iterNode = studentHead;
        do {
            if (iterNode->student.findBook(id)) {
                return true;
            }
            iterNode = iterNode->nextStudent;
        } while (iterNode != studentHead);
        return false;
    }
}

// returns id of the student
int LibrarySystem::findCheckedOutBookStudent(int id){
    // iterate through the students list
    // call students helper function to check whether a student took the book with specified ID
    if (!studentHead) {
        // no student so book not taken by any student
        return -1;
    } else {
        // iterate through the circular student list
        StudentNode *iterNode = studentHead;
        do {
            if (iterNode->student.findBook(id)) {
                // id of the student
                return iterNode->student.getId();
            }
            iterNode = iterNode->nextStudent;
        } while (iterNode != studentHead);
        return -1;
    }
}

// finds the book not yet checked out by any student
bool LibrarySystem::findNotCheckedOutBook(int id){
    if (!bookHead) {
        // no student so book not taken by any student
        return false;
    } else {
        // iterate through the circular book (not checked out) list
        BookNode *iterNode = bookHead;
        do {
            if (iterNode->book.getId() == id) {
                return true;
            }
            iterNode = iterNode->nextBook;
        } while (iterNode != bookHead);
        return false;
    }
}


// finds the book not yet checked out by any student
BookNode* LibrarySystem::getBook(int id){
    if (!bookHead) {
        // no student so book not taken by any student
        return NULL;
    } else {
        // iterate through the circular book (not checked out) list
        BookNode *iterNode = bookHead;
        do {
            if (iterNode->book.getId() == id) {
                return iterNode;
            }
            iterNode = iterNode->nextBook;
        } while (iterNode != bookHead);
        return NULL;
    }
}


// STATUS: Working
// Finds the book with the specified id in the libraries not checked out list
bool LibrarySystem::deleteNotCheckedOutBook(int id){
    // Find the book with the id in the library system. Delete the book
    if (!bookHead) {
        // 0 books in the library not checked-out list
        return false;
    } else {
        // check cases
        // 1. single element
        // 2. delete from head
        // 3. delete from in between
        // 4. delete from last
        BookNode *iterNode = bookHead;
        // check the head
        if (iterNode->book.getId() == id) {
            // single element deletion
            if ( booksNotCheckedOut == 1) {
                delete iterNode;
                bookHead = NULL;
                bookLast = NULL;
            }
            else {
                bookHead = bookHead->nextBook;
                bookLast->nextBook = bookHead;
                delete iterNode;
                iterNode = NULL; // safe
            }
            booksNotCheckedOut--;
            return true;
        }
        while (iterNode->nextBook != bookHead) {
            if (iterNode->nextBook->book.getId() == id) {
                // not a deletion from head
                BookNode *temp = iterNode->nextBook;
                // deletion from last
                if (iterNode->nextBook == bookLast) {
                    iterNode->nextBook = iterNode->nextBook->nextBook;
                    bookLast = iterNode;
                    bookLast->nextBook = bookHead;
                } else {
                    // delete from an internal node
                    iterNode->nextBook = iterNode->nextBook->nextBook;
                }
                delete temp;
                temp = NULL;
                booksNotCheckedOut--;
                return true;
            }
            iterNode = iterNode->nextBook;
        }
        return false;
    }
}


// check a student with a given ID in the library system
bool LibrarySystem::findStudent(int id){
    if (!studentHead) {
        return false;
    } else {
        // iterate through the circular student list
        StudentNode *iterNode = studentHead;
        do {
            if (iterNode->student.getId() == id) {
                return true;
            }
            iterNode = iterNode->nextStudent;
        } while (iterNode != studentHead);
        return false;
    }
}

// check a student with a given ID in the library system
LibrarySystem::StudentNode* LibrarySystem::getStudent(int id){
    if (!studentHead) {
        return NULL;
    } else {
        // iterate through the circular student list
        StudentNode *iterNode = studentHead;
        do {
            if (iterNode->student.getId() == id) {
                return iterNode;
            }
            iterNode = iterNode->nextStudent;
        } while (iterNode != studentHead);
        return NULL;
    }
}

// ========= END OF HELPERS =========

// ========= ASSIGNMENT METHODS ===== PARTB & PARTA

/**
 * @brief Adds a book into the library displays a warning message if book already exists
 * @param bookId Id of the book
 * @param name Title of the book
 * @param year Publish year of the book
 * STATUS: Working
 */
void LibrarySystem::addBook( const int bookId, const string name, const int year){
    // Always add a book at the head of the list O(1)
    // check whether any student have the book specified with the id
    if (findCheckedOutBook(bookId)) {
        cout << "Book " << bookId << " checked out by a student can't add to the library system" << endl;
        return;
    }
    if (findNotCheckedOutBook(bookId)) {
        cout << "Book " << bookId <<  " already exists" << endl;
        return;
    }
    // add the book to the library sysytems not checked out book
    if (bookHead == NULL && bookLast == NULL) {
        BookNode *bNode = new BookNode;
        // no need to worry about memory leak book does not have dynamic alloc data
        bNode->book = Book(bookId, name, year);
        bookHead = bNode;
        bookLast = bNode;
        bookLast->nextBook = bNode;
        this->booksNotCheckedOut++;
    } else {
        BookNode *bNode = new BookNode;
        // no need to worry about memory leak book does not have dynamic alloc data
        bNode->book = Book(bookId, name, year);
        bNode->nextBook = bookHead;
        bookHead = bNode;
        bookLast->nextBook = bookHead;
        this->booksNotCheckedOut++;
    }
    cout << "Book " << bookId <<  " has been added" << endl;
}


/**
 * @brief Deletes the book with given ID from the library system
 *        - Deletion can be done on both checked out or not checked out books
 * @param bookId Id of the book
 * STATUS: Working
 */
void LibrarySystem::deleteBook( const int bookId ){
    // first check checked out books list student's list
    // second check not checked out book list in the library
    if(deleteNotCheckedOutBook(bookId)){
        // book deleted from the library display a message
        cout << "Book " << bookId <<  " has not been checked out" << endl;
        cout << "Book " << bookId <<  " has been deleted" << endl;
        return;
    }
    StudentNode *sNode = studentHead;
    // check student node is NULL or not
    if (sNode) {
        do {
            // check whether student have the book
            if (sNode->student.deleteBook(bookId)) {
                // student has the book
                // book is deleted
                cout << "Book " << bookId <<  " has been checked out" << endl;
                cout << "Book " << bookId <<  " has been deleted" << endl;
                return;
            }
            sNode = sNode->nextStudent;
        } while (sNode != studentHead);
        // couldn't find the book in the lists
        cout << "Book " << bookId <<  " does not exist" << endl;
    }
    return;
}

/**
 * @brief Adds a student to the library system
 *        - Student ID's are unique positive integers
 * @param studentId Id of the Student
 * @param name of the student
 * STATUS: Working
 */
void LibrarySystem::addStudent( const int studentId, const string name ){
    if (findStudent(studentId)) {
        // display warning message student already in the system
        cout << "Student " << studentId << " already exists " << endl;
        return;
    }
    // add the student to the student list
    // empty list
    if (studentHead == NULL && studentLast == NULL) {
        StudentNode *sNode = new StudentNode;
        // new student
        sNode->student = Student(name, studentId);
        studentHead = sNode;
        studentLast = sNode;
        studentHead->precedeStudent = studentLast; // connect the precede
        studentLast->nextStudent = studentHead;
        // increase number of student
        this->numberOfStudents++;
    } else {
        StudentNode *sNode = new StudentNode;
        // no need to worry about memory leak book does not have dynamic alloc data
        sNode->student = Student(name, studentId);
        sNode->nextStudent = studentHead;
        studentHead = sNode;
        sNode->precedeStudent = studentLast;
        studentLast->nextStudent = sNode;
        // increase number of student
        this->numberOfStudents++;
    }
    cout << "Student " << studentId <<  " has been added" << endl;
}


/**
 * @brief Deletes a student from the library system if student exists
 *        - Student ID's are unique positive integers
 * @param studentId Id of the Student
 * STATUS:  Pending Books that are taken by student should returned to the library
 */
void LibrarySystem::deleteStudent( const int studentId ){
    // Find the student with the given ID and delete from the student list
    if (!studentHead) {
        // 0. no student in the library
        cout << "Student " << studentId << " does not exist" << endl;
        return;
    } else {
        // check cases
        // 1. single element
        // 2. delete from head
        // 3. delete from in between
        // 4. delete from last
        StudentNode *iterNode = studentHead;
        // check the head
        if (iterNode->student.getId() == studentId) {
            // single element deletion
            if (numberOfStudents == 1) {
                delete iterNode;
                studentHead = NULL;
                studentLast = NULL;
            }
            else {
                studentHead = studentHead->nextStudent;
                studentLast->nextStudent = studentHead;
                studentHead->precedeStudent = studentLast;
                delete iterNode;
                iterNode = NULL; // safe
            }
            cout << "Student " << studentId << " has been deleted" << endl;
            numberOfStudents--;
            return;
        }
        while (iterNode->nextStudent != studentHead) {
            if (iterNode->nextStudent->student.getId() == studentId) {
                // not a deletion from head
                StudentNode *temp = iterNode->nextStudent;
                // deletion from last
                if (iterNode->nextStudent == studentLast) {
                    iterNode->nextStudent = iterNode->nextStudent->nextStudent;
                    studentLast = iterNode;
                    studentLast->nextStudent = studentHead;
                    studentHead->precedeStudent = studentLast;
                } else {
                    // delete from an internal node
                    iterNode->nextStudent = iterNode->nextStudent->nextStudent;
                }
                delete temp;
                temp = NULL;
                numberOfStudents--;
                cout << "Student " << studentId << " has been deleted" << endl;
                return;
            }
            iterNode = iterNode->nextStudent;
        }
        cout << "Student " << studentId << " does not exist" << endl;
    }
}

/**
 * @brief Checkout a book from the library
 *        - Display warning message if book or student does not exiast
 * @param studentId Id of the Student
 * @param bookId Id of the Book to check out
 * STATUS: Working
 */
void LibrarySystem::checkoutBook( const int bookId, const int studentId ){
    if (!findNotCheckedOutBook(bookId)) {
        // book not found in the library's book checkout list
        // NOTE a book can only checked out once
        cout << "Book " << bookId << " does not exist for checkout" << endl;
        return;
    }
    if (!findStudent(studentId)) {
        cout << "Student " << studentId << " does not exist for checkout" << endl;
        return;
    }
    // perform the checkout operation
    // you will add the book to student's book list delete from library
    StudentNode *studentPtr = getStudent(studentId);
    // get the book
    BookNode *bookPtr = getBook(bookId);
    // add book
    studentPtr->student.addBook(bookPtr->book.getId(), bookPtr->book.getTitle(), bookPtr->book.getYear());
    // delete the book from the library
    deleteNotCheckedOutBook(bookId);
    // increase the number of books checked out
    booksCheckedOut++;
    // display a message
    cout << "Book " << bookId << " has been checked out by student " << studentId << endl;
}


/**
 * @brief Displays all books in the library
 * STATUS: Working
 */
void LibrarySystem::showAllBook(){
    // first iterate through not checked out books list
    cout << "Book id " << setw(15) << setfill(' ') << "Book name" << setw(20) << setfill(' ') << "Year " << setw(10) << setfill(' ') <<            "Status" <<  endl;
    BookNode *bNode = bookHead;
    if (bNode) {
        do {
            // print the information
            cout << bNode->book.getId() << setw(25) << setfill(' ') << bNode->book.getTitle() << setw(15) << setfill(' ') << bNode->book.getYear()  << setw(15) << setfill(' ') << " Not checked out" <<  endl;
            bNode = bNode->nextBook;
        } while (bNode != bookHead);
        // iterate through student list and print the books students have
        StudentNode *sNode = studentHead;
        if (sNode) {
            do {
                // print information
                sNode->student.showBooks();
                sNode = sNode->nextStudent;
            } while (sNode != studentHead);
        }
    }
}


/**
 * @brief Returns the Book checked out by student to the Library System
 *          - Display warning message if the book does not exist
 *          - If book not checked out display a wearning message
 * STATUS: Working
 */
void LibrarySystem::returnBook( const int bookId ){
    if (findNotCheckedOutBook(bookId)) {
        // book not in the library system
        cout << "Book " << bookId << " has not been checked out" << endl;
        return;
    } else if (!findCheckedOutBook(bookId)){
        cout << "Book " << bookId << " not exist in the library" << endl;
        return;
    } else {
        // delete the book from student
        // return to the not checked out list of the library
        int studentId = findCheckedOutBookStudent(bookId);
        StudentNode *temp = getStudent(studentId);
        BookNode *bNode = temp->student.getBook(bookId);
        int year = bNode->book.getYear();
        string title = bNode->book.getTitle();
        temp->student.deleteBook(bookId);
        if (bookHead == NULL && bookLast == NULL) {
            BookNode *bNode = new BookNode;
            // no need to worry about memory leak book does not have dynamic alloc data
            bNode->book = Book(bookId, title, year);
            bookHead = bNode;
            bookLast = bNode;
            bookLast->nextBook = bNode;
            this->booksNotCheckedOut++;
        } else {
            BookNode *bNode = new BookNode;
            // no need to worry about memory leak book does not have dynamic alloc data
            bNode->book = Book(bookId, title, year);
            bNode->nextBook = bookHead;
            bookHead = bNode;
            bookLast->nextBook = bookHead;
            this->booksNotCheckedOut++;
        }
        cout << "Book " << bookId << " has been returned" << endl;
    }
}


/**
 * @brief Displays detailed information about a particular book
 * STATUS: Working
 */
void LibrarySystem::showBook(const int bookId){
    if (findCheckedOutBook(bookId)) {
        // book checked out by a student
        int studentId = findCheckedOutBookStudent(bookId);
        // get information
        StudentNode * sNode = getStudent(studentId);
        BookNode *bNode = sNode->student.getBook(bookId);
        // print the information
        cout << bNode->book.getId() << setw(25) << setfill(' ') << bNode->book.getTitle() << setw(15) << setfill(' ') << bNode->book.getYear()  << setw(15) << setfill(' ') << " Checked out by student " << studentId<<  endl;
    } else if (findNotCheckedOutBook(bookId)){
        // get the book
        BookNode *bNode = getBook(bookId);
        cout << bNode->book.getId() << setw(25) << setfill(' ') << bNode->book.getTitle() << setw(15) << setfill(' ') << bNode->book.getYear()  << setw(15) << setfill(' ') << " Not checked out" <<  endl;
    } else {
        cout << "Book with the id " << bookId << " does not exits" << endl;
    }
}


/**
 * @brief Displays detailed information about a particular student
 * STATUS: Working
 */
void LibrarySystem::showStudent(const int studentId){
    if (findStudent(studentId)) {
        // display info
        cout << "Student id: " << studentId << " student name: " <<  getStudent(studentId)->student.getName() << endl;
        // display books
        cout << "Student " << studentId << " checked out the following books: " << endl;
        getStudent(studentId)->student.showBooks2();
    } else {
        cout << "Student  " << studentId << "does not exist in the system" << endl;
    }
}
