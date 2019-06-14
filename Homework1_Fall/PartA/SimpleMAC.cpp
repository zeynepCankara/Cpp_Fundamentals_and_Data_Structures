#include "SimpleMusicAlbum.h"
#include "SimpleMAC.h"
#include <string.h>
#include <iostream>
using namespace std;
// Default constructor
MAC::MAC(){
musicAlbums = NULL;
noOfMusicAlbums = 0;
}
// Destructor
MAC::~MAC(){
if (noOfMusicAlbums > 0) {
delete [] musicAlbums;
}
}

/**
* @brief Copy Constructor
* @param macToCopy copied MAC
*/
MAC::MAC(const MAC &macToCopy)
:noOfMusicAlbums(macToCopy.noOfMusicAlbums){
if(noOfMusicAlbums > 0) {
// create a new music album with size of macToCopy
musicAlbums = new MusicAlbum[noOfMusicAlbums];
for (int i = 0; i < noOfMusicAlbums; ++i) {
musicAlbums[i] = macToCopy.musicAlbums[i];
}
}
else {
musicAlbums = NULL;
}
}

/**
* @brief Overloaded assignment operator
* @param right music album passed by reference
*/
void MAC::operator=(const MAC &right){
// avoid self-assignment
if ( &right != this ) {
// make their no of music albums equal
noOfMusicAlbums = right.noOfMusicAlbums;
// make sure MAC contains music
if(noOfMusicAlbums > 0){
// free the current music album

delete [] musicAlbums;
musicAlbums = NULL;
// set the left music album to the music album of the right MAC
musicAlbums = new MusicAlbum[noOfMusicAlbums];
for (int i = 0; i < noOfMusicAlbums; ++i) {
musicAlbums[i] = right.musicAlbums[i];
}
}
else {
noOfMusicAlbums = 0;
musicAlbums = NULL;
}
}
}
/**
* @brief Adds a music album to the collection if the album not in the collection
* @param maArtist name of the artist
* @param maTitle name of the album title
* @param maYear year the album published
* @return boolean indicating whether music album in the collection
*/
bool MAC::addMusicAlbum(const string maArtist, const string maTitle, const int maYear) {
// create a new music album with given parameters
MusicAlbum musicAlbum(maArtist, maTitle, maYear);
bool inCollection = true;
// if the music albums has no elements add music album to the music albums
if (noOfMusicAlbums == 0) {
noOfMusicAlbums++;
// initialize the music albums array
musicAlbums = new MusicAlbum[noOfMusicAlbums];
// add the music album to the music albums
musicAlbums[noOfMusicAlbums-1] = musicAlbum;
}
else {
// check if the music album already in the colleciton
for (int i = 0; i < noOfMusicAlbums; i++) {
if (musicAlbums[i].isEqual(musicAlbum)) {
return false;
}
}
// create a template to copy elements of music albums
MusicAlbum *temp = new MusicAlbum[noOfMusicAlbums];
for (int i = 0; i < noOfMusicAlbums; i++) {
temp[i] = musicAlbums[i];
}
// free the music album
delete [] musicAlbums;
musicAlbums = NULL;
// increase the size

noOfMusicAlbums++;
musicAlbums = new MusicAlbum[noOfMusicAlbums];
for (int i = 0; i < noOfMusicAlbums-1; i++) {
musicAlbums[i] = temp[i];
}
musicAlbums[noOfMusicAlbums-1] = musicAlbum;
// free the template
delete [] temp;
}
return inCollection;
}
/**
* @brief Remove a music album from the collection if it is in the collection
* @param maArtist name of the artist
* @param maTitle name of the album title
* @return boolean indicating whether music album in the collection
*/
bool MAC::removeMusicAlbum(const string maArtist, const string maTitle){
bool inCollection = false;
//check if the collection initialized
if (noOfMusicAlbums > 0) {
// create a new music album with given parameters
MusicAlbum musicAlbum(maArtist, maTitle, 0);
// mark the index album found
int idx = -1;
// check if the music album already in the colleciton
for (int i = 0; i < noOfMusicAlbums; i++) {
if (musicAlbums[i].isEqual(musicAlbum)) {
inCollection = true;
idx = i;
}
}
// if it is in the collection remove it
if (inCollection) {
// copy the music albums
MusicAlbum *temp = new MusicAlbum[noOfMusicAlbums];
for (int i = 0; i < noOfMusicAlbums; i++) {
temp[i] = musicAlbums[i];
}
// decrease the number of music albums
noOfMusicAlbums -= 1;
musicAlbums = new MusicAlbum[noOfMusicAlbums];
// construct the music array this time with deleted music album
for (int i = 0; i < idx; i++) {
musicAlbums[i] = temp[i];

}
for (int i = idx + 1; i < noOfMusicAlbums+1; i++) {
musicAlbums[i-1] = temp[i];
}
delete [] temp;
}
}
return inCollection;
}
/**
* @brief returns number of music albums within collection
* @param allMusicAlbums music albums
* @return int number of music albums
*/
int MAC::getMusicAlbums(MusicAlbum *&allMusicAlbums){
allMusicAlbums = new MusicAlbum[noOfMusicAlbums];
for (int i = 0; i < noOfMusicAlbums; i++) {
allMusicAlbums[i] = musicAlbums[i];
}
return noOfMusicAlbums;
}
