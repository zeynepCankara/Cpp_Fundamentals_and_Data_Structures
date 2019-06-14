#include "MusicAlbum.h"
// Constructor
MusicAlbum::MusicAlbum(const string maArtist, const string maTitle, const int maYear){
this->artist = maArtist;
this->title = maTitle;
this->year = maYear;

// initialize the songs list
songs = NULL;
noSongs = 0;
}
// Destructor
MusicAlbum::~MusicAlbum(){
// delete songs of the album
if (noSongs > 0) {
delete [] songs;
} else {
delete songs;
}
}
// Copy constructor
MusicAlbum::MusicAlbum(const MusicAlbum &maToCopy){
this->title = maToCopy.title;
this->artist = maToCopy.artist;
this->year = maToCopy.year;
// check if there are songs in the album
if (noSongs > 0) {
// free the memory
delete [] songs;
}
// copy the songs from maToCopy
noSongs = maToCopy.noSongs;
if (noSongs > 0) {
songs = new Song[noSongs];
for (int i = 0; i < noSongs; i++) {
songs[i] = maToCopy.songs[i];
}
} else {
noSongs = 0;
songs = NULL;
}
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

// get number of songs in the album
int MusicAlbum::getNoSongs(){
return noSongs;
}
// Overload assignment operator
void MusicAlbum::operator=(const MusicAlbum &right){
// avoid self-assignment
if (&right != this) {
this->title = right.title;
this->artist = right.artist;
this->year = right.year;
// if there are songs in the music album free the memory
if (noSongs > 0) {
delete [] songs;
} else {
delete songs;
}
// deep copy of the songs
this->noSongs = right.noSongs;
if (noSongs > 0) {
songs = new Song[noSongs];
for (int i = 0; i < noSongs; i++) {
songs[i] = right.songs[i];
}
} else {
noSongs = 0;
songs = NULL;
}
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
// part B of the music album
/**
* @brief Calculates the total length of songs in the music album
* @param minutes total minutes passed by reference
* @param seconds total seconds passed by reference
*/
void MusicAlbum::calculateMusicAlbumLength(int &minutes, int &seconds){
// initialize the minutes and seconds
minutes = 0;
seconds = 0;
// make sure there are songs in the list
if (noSongs > 0) {
for (int i = 0; i < noSongs; i++) {

minutes += songs[i].getMins();
seconds += songs[i].getSecs();
}
// conversion of seconds to the minutes
int minutesInSeconds = seconds / 60;
seconds = seconds % 60;
minutes += minutesInSeconds;
}
}
// method for adding a Song into the music album
bool MusicAlbum::addSong(const string sName, const int sMins, const int sSeconds){
bool isAdable = true;
// create a song with given parameters
Song song(sName, sMins, sSeconds);
// check if music album contains any matching song
if (noSongs > 0) {
// check if the title of the song is unique
for (int i = 0; i < noSongs; i++) {
if (songs[i].getName() == sName) {
return false;
}
}
// expand the songs and add the song
// create a template to copy elements of songs
Song *temp = new Song[noSongs];
for (int i = 0; i < noSongs; i++) {
temp[i] = songs[i];
}
// free memory the songs
delete [] songs;
// increase the size
noSongs++;
// create the songs array
songs = new Song[noSongs];
// copy from the template
for (int i = 0; i < noSongs-1; i++) {
songs[i] = temp[i];
}
// add song the song
songs[noSongs-1] = song;
// delete the temp
delete [] temp;
}
else {
// song collection is empty therefore you should initialize it
noSongs = 0;
songs = new Song[noSongs+1];
songs[noSongs] = song;
noSongs++;
}
return isAdable;
}

// clear the songs of the music album
bool MusicAlbum::clearSongs(){
if (noSongs > 0){
// delete all songs in the album
delete [] songs;
songs = NULL;
return true;
} else {
noSongs = 0;
return false;
}
}
