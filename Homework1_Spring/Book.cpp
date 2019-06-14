//
//  BookStore.cpp, Source file
//
//  @Author: Zeynep Cankara
//  @Homework: 1
//  @Course: CS201
//  @Description: Creates Book objects.
//  Practice C++ concepts such as dynamic allocation. Overloading operators. Classes...

#include "Book.h"
#include <cstring> // >>
#include <iostream>  // cout
using namespace std;
// Default Constructor
Book::Book(const string bookTitle , const double bookPrice ){
    title = bookTitle;
    price = bookPrice;
    editionYears = NULL;
    editionNo = 0;
}

// Destructor
Book::~Book(){
    // dealloc
    if (editionYears) { // can also check (editionNo > 0)
        delete [] editionYears;
        editionNo = 0; // consistency
    }
}

// Copy Constructor
Book::Book( const Book& bookToCopy )
:editionNo(bookToCopy.editionNo){
    price = bookToCopy.price;
    title = bookToCopy.title;
    // deeep copy the edition years only it's not empty
    if (editionNo > 0) {
        editionYears = new int[editionNo];
        for (int i = 0; i < editionNo; i++) {
            editionYears[i] = bookToCopy.editionYears[i];
        }
    } else {
        editionYears = NULL;
    }
}

// Overloaded Assignment Operator
Book& Book::operator=(const Book &right){
    if (&right != this){
        price = right.price;
        title = right.title;
        if (editionNo != right.editionNo) {
            if (editionNo > 0) {
                // deallocate editions array to avoid memory leaks
                delete [] editionYears;
                editionYears = NULL;
                editionNo = 0; // consistent
            }
            // assign right Books number of editions to current Book object
            editionNo = right.editionNo;
            if (editionNo > 0 ) {
                // alloc editionYears array initialized with size of right books edition No
                editionYears = new int[editionNo];
            } else {
                editionYears = NULL; // right object does not contain any editions
                editionNo = 0;
            }
        }
        for (int i = 0; i < editionNo; i++) {
            editionYears[i] = right.editionYears[i];
        }
    }
    // return the address of current object to allow cascading
    return *this;
}

/**
 * @brief Adds new addition to the collections. Editions not need to be unique
 * @param newEditionYear year of the new edition
 */
void Book::addEdition( const int newEditionYear){
    if (editionNo > 0) {
        // increment the edition no
        editionNo++;
        // store the temporary edition years
        int * temp = editionYears;
        // create a new edition years
        editionYears = new int[editionNo];
        // copy over the current edition year elements
        for (int i = 0; i < editionNo-1; i++) {
            editionYears[i] = temp[i];
        }
        // add the new edition year
        editionYears[editionNo-1] = newEditionYear;
        // deallocate the edition year
        delete [] temp; // avoid memory leak
        temp = NULL; // safe-guard
    } else {
        // create a new edition with the incremented size
        editionNo++;
        editionYears = new int[editionNo];
        editionYears[0] = newEditionYear;
    }
}

// Overloaded << operator
ostream& operator<<( ostream& out, const Book& b ){
    // print general information
    cout << b.title << ", " << b.price << " TL ";
    // print the editionYears array
    if (b.editionNo > 0) {
        cout << "(";
        for (int i = 0; i < b.editionNo-1; i++) {
            cout << b.editionYears[i] << ", ";
        }
        cout << b.editionYears[b.editionNo-1] << ")" << endl;

    } else {
        cout << "(none)" << endl;
    }
    return out;
}

// Overloaded >> operator
istream& operator>>( istream& in, Book& b ){
    // first check whether book contains ant book edition
    if (b.editionNo > 0) {
        delete [] b.editionYears;
        b.editionNo = 0;
        b.editionYears = NULL; // safe-guard
    }
    string userInput; // userInput
    cout << "Enter all edition years for " << b.title << ": ";
    // read the input single line
    getline(cin, userInput);
    // tokenize the sting
    char * cInput = new char [userInput.length()+1];
    // convert user Input to C-strin
    strcpy (cInput, userInput.c_str());
    char * token = strtok(cInput," ");
    int newEditionSize = 0;
    // allocate space as userInputString
    int *userArray = new int[userInput.length()];
    int idx = 0;
    while (token!=NULL)
    {
        newEditionSize++; // determine size of the edition array
        userArray[idx++] = atoi(token);
        token = strtok(NULL," ");
    }
    b.editionNo = newEditionSize;
    b.editionYears = new int[newEditionSize];
    for (int i = 0; i < newEditionSize; i++) {
        b.editionYears[i] = userArray[i];
    }
    delete [] userArray; // dealloc
    delete [] cInput; // dealloc
    return in;
}

