// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "grid.h"
#include "maze.h"
#include "mazegraphics.h"
#include "queue.h"
#include "set.h"
#include "stack.h"
#include "vector.h"
#include "testing/SimpleTest.h"
using namespace std;


/* BRIEF: generateValidMoves
 * PARAM: maze, cur
 * -------------------------
 * Given a start gridelocation, and a maze map information
 * generate all the adjacent gridlocations.
 */
Set<GridLocation> generateValidMoves(Grid<bool>& maze, GridLocation cur) {
    Set<GridLocation> neighbors;
    // create a next grid location set
    GridLocation next;
    // start location is t
    next.row = cur.row;
    next.col = cur.col;
    for (int i = 0; i < maze.numRows(); i++){
        for (int j = 0; j < maze.numCols(); j++){
            if (maze[i][j] == true){
                next.row = i;
                next.col = j;
            }
            if (next.row == cur.row || next.col == cur.col) {
                if (next != cur){
                    if(abs(next.row - cur.row) <= 1 &&
                       abs(next.col - cur.col) <= 1){
                        neighbors += next;
                    }

                }
            }
        }
    }
    return neighbors;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
/* If you find a problem with the path, call error() to report it.
 * If the path is a valid solution, then this function should run to completion
 * without throwing any errors.
 */

void validatePath(Grid<bool>& maze, Stack<GridLocation> path) {
    GridLocation mazeExit = {maze.numRows()-1,  maze.numCols()-1};
    GridLocation mazeBegin = {0 ,0};
    Set<GridLocation> visited_steps = {};
    const int stepsnum = path.size();
        if (path.peek() != mazeExit) {
            error("Path does not end at maze begin");
        }
    for (int every_step_of_path = 0;
         every_step_of_path < stepsnum - 1;
         every_step_of_path++){
            GridLocation cur_step = path.pop();
            GridLocation next_step = path.peek();
            Set<GridLocation> valid_steps = generateValidMoves(maze, cur_step);

            if (visited_steps.contains(cur_step)){
                error("Duplicated steps are provided");
                break;
            }
            if (valid_steps.contains(next_step)){
                visited_steps += cur_step;
            }
            else {
                error("Path provided is not valid");
                break;
            }
    }

    if (path.peek() != mazeBegin) {
        error("Path does not start at maze begin");
    }
}

/* @brief  solveMaze
 * -----------------
 *         given the bool maze, find the way out of the maze;
 * @param  maze
 * @return Stack<GridLocation> path to store the result
 */

Stack<GridLocation> solveMaze(Grid<bool>& maze) {
    MazeGraphics::drawGrid(maze);
    GridLocation               mazeExit = {maze.numRows()-1,  maze.numCols()-1};
    GridLocation               mazeBegin = {0,0};
    Stack<GridLocation>        path; // This is for storing stack to be return.
    Stack<GridLocation>        trials = {mazeBegin}; // Create a stack to store the gridlocation temps. ---> dynamic
    Queue<Stack<GridLocation>> BFS_trials = {trials}; // Add the temps to queue. ---> dynamic
    Set<GridLocation>          visited_steps = {};
//    int max_step = maze.numRows() + maze.numCols();


    while (!BFS_trials.isEmpty()){
        MazeGraphics::highlightPath(trials, "green", 50);
        trials = BFS_trials.dequeue();   //
        GridLocation cur_step = trials.peek();
        if (cur_step == mazeExit){
            path = trials;
            MazeGraphics::highlightPath(path, "green", 50);
            break;
        }
        Set<GridLocation>   valid_steps = generateValidMoves(maze, cur_step);

        for (const GridLocation  &next_step : valid_steps){ // copy valid_steps into next_steps set
                                                            // and test every elements:
                                                            // if not visited, give to trials_copy stack and enqueue
            Stack<GridLocation> trials_copy = trials;

            if (visited_steps.contains(next_step)){
    //            error("Duplicated steps are provided");
                continue;
            }

            else{
                visited_steps += cur_step;
                trials_copy.push(next_step);
                BFS_trials.enqueue(trials_copy);
                }
            }
          }
    return path;
}

/*
 * The given readMazeFile function correctly reads a well-formed
 * maze from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readMazeFile(string filename, Grid<bool>& maze) {
    /* The following code reads data from the file into a Vector
     * of strings representing the lines of the file.
     */
    ifstream in; // hard disk to memory

    if (!openFile(in, filename))
        error("Cannot open file named " + filename);

    Vector<string> lines;
    readEntireFile(in, lines);

    /* Now that the file data has been read into the Vector, populate
     * the maze grid.
     */
    int numRows = lines.size();        // rows is count of lines
    int numCols = lines[0].length();   // cols is length of line
    maze.resize(numRows, numCols);     // resize grid dimensions

    for (int r = 0; r < numRows; r++) {
        if (lines[r].length() != numCols) {
            error("Maze row has inconsistent number of columns");
        }
        for (int c = 0; c < numCols; c++) {
            char ch = lines[r][c];
            if (ch == '@') {        // wall
                maze[r][c] = false;
            } else if (ch == '-') { // corridor
                maze[r][c] = true;
            } else {
                error("Maze location has invalid character: '" + charToString(ch) + "'");
            }
        }
    }
}

/* The given readSolutionFile correctly reads a path from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readSolutionFile(string filename, Stack<GridLocation>& soln) {
    ifstream in;

    if (!openFile(in, filename)) {
        error("Cannot open file named " + filename);
    }

    if (!(in >> soln)) {// if not successfully read
        error("Maze solution did not have the correct format.");
    }
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("generateValidMoves on location in the center of 3x3 grid with no walls") {
    Grid<bool> maze = {{true, true, true},
                       {true, true, true},
                       {true, true, true}};
    GridLocation center = {1, 1};
    Set<GridLocation> expected = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};

    EXPECT_EQUAL(generateValidMoves(maze, center), expected);
}

PROVIDED_TEST("generateValidMoves on location on the side of 3x3 grid with no walls") {
    Grid<bool> maze = {{true, true, true},
                       {true, true, true},
                       {true, true, true}};
    GridLocation side = {0, 1};
    Set<GridLocation> expected = {{0,0}, {0,2}, {1, 1}};

    EXPECT_EQUAL(generateValidMoves(maze, side), expected);
}

PROVIDED_TEST("generateValidMoves on corner of 2x2 grid with walls") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    GridLocation corner = {0, 0};
    Set<GridLocation> expected = {{1, 0}};

    EXPECT_EQUAL(generateValidMoves(maze, corner), expected);
}

PROVIDED_TEST("validatePath on correct solution") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    Stack<GridLocation> soln = { {0 ,0}, {1, 0}, {1, 1} };
    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("validatePath on correct solution loaded from file for medium maze") {
    Grid<bool> maze;
    Stack<GridLocation> soln;
    readMazeFile("res/5x7.maze", maze);
    readSolutionFile("res/5x7.soln", soln);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("validatePath on correct solution loaded from file for large maze") {
    Grid<bool> maze;
    Stack<GridLocation> soln;
    readMazeFile("res/25x33.maze", maze);
    readSolutionFile("res/25x33.soln", soln);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("validatePath on invalid path should raise error") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    Stack<GridLocation> not_end_at_exit = { {1, 0}, {0, 0} };
    Stack<GridLocation> not_begin_at_entry = { {1, 0}, {1, 1} };
    Stack<GridLocation> go_through_wall = { {0 ,0}, {0, 1}, {1, 1} };
    Stack<GridLocation> teleport = { {0 ,0}, {1, 1} };
    Stack<GridLocation> revisit = { {0 ,0}, {1, 0}, {0, 0}, {1, 0}, {1, 1} };

    EXPECT_ERROR(validatePath(maze, not_end_at_exit));
    EXPECT_ERROR(validatePath(maze, not_begin_at_entry));
    EXPECT_ERROR(validatePath(maze, go_through_wall));
    EXPECT_ERROR(validatePath(maze, teleport));
    EXPECT_ERROR(validatePath(maze, revisit));
}

PROVIDED_TEST("solveMaze on file 5x7") {
    Grid<bool> maze;
    readMazeFile("res/5x7.maze", maze);
    Stack<GridLocation> soln = solveMaze(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

//STUDENT_TEST("solveMaze on file 5x7"){
//    Grid<bool> maze;
//    readMazeFile("res/5x7.maze", maze);
//    Stack<GridLocation> soln = solveMaze(maze);
//    EXPECT_EQUAL(soln, {{0,0}});
//}

PROVIDED_TEST("solveMaze on file 21x23") {
    Grid<bool> maze;
    readMazeFile("res/21x23.maze", maze);
    Stack<GridLocation> soln = solveMaze(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

// TODO: add your test cases here
