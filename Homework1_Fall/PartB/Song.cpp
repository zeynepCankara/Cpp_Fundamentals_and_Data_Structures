#include "Song.h"
// default constructor
Song::Song(const string sName, const int sMins,
const int sSecs){
this->name = sName;
this->mins = sMins;
this->secs = sSecs;
}
// destructor
Song::~Song(){
}
// copy constructor
Song::Song(const Song &songToCopy){
this->name = songToCopy.name;
this->mins = songToCopy.mins;
this->secs = songToCopy.secs;
}
// overloaded assignment operator
void Song::operator=(const Song &right){
if (&right != this) {
this->name = right.name;
this->mins = right.mins;
this->secs = right.secs;
}
}

// Getters
// minutes
int Song::getMins(){
return this->mins;
}
// seconds
int Song::getSecs(){
return this->secs;
}
// name
string Song::getName(){
return this->name;
}

