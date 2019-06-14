#include "MAC.h"
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
// free the memory for the music album
for (int i = 0; i < noOfMusicAlbums; i++) {
musicAlbums[i].clearSongs();
}
delete [] musicAlbums;
} else {
delete musicAlbums;
}
}

/**
* @brief Copy Constructor
* @param macToCopy copied MAC
*/
MAC::MAC(const MAC &macToCopy){
noOfMusicAlbums = macToCopy.noOfMusicAlbums;
if(noOfMusicAlbums > 0) {
// create a new music album with size of macToCopy
musicAlbums = new MusicAlbum[noOfMusicAlbums];
for (int i = 0; i < noOfMusicAlbums; ++i) {
musicAlbums[i] = macToCopy.musicAlbums[i];
}
}
else {
noOfMusicAlbums = 0;
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
// free the memory for the music album
for (int i = 0; i < noOfMusicAlbums; i++) {
musicAlbums[i].clearSongs();
}
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
// free the memory for the music album
for (int i = 0; i < noOfMusicAlbums; i++) {
musicAlbums[i].clearSongs();
}
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
// free the memory for the music album
for (int i = 0; i < noOfMusicAlbums; i++) {
musicAlbums[i].clearSongs();
}
// free the memory for the music album
for (int i = 0; i < noOfMusicAlbums; i++) {
musicAlbums[i].clearSongs();
}
delete [] musicAlbums;
musicAlbums = NULL;

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
/**
* @brief Add a song into the music album. Song name must be unique and music album should
be in the collection
* @param maArtist name of the artist
* @param maTitle name of the title
* @param sName name of the song
* @param sMins name of the minutes
* @param sSecs name of the seconds
* @return added boolean indicating song is added or not
*/
bool MAC::addSong(const string maArtist, const string maTitle,
const string sName, const int sMins,
const int sSecs){
bool addable = false;
// music album with given title and artist name
MusicAlbum musicAlbum(maArtist, maTitle);
// song with the given name, minutes, seconds
Song song(sName, sMins, sSecs);
// remember the index found of the music album
int index = -1;
// check if the music album exist in the collection
if (noOfMusicAlbums > 0) {
for (int i = 0; i < noOfMusicAlbums; i++) {
if(musicAlbums[i].isEqual(musicAlbum)){

addable = true;
index = i;
}
}
}
// continue if the music album in the collection
if(addable){
// check if the song name is unique in the songs of the music album
addable = musicAlbums[index].addSong(sName, sMins, sSecs);
}
return addable;
}
/**
* @brief Clear the song list if the album exist
* @param maArtist name of the artist
* @param maTitle name of the title
* @return removable boolean indicating song is added or not
*/
bool MAC::removeSongs(const string maArtist,
const string maTitle){
bool removable = false;
// create a music album with given parameters
MusicAlbum musicAlbum(maArtist, maTitle);
// mark the index of the music album in the list
int index = -1;
// check if the music album exist in the collection
if (noOfMusicAlbums > 0) {
for (int i = 0; i < noOfMusicAlbums; i++) {
if(musicAlbums[i].isEqual(musicAlbum)){
removable = true;
index = i;
}
}
}
// continue if music album exist
if (removable) {
removable = musicAlbums[index].clearSongs();
}
return removable;
}
/**
* @brief Calculate the average length of songs in the music albums
* @param minutes return value of minutes passed by reference
* @param seconds return value of seconds passed by reference
*/
void MAC::calculateAvgMusicAlbumLength(int &minutes,
int &seconds){
// initialize minutes and second
minutes = 0;
seconds = 0;
// check whether music albums are empty or not
if (noOfMusicAlbums > 0) {
for (int i = 0; i < noOfMusicAlbums; i++) {

int curMinutes = 0;
int curSeconds = 0;
musicAlbums[i].calculateMusicAlbumLength(curMinutes, curSeconds);
minutes += curMinutes;
seconds += curSeconds;
}
// convert everything to seconds
seconds += minutes * 60;
// calculate average running length
seconds = seconds / noOfMusicAlbums;
// convert number of seconds to minutes
int noMinutesInSeconds = seconds / 60;
minutes = noMinutesInSeconds;
// obtain the seconds
seconds = seconds % 60;
}
}
