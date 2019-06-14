/**
 *  @Author: Zeynep Cankara
 *  @Date: 06.05.2019
 *  @File: main.cpp
 *  @Course: CS201
 *  @Assignment: Homework03
 *  Spring 2019
 *  @Description: Driver source (.cpp) file for the library system
 *                - Conduct custom tests for classes
 */

#include <iostream>
#include "Student.h"
#include "LibrarySystem.h"
using namespace std;
int main() {

    // test for addBook() ->LibrarySystem.cpp
    cout << "====== START TEST (LibrarySystem Class) ====== \n";
    LibrarySystem ls1;
    ls1.addBook(12, "The Long Night", 2021);
    ls1.addBook(9, "Knight of The Seven Kingdoms", 2022);
    ls1.addBook(4, "Game of Thrones", 1999);
    ls1.addBook(34, "The Battle of Bastards", 2002);
    ls1.addBook(4, "A Game of Thrones", 1999);
    ls1.addBook(12, "The Song of Ice and Fire", 2021);
    // addBook working
    cout << "deleteBook() method test\n" << endl;
    ls1.deleteBook(4); // book found in the list
    ls1.deleteBook(99); // book not found in the list

    cout << "***** New library system introduced ***** \n" << endl;
    cout << " ===== Add books to the library system ===== " << endl;
     cout << "addBook() method test\n" << endl;
    LibrarySystem ls2;
    ls2.addBook(12, "Song of Ice and Fire", 2021);
    ls2.addBook(9, "Game of Thrones", 2021);
    ls2.addBook(9, "Winds of Winter", 2021);
    ls2.deleteBook(4); // book found in the list (not in the list)
    ls2.deleteBook(12); // book found in the list (head delete)
    ls2.deleteBook(12); // book already deleted (already deleted item)
    ls2.deleteBook(9); // book found in the list (single item delete)
    ls2.deleteBook(4); // book found in the list (empty list delete)

    // addStudent() check
    cout << "addStudent() method test\n" << endl;
    ls2.addStudent(12, "Jon Snow");
    ls2.addStudent(12, "Jon Snow");
    ls2.addStudent(2, "Arya Stark");
    ls2.addStudent(33, "Sansa Stark");
    ls2.addStudent(2, "Arya Stark");
    ls2.addStudent(99, "Theon Greyjoy");
    // unique students 99, 12, 33, 2
    // addStudent() working properly

    // deleteStudent() check
    // 1. empty list deletion
    // 2. deletion of the last element
    // 3. deletion from the head
    // 4. deletion in between
    // 5. single element deletion
    cout << "deleteStudent() method test\n" << endl;
    // last element deletion
    ls2.deleteStudent(12);
    // element does not exist
    ls2.deleteStudent(666);
    // delete head element
    ls2.deleteStudent(99);
    // try deleting the same element
    ls2.deleteStudent(12);
    ls2.deleteStudent(33);
    // single element deletion
    ls2.deleteStudent(2);
    // no element deletion
    ls2.deleteStudent(444);
    // deleteStudent() working properly

    cout << "checkoutBook() method test\n" << endl;
    ls2.addBook(12, "Song of Ice and Fire", 2021);
    ls2.addBook(9, "Game of Thrones", 2021);
    ls2.addBook(667, "Hardhome", 2000);
    ls2.addBook(647, "The Dance of Dragons", 2000);
    ls2.addStudent(233, "Robb Stark");
    ls2.addStudent(1, "Rhegal Targaryen");
    ls2.checkoutBook(9, 233); // checkout
    ls2.checkoutBook(1000, 233); // book does not exist
    ls2.checkoutBook(12, 11); // student does not exist
    ls2.checkoutBook(12, 1); // checkout
    ls2.checkoutBook(9, 233); // not checkout
    // checkoutBook() working properly


    cout << "showAllBook() method test\n" << endl;
    ls2.showAllBook();
    // showAllBook() working properly

    // new library systsem
    // TEST checkoutBook(bookId, studentId) works properly
    cout << "ls3 Library System Test" << endl;
    LibrarySystem ls3;
    ls3.addStudent(1, "Jamie Lannister");
    ls3.addStudent(2, "Arya Stark");
    ls3.addStudent(3, "Gendry Baratheon");
    ls3.addBook(1, "Game of Thrones", 1999);
    ls3.addBook(2, "The Children of the Forest", 2000);
    ls3.addBook(5, "Azor Ahai", 2021);
    ls3.addBook(3, "The Long Night", 2001);
    ls3.addBook(4, "Winterfell", 2019);
    ls3.addBook(44, "Battle of Blackwater", 2019);
    ls3.showAllBook();
    ls3.checkoutBook(1, 1);
    ls3.checkoutBook(5, 1);
    ls3.checkoutBook(4, 3);
    ls3.showAllBook();

    cout << "showBook() method test\n" << endl;
    ls3.showBook(4);
    ls3.showBook(222);
    ls3.showBook(2);

    cout << "showStudent() method test\n" << endl;
    ls3.showStudent(1);


    // test for delete book method
    cout << "deleteBook() method test\n" << endl;
    ls3.deleteBook(44);
    ls3.deleteBook(4);
    ls3.showAllBook();

    cout << "returnBook() method test\n" << endl;
    ls3.returnBook(1); // book checked out
    ls3.returnBook(100);  // book does not exist
    ls3.returnBook(2); // book not checked out
    ls3.showAllBook();



    // ======= END TEST ======== //
    return 0;
}
