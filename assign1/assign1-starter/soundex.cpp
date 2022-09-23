/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
#include <iostream>
#include <cstring>
using namespace std;

/* This function is intended to return a string which
 * contains only the letter characters from the original
 * (all non-letter characters are removed)
 *
 * WARNING: The provided code is buggy!
 * First of the inputs can't be a char.
 * ------------------------------------
 * make a while loop to force first char to be the first
 * number.
 */

//A program to output the firt caption of
//the input string.
//getCap
//------


char getCap(string s) {
    char CAP = s[0];
    return CAP;
}

string removeNonLetters(string s) {
    long num = 1;
    while(true){
        if (!isalpha(s[0])){
            s[0] = s[num];
            s[num] = '@';
            num++;
            }
        if (isalpha(s[0])){
            break;
        }
    }
    string result = charToString(s[0]);
    for (int i = 1; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

string soundexCoding(string s){
    for (long pos = 0; pos < s.length(); pos++){
        switch (toupper(s[pos])){
            case 'A': case 'E': case 'I': case 'O': case 'U': case 'H': case 'W': case 'Y':
                s[pos] = '0';
            break;
            case 'B': case 'F': case 'P': case 'V':
                s[pos] = '1';
            break;
            case 'C': case 'G': case 'J': case 'K': case 'Q': case 'S': case 'X': case 'Z':
                s[pos] = '2';
            break;
            case 'D': case 'T':
                s[pos] = '3';
            break;
            case 'L':
                s[pos] = '4';
            break;
            case  'M': case 'N':
                s[pos] = '5';
            break;
            case 'R':
                s[pos] = '6';
            break;
        }
        }
    return s;
}

//kick the fucking duplexes out of my string.
//-------------------------------------------

string stringDePlex(string s){
    string result = charToString(s[0]);
    for (long pos = 1; pos < s.length(); pos++){
        if (s[pos]!=s[pos-1]){
            result += s[pos];
        }
    }
    return result;
}

//reslove the zero problems.
//--------------------------

string zeroProblem(string s){
    string result = charToString(s[0]);
    for (long pos = 1; pos < s.length(); pos++){
        if (s[pos]!='0'){
            result += s[pos];
        }
    }
    return result;
}

//Add enough zeros
//________________

string addZeros(string s){
    if (s.length() < 4){
        while (true){
            s += '0';
            if (s.length() == 4){
                break;
        }
        }
    }
   else if (s.length() >= 4){
        s = s.substr(0,4);
        }
    return s;
}



/* main program, output the coded NAME input.
 * __________________________________________
 * including a line to make the first alphabet
 * uppercase.
 */
string soundex(string s) {
    string result = addZeros(zeroProblem(stringDePlex(soundexCoding(removeNonLetters(s)))));
    result[0] = toupper(getCap(s));
    return result;
}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    // The names in the database are now stored in the provided
    // vector named databaseNames
    /* TODO: Fill in the remainder of this function. */
    char name[256];
    cout << "Enter a surname (RETURN to quit): ";
    cin.getline(name, 256);
    string nameInput = soundex(name);
    cout << "Soundex code is: " << nameInput << endl;
    databaseNames.sort();
    cout << "Matches from database: {";
    vector<string> new_vector;
    for (unsigned int i = 0; i < databaseNames.size(); i++){
        if (soundex(databaseNames[i]) == nameInput) {
            cout << databaseNames[i] << ", ";
        }
    }
    cout << "\b\b}";
}

/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

//// TODO: add your test cases here
//// character at 1st place will induce error
PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "@A";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "A");
}
