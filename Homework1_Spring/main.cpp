//
//  main.cpp
//  CS201Homework1
//
//  Created by Zeynep Cankara on 15.03.2019.
//  Copyright © 2019 Zeynep Cankara. All rights reserved.
//

#include <iostream>
# include "Book.h"
# include "BookStore.h"
using namespace std;


int main(){
    Book A( "The Lord of the Rings", 31.25 );
    Book B( "The Dispossessed", 25.35 );
    Book C;
    Book D( A );
    
    A.addEdition( 2007 );
    B.addEdition( 1974 );
    
    C = B;
    C.addEdition( 1990 );
    C.addEdition( 2010 );
    C.addEdition( 1990 );
    B.addEdition( 2004 );
    
    cout << A << endl;
    cout << B << endl;
    cout << C << endl;
    cout << D << endl;
    
    cin >> B;
    cout << B << endl;
    
    cin >> B;
    cout << B << endl;
    
    cin >> B;
    cout << B << endl;
    
    cout << C << endl;
    
    BookStore bs;
    
    bs.addBook( "Tutunamayanlar", 40.50 );
    bs.addBook( "Bir Gun Tek Basina", 34.99 );
    bs.addBook( "Love in the Time of Cholera", 40 );
    bs.addBook( "Die Blendung", 27.75 );
    
    bs["Bir Gun Tek Basina"].addEdition( 1974 );
    bs["Bir Gun Tek Basina"].addEdition( 1998 );
    bs["Bir Gun Tek Basina"].addEdition( 2007 );
    cin >> bs["Love in the Time of Cholera"];
    cout << endl << bs << endl;
    
    bs.removeBook( "Bir Gun Tek Basina" );
    cout << bs << endl;
    
        try {
            cin >> bs["The Little Prince"];
        }
        catch ( const exception& e ){
            cout << e.what() << endl;
        }
        try {
            bs.addBook( "Die Blendung", 50.45 );
        }
        catch ( const exception& e ){
            cout << e.what() << endl;
        }
        try {
            bs.removeBook( "The Waves" );
        }
        catch ( const exception& e ){
            cout << e.what() << endl;
        }
        cout << endl;
    
    BookStore bs2(bs);
    Book one( "The Catcher in the Rye", 20 );
    bs2["Tutunamayanlar"] = one;
    
    cout << bs << endl;
    cout << bs2 << endl;
    
    
    //Overloaded assignment test
    BookStore bs3;
    bs3.addBook("The Intelligent Investor", 55.30);
    bs3.addBook("The Last Lecture", 10.90);
    
    bs = bs3;
    // print bs3
    cout << bs << endl;
    
    bs3.removeBook("The Intelligent Investor");
    cout << "Contents of Store 1: " << endl;
    cout << bs << endl;
    cout << "Contents of Store 3: " << endl;
    cout << bs3 << endl;
    
    // remove 1 more book
    cout << "Store 3 bankrupt: " << endl;
    bs3.removeBook("The Last Lecture");
    cout << bs3 << endl; // nothing to print
    
    
    return 0;
}

