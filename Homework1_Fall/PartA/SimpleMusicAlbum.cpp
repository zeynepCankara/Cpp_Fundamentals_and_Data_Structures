#include "SimpleMusicAlbum.h"
#include <iostream>
// Constructor
MusicAlbum::MusicAlbum(const string maArtist, const string maTitle, const int maYear){
    this->artist = maArtist;
    this->title = maTitle;
    this->year = maYear;
}
// Destructor
MusicAlbum::~MusicAlbum(){
}
// Copy constructor
MusicAlbum::MusicAlbum(const MusicAlbum &maToCopy){
    this->title = maToCopy.title;
    this->artist = maToCopy.artist;
    this->year = maToCopy.year;
}
// Get methods
// get artist
string MusicAlbum::getMusicAlbumArtist(){
return artist;
}
// get title
string MusicAlbum::getMusicAlbumTitle(){
return title;
}
// get year
int MusicAlbum::getMusicAlbumYear(){
return year;
}
// Overload assignment operator
void MusicAlbum::operator=(const MusicAlbum &right){
    if (&right != this) {
        this->title = right.title;
        this->artist = right.artist;
        this->year = right.year;
    }
}
// Compare two music albums
bool MusicAlbum::isEqual(const MusicAlbum &album){
    bool isSame = false;
    if (title == album.title && artist == album.artist) {
            isSame = true;
    }
    return isSame;
}

