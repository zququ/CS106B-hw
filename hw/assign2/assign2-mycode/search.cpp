// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "map.h"
#include "search.h"
#include "set.h"
#include "strlib.h"
#include "vector.h"
#include "testing/SimpleTest.h"
#include "simpio.h"
using namespace std;


/*
 * @brief cleanToken
 * -----------------
 *        1. make special char (`ispunct` can recognize) out of input string
 *           from the start of end, but not interval special char.
 *        2. if all the string is composed of special chars, return "".
 *        3. make tolowercase to the returned string.
 *
 * @param `string` s
 * @return s (after modified)
 */


string cleanToken(string s)
{
    string new_s = "";
    string new_s_rev = "";
    int nonalpha_counter = 0;
    bool temp_counter = false;
    bool temp_counter_rev = false;

    if (s == ""){   // if not set, given a s = "" will make death loop.
        s = "";
    }

    else{
        /*
         * @question: Don't know how to use
         *            `const char &items : s`
         *            -----------------------
         *            to write this code to speed up.
         */

        // forward de front few chars which 'ispunct', but not interval chars.
        for (int punct_num = 0; punct_num <= s.length()-1; punct_num ++){
            if (isalpha(s[punct_num]) || isdigit(s[punct_num])){
                new_s += s[punct_num];
                temp_counter = true;
                continue;
            }
            if (ispunct(s[punct_num]) && temp_counter == true){
                new_s += s[punct_num];
            }
        }

        // backward de last few chars which 'ispunct', but not interval chars.
        for (int punct_num_rev = new_s.length(); punct_num_rev >= 0; punct_num_rev --){
            if (isalpha(new_s[punct_num_rev]) || isdigit(new_s[punct_num_rev])){
                new_s_rev += new_s[punct_num_rev];
                temp_counter_rev = true;
                continue;
            }
            if (ispunct(new_s[punct_num_rev]) && temp_counter_rev == true){
                new_s_rev += new_s[punct_num_rev];
            }
        }
        s = toLowerCase(new_s_rev);

        // attention need to reverse the output string
        reverse(s.begin(), s.end());

        // if all chars are not `isalpha()`, return a blank "" to s.
        for (int i_char = 0; i_char <= s.length(); i_char ++){
            if (isalpha(s[i_char])){
                break;
            }
            if (!isalpha(s[i_char])){
                nonalpha_counter ++;
            }
            if (nonalpha_counter == s.length()){
                s = "";
            }
        }
}
    return s;
}

/* @brief gatherTokens
 *        ------------
 *        function to gather all the word after `cleanToken`
 *        need to attention the "" can't be added to the tokens set
 *
 * @params   <string> text
 * @returns Set<string> tokens
 */
Set<string> gatherTokens(string text)
{
    Set<string> tokens;
    Vector<string> v = stringSplit(text, " ");  // stringSplit funciton
                                                // break string into vector<string>

    for (string &word : v){
        string new_word = cleanToken(word);

        if (new_word == ""){   // edge test, avoid "" being added to the token set
            continue;
        }
        else {
            tokens += new_word;
        }
    }

    return tokens;
}

/*
 * @brief buildIndex
 *        ----------
 *        function to build up a Map<string, Set<string>> index,
 *                                                        -----
 * @params                  <string> --> dbfile;
 *         <Map<string, Set<string>> --> index
 *
 * @return line.size()/2 --> which is the size of the database
 */

int buildIndex(string dbfile, Map<string, Set<string>>& index)
{   Set<string> whole_tokens;
    Set<string> specific_url;
    ifstream in;  // hard disk --> to memory in

    if (!openFile(in, dbfile))   // dafile edge test
        error("Cannot open file named " + dbfile);

    Map<string, Set<string>> temp_index;
    Vector<string>           lines;
    readEntireFile(in, lines);   // memory in to 'lines'

    // even lines added to the <Set> --> whole_tokens

    for (int line_num = 1; line_num < lines.size(); line_num += 2){
        whole_tokens += gatherTokens(lines[line_num]);
    }

    // build the Map<string, Set<string>> --> index
    // math every keywords with the Set<website address>
    for (const string &every_keywords : whole_tokens){
         for (int line_num = 1; line_num < lines.size(); line_num += 2){
            if (toLowerCase(lines[line_num]).find(every_keywords) != string::npos){
                index[every_keywords] += lines[line_num - 1];
            }
        }
    }

    return lines.size()/2; // size of the database --> index
}

/*
 * @brief  findQueryMathces
 *         ----------------
 *         function to find the input <string> --> query with the corresponded <Set> --> $$website address$$ respectively.
 *         Need attention the set operations:
 *
 *         `A B` --> set A unionWith B
 *         `A+B` --> set A intersect B
 *         `A-B` --> set A difference B
 *
 * @params Map<string, Set<string>> --> index; string --> query
 * @return the final Set (with only one element) after operation
 */


Set<string> findQueryMatches(Map<string, Set<string>>& index, string query)
{
    Set<string> result;

    Vector<string> despace_query = stringSplit(query, ' ');
    Vector<string> clean_query;
    Vector<Set<string>> web_collection;

    // make space out of the query

    for (const string &every_frac : despace_query){
        clean_query += cleanToken(every_frac);
    }

    // make the website collecion corresponded to every searching keywords.

    for (const string &every_frac2 : clean_query){
        web_collection += index[every_frac2];
    }

    // set operation

    for (int i = 1; i < despace_query.size(); i ++){

        // >> operated
        // A >> B operated to be A --> AB        (A, B in sequence, and #A + 1 = #B)
        // then make B = A = AB

        if (despace_query[i][0] == '+'){
            web_collection[i-1].intersect(web_collection[i]);
            web_collection[i] = web_collection[i-1];

        }
        if (despace_query[i][0] == '-'){
            web_collection[i-1].difference(web_collection[i]);
            web_collection[i] = web_collection[i-1];
        }
        else {
            web_collection[i-1].unionWith(web_collection[i]);
            web_collection[i] = web_collection[i-1];
        }
    }

    result = web_collection[web_collection.size()-1];
    return result;
}

/*
 * @brief searchEngine
 *        ------------
 *        function to carry out the searching egine
 * @params dbfile
 * @return cout the relating result after searching
 *
 */
void searchEngine(string dbfile)
{
    Map<string, Set<string>> index;
    int nPages = buildIndex(dbfile, index);

    cout << "To construct the searchEngine database, need " << nPages << " pages." << endl;
    cout << "There are " << index.size() << " unique elements have been found in this database." << endl;
    Set<string> result;

    while (true){
        string query = getLine("Enter query sentence (RETURN/ENTER to quit): ");

        if (query == "" || query == " "){
            break;
        }

        result = findQueryMatches(index, query);
        cout << "Found " << result.size() << " pages" << endl;
        cout << result << endl;
}

}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("cleanToken on strings with no punctuation at beginning or end") {
    EXPECT_EQUAL(cleanToken("hello"), "hello");
    EXPECT_EQUAL(cleanToken("WORLD"), "world");
    EXPECT_EQUAL(cleanToken("CS*106B"), "cs*106b");
}

PROVIDED_TEST("cleanToken on strings with some punctuation at beginning and end") {
    EXPECT_EQUAL(cleanToken("/hello/"), "hello");
    EXPECT_EQUAL(cleanToken("~woRLD!"), "world");
}

PROVIDED_TEST("cleanToken on non-word strings (no letters)"){
    EXPECT_EQUAL(cleanToken("106"), "");
    EXPECT_EQUAL(cleanToken("~!106!!!"), "");
}

PROVIDED_TEST("gatherTokens from simple string") {
    Set<string> expected = {"go", "gophers"};
    EXPECT_EQUAL(gatherTokens("go go go gophers"), expected);
}

PROVIDED_TEST("gatherTokens correctly cleans tokens") {
    Set<string> expected = {"i", "love", "cs*106b"};
    EXPECT_EQUAL(gatherTokens("I _love_ CS*106B!"), expected);
}

PROVIDED_TEST("gatherTokens from seuss, 5 unique words, mixed case, punctuation") {
    Set<string> tokens = gatherTokens("One Fish Two Fish *Red* fish Blue fish ** 10 RED Fish?");
    EXPECT_EQUAL(tokens.size(), 5);
    EXPECT(tokens.contains("fish"));
    EXPECT(!tokens.contains("Fish"));
}

PROVIDED_TEST("buildIndex from tiny.txt, 4 pages, 11 unique tokens") {
    Map<string, Set<string>> index;
    int nPages = buildIndex("res/tiny.txt", index);
    EXPECT_EQUAL(nPages, 4);
    EXPECT_EQUAL(index.size(), 11);
    EXPECT(index.containsKey("fish"));
}

PROVIDED_TEST("findQueryMatches from tiny.txt, single word query") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRed = findQueryMatches(index, "red");
    EXPECT_EQUAL(matchesRed.size(), 2);
    EXPECT(matchesRed.contains("www.dr.seuss.net"));
    Set<string> matchesHippo = findQueryMatches(index, "hippo");
    EXPECT(matchesHippo.isEmpty());
}

PROVIDED_TEST("findQueryMatches from tiny.txt, compound queries") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}


//// TODO: add your test cases here

STUDENT_TEST("My test1, edge test for cleanToken") {
    EXPECT_EQUAL(cleanToken(""), "");
}

STUDENT_TEST("My test2, nornal test for cleanToken") {
    EXPECT_EQUAL(cleanToken("  I@Love@Myself "), "i@love@myself");
    EXPECT_EQUAL(cleanToken("www.stanford.com"), "www.stanford.com");
}

STUDENT_TEST("My test3, edge test for gatherTokens") {
    Set<string> tokens = gatherTokens("");
    EXPECT_EQUAL(tokens, {});
}

STUDENT_TEST("My test4, edge test for findQueryMatches"){
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    TIME_OPERATION(1, buildIndex("res/website.txt", index));
    Set<string> matchesRedOrFish = findQueryMatches(index, "fish -two +green");
    EXPECT_EQUAL(matchesRedOrFish.size(), 0);

}

STUDENT_TEST("My test5, 3 elements normal test1"){
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "fish green red");
    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
}

STUDENT_TEST("My test6, 3 elements normal test2"){
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "fish -fish red");
    EXPECT_EQUAL(matchesRedOrFish.size(), 2);
}

STUDENT_TEST("My test7, 5 elements normal test1"){
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "fish +bread green -red two");
    EXPECT_EQUAL(matchesRedOrFish.size(), 2);
}
