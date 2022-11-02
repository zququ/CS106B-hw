#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "backtracking.h"
#include "gridlocation.h"
#include "grid.h"
#include "set.h"
#include "lexicon.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * @describtion 1. using Grid<char> to represent the coreBoard
 *              2. every place is an alphabet cubic, and the alphabet value
 *                 --> alphabet at the top of the alphabet cubic
 *              3. the word should be at least 4 alphabets long
 *              4. alphabets spelled word shold be an effective a word which can
 *                 be found in the given English word list
 *              5. words can be found by tracking the adjacent alphabet cubics,
 *                 but only one single cubic can be choosen once.
 *              6. alphbets on the cubic can be tracked through 4 baselines -->
 *                 (up, down, left, right) and 4 diagonals, 3-8 neighbours in total.
 *              7. words can't be scored repeatly, only can be socored once.
 *              8. words are socred by the length:
 *                  <= 3 alphabets --> invalid/ 0 score
 *                     4 alphabets --> 1 score
 *                     5 alphabets --> 2 scores
 *                     ...
 * @guide       #Backtracking: from each of 16 alphabet cubics, beginning to search
 *                             every cubic, search every paths from the start recursively
 *                             and track the neighbour cubics.
 *              #labeling    : you don't want to explore the same alphabet cubic twice, so
 *                             you need some method to label if have visited this cubic.
 * @attention   1. use ADT, attention for if ADT is efficient.
 *              2. EnlishWords.txt includes 125 thousand words, which is enough
 *              3. the code includs some prototype or test example, you can test the helper
 *                 function with them. You can use any helper function or packing function,
 *                 however, scoreBoard fucntion should be used completedly match the prototype
 *                 above.
 *              4. need to attention for efficiency
 *              5. explicit, using contiansPrefix function.
 */

/*
 * @brief 	 	points()
 * ---------------------
 * @description input a string and return the points (score)
 * @params		<string> str
 * @return 		<int> points (score)
 */

int points(string str) {
    if(str.length() < 3){
        return 0;
    } else {
        return str.length() - 3;
    }
}

/*
 * @brief 	 	cor2loc()
 * ----------------------
 * @description input a grid coordinate and return the <GridLocation>
 * @params		Vector<int> cor
 * @return 		<GridLocation>
 */

GridLocation cor2loc(Vector<int> cor){
    GridLocation loc;
    loc.row = cor[0];
    loc.col = cor[1];
    return loc;
}

 /*
 * @brief 	 	valid_step()
 * -------------------------
 * @description given one <GridLocation> loc, return the <Set> valid next steps (<GridLocation>)
 * @params		Grid<char> board, <GridLoction> loc
 * @return 		a Set <GridLocation> of all the valid next steps
 */

Set<GridLocation> validNext(Grid<char>& board, GridLocation loc){
    Vector<GridLocation> next_step = {cor2loc({loc.row-1, loc.col-1}),
                                      cor2loc({loc.row-1, loc.col  }),
                                      cor2loc({loc.row-1, loc.col+1}),
                                      cor2loc({loc.row  , loc.col-1}),
                                      cor2loc({loc.row  , loc.col+1}),
                                      cor2loc({loc.row+1, loc.col-1}),
                                      cor2loc({loc.row+1, loc.col  }),
                                      cor2loc({loc.row+1, loc.col+1})};
    Set<GridLocation> valid_step;
    for (const GridLocation& item : next_step){
        if (board.inBounds(item) && board.get(item) != '_'){
                valid_step.add(item);
    }
}
    return valid_step;
}

/*
 * @brief       scoreBoard()
 * -------------------------
 * @discription
 * @params      <Grid<char>> board, <Lexicon> lex
 * @return      The total score of the spelled words
 */

int scoreBoardRec(Grid<char>& board, Lexicon& lex, string soFar, Set <GridLocation> visited_loc,
                  Set <string> &visited_words,GridLocation loc){
    int result = 0;
    // base 1:
    if (!lex.containsPrefix(soFar))
    {
        return 0;
    }
    // common operation
    soFar += board[loc];
    visited_loc += loc;
    // base 2: soFar in lex and no duplication
    if (lex.contains(soFar) && !visited_words.contains(soFar))
    {
        result += points(soFar);
        visited_words += soFar;
    }
    // word forming
    for (auto &elems : validNext(board, loc))
    {
        if (!visited_loc.contains(elems))
        {
            result += scoreBoardRec(board, lex, soFar, visited_loc, visited_words, elems);
        }
    }
    // return to last state for next rec
    soFar.erase(soFar.size() -1);
    visited_loc.remove(loc);
    // final return
    return result;
}

int scoreBoard(Grid<char>& board, Lexicon& lex) {
    int result = 0;
    string soFar = "";
    Set <GridLocation> visited_loc;
    Set <string> visited_words = {};

    for (const GridLocation &locations : board.locations())
    {
        if (board[locations] != '_')
        {
        result += scoreBoardRec(board, lex, soFar, visited_loc, visited_words, locations);
        }
    }
    return result;
}

/* * * * * * Test Cases * * * * * */

/* Test helper function to return shared copy of Lexicon. Use to
 * avoid (expensive) re-load of word list on each test case. */
static Lexicon& sharedLexicon() {
    static Lexicon lex("res/EnglishWords.txt");
    return lex;
}

PROVIDED_TEST("Load shared Lexicon, confirm number of words") {
    Lexicon lex = sharedLexicon();
    EXPECT_EQUAL(lex.size(), 127145);
}

PROVIDED_TEST("Test point scoring") {
    EXPECT_EQUAL(points("and"), 0);
    EXPECT_EQUAL(points("quad"), 1);
    EXPECT_EQUAL(points("quint"), 2);
    EXPECT_EQUAL(points("sextet"), 3);
    EXPECT_EQUAL(points("seventh"), 4);
    EXPECT_EQUAL(points("supercomputer"), 10);
}

PROVIDED_TEST("Test scoreBoard, board contains no words, score of zero") {
    Grid<char> board = {{'B','C','D','F'}, //no vowels, no words
                        {'G','H','J','K'},
                        {'L','M','N','P'},
                        {'Q','R','S','T'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 0);
}

PROVIDED_TEST("Test scoreBoard, board contains one word, score of 1") {
    Grid<char> board = {{'C','_','_','_'},
                        {'Z','_','_','_'},
                        {'_','A','_','_'},
                        {'_','_','R','_'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
}

PROVIDED_TEST("Test scoreBoard, alternate paths for same word, still score of 1") {
    Grid<char> board = {{'C','C','_','_'},
                        {'C','Z','C','_'},
                        {'_','A','_','_'},
                        {'R','_','R','_'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
}

PROVIDED_TEST("Test scoreBoard, small number of words in corner of board") {
    Grid<char> board = {{'L','I','_','_'},
                        {'M','E','_','_'},
                        {'_','S','_','_'},
                        {'_','_','_','_'}};
    Set<string> words = {"SMILE", "LIMES", "MILES", "MILE", "MIES", "LIME", "LIES", "ELMS", "SEMI"};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()),  2 + 2 + 2 + 1 + 1 + 1 + 1 + 1 + 1);
}

PROVIDED_TEST("Test scoreBoard, full board, small number of words") {
    Grid<char> board = {{'E','Z','R','R'},
                        {'O','H','I','O'},
                        {'N','J','I','H'},
                        {'Y','A','H','O'}};
    Set<string> words = { "HORIZON", "OHIA", "ORZO", "JOHN", "HAJI"};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 4 + 1 + 1 + 1 + 1);
}

STUDENT_TEST("My easy test") {
    Grid<char> board = {{'A', 'P', 'P', 'L', 'E'}};
    Set<string> words = {"APPLE"};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 2);
}

PROVIDED_TEST("Test scoreBoard, full board, medium number of words") {
    Grid<char> board = {{'O','T','H','X'},
                        {'T','H','T','P'},
                        {'S','S','F','E'},
                        {'N','A','L','T'}};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 76);
}

PROVIDED_TEST("Test scoreBoard, full board, large number of words") {
    Grid<char> board = {{'E','A','A','R'},
                        {'L','V','T','S'},
                        {'R','A','A','N'},
                        {'O','I','S','E'}};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 234);
}
