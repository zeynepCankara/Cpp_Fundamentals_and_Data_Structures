// Simple book node class to store books in circular linkedlist

#ifndef BookNode_h
#define BookNode_h

//================
#include "Book.h"
class BookNode {
public:
    Book book;
    BookNode* nextBook;
    // default constructor
    BookNode();
};
//================
#endif /* BookNode_h */
