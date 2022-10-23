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

/**
 * @brief generateValidMoves - 生成下一步可行的位置坐标集合
 * @param maze
 * @param cur
 * @return 位置坐标集合
 */
Set<GridLocation> generateValidMoves(Grid<bool>& maze, GridLocation cur) {
    Set<GridLocation> neighbors;
    /* TODO: Fill in the remainder of this function. */
    GridLocation next;

    // 用 inBounds 接口，减少使用底层代码：row+1 col-1 等等 ###


    // 定义四个变量

    // 判断 inbounds

    // 判断 wall/false

    next = GridLocation(cur.row - 1, cur.col);
    if (maze.inBounds(next) && maze[next]) // 是否在地图内？是否是通道？
        neighbors.add(next);
    next = GridLocation(cur.row, cur.col - 1);
    if (maze.inBounds(next) && maze[next])
        neighbors.add(next);
    next = GridLocation(cur.row + 1, cur.col);
    if (maze.inBounds(next) && maze[next])
        neighbors.add(next);
    next = GridLocation(cur.row, cur.col + 1);
    if (maze.inBounds(next) && maze[next])
        neighbors.add(next);

    return neighbors;
}

#define VALIDATEPATH_V1
#ifdef VALIDATEPATH_V2 // 作业测试
void validatePath(Grid<bool> &maze, Stack<GridLocation> path) {

}
#endif
#ifdef VALIDATEPATH_V1 // My Soln
/**
 * @brief validatePath - 验证路径
 * @param maze
 * @param path
 */
void validatePath(Grid<bool>& maze, Stack<GridLocation> path) {
    GridLocation mazeExit = {maze.numRows()-1,  maze.numCols()-1};

    // 判断 path 顶端是否等于 exit
    // 定义 一个 ADT 存放 visited
    // 循环操作：
        // 取出栈顶，pop， 通过 pop计算 generateValidMoves
        // peek 是否在 generateValidMoves
        // 判断是否在 visited 里面
        // 不重复则添加到 visited 里面

    // 判断起点

    if (path.peek() != mazeExit) {
        error("路径不是在终点结束");
    }

    /* TODO: Fill in the remainder of this function. */
    Set<GridLocation> visited;
    Set<GridLocation> neighbors;
    GridLocation cur = path.pop();
    GridLocation next;
    while (!path.isEmpty()) {
        // 取出下一个位置
        next = path.pop();
        // 判断下一个位置是否可行
        neighbors = generateValidMoves(maze, cur);
        if (!neighbors.contains(next))
            error("路径堵塞，无法通行");
        // 记录走过的位置，防止回头
        if (!visited.contains(cur))
            visited.add(cur);
        else
            error("路径中有回头路");
        // 切换当前位置
        cur = next;
    }

    GridLocation mazeEntry = {0, 0};
    if (cur != mazeEntry) {
        error("路径不是从起点开始");
    }
}
#endif

STUDENT_TEST("validatePath 临界情况") {
    Grid<bool> maze = {{true}};
    Stack<GridLocation> revisit = {{0, 0}};
    EXPECT_NO_ERROR(validatePath(maze, revisit));

    maze = {{true, true}};
    revisit = {{0, 0}, {0, 1}};
    EXPECT_NO_ERROR(validatePath(maze, revisit));
}

STUDENT_TEST("validatePath 原地踏步路径") {
    Grid<bool> maze = {{true, false}, {true, true}};
    Stack<GridLocation> revisit = {{0, 0}, {0, 0}, {1, 0}, {1, 1}};
    Stack<GridLocation> revisit2 = {{0, 0}, {1, 0}, {1, 0}, {1, 1}};

    EXPECT_ERROR(validatePath(maze, revisit));
    EXPECT_ERROR(validatePath(maze, revisit2));
}

STUDENT_TEST("generateValidMoves 绕圈") {
    Grid<bool> maze = {{true, true, true}, {true, true, true}, {true, true, true}};
    Stack<GridLocation> revisit
        = {{0, 0}, {1, 0}, {1, 1}, {1, 2}, {0, 2}, {0, 1}, {1, 1}, {2, 1}, {2, 2}};

    EXPECT_ERROR(validatePath(maze, revisit));
}

/**
 * @brief gatherVisited - 获取当前路径中的所有位置
 * @param path
 * @return 以集合形式返回
 */
Set<GridLocation> gatherVisited(Stack<GridLocation> path) {
    Set<GridLocation> visited;
    while (!path.isEmpty()) {
        visited.add(path.pop());
    }
    return visited;
}

#define SOLVEMAZE_V2
#ifdef SOLVEMAZE_V2 // My Soln
/**
 * @brief solveMaze
 * @param maze
 * @return 
 */
Stack<GridLocation> solveMaze(Grid<bool>& maze) {
    MazeGraphics::drawGrid(maze);
    Stack<GridLocation> path;
    /* TODO: Fill in the remainder of this function. */
    GridLocation mazeExit = {maze.numRows() - 1, maze.numCols() - 1};

    // 初始化带查询路径的任务队列
    Stack<GridLocation> initPath = {{0, 0}};
    Queue<Stack<GridLocation>> todo = {initPath};

    // 如果任务队列不为空，则一直查找
    while (!todo.isEmpty()) {
        // 取出优先查找的路径
        path = todo.dequeue();
        MazeGraphics::highlightPath(path, "GREEN", 100);
        // 如果已经到达出口，结束查询
        if (path.peek() == mazeExit)
            break;
        // 找出接下来的可选位置
        auto neighbers = generateValidMoves(maze, path.peek());
        // 创建新的带查询路径放入任务队列
        for (const auto &pos : neighbers) {
            if (!gatherVisited(path).contains(pos)) { // 避免回头
                auto copyPath = path;
                copyPath.push(pos);
                todo.enqueue(copyPath);
            }
        }
    }

    return path;
}
#endif

#ifdef SOLVEMAZE_V1 // Stanford Method
/**
 * @brief solveMaze
 * @param maze
 * @return 
 */
Stack<GridLocation> solveMaze(Grid<bool> &maze) {
    MazeGraphics::drawGrid(maze);
    Stack<GridLocation> path;
    /* TODO: Fill in the remainder of this function. */
    GridLocation mazeExit = {maze.numRows() - 1, maze.numCols() - 1};

    // 初始化带查询路径的任务队列
    Stack<GridLocation> initPath = {{0, 0}};
    Queue<Stack<GridLocation>> todo = {initPath};

    Set<GridLocation> visited = {{0, 0}}; // 记录访问过的位置

    // 如果任务队列不为空，则一直查找
    while (!todo.isEmpty()) {
        // 取出优先查找的路径
        path = todo.dequeue();
        MazeGraphics::highlightPath(path, "GREEN", 100);
        // 如果已经到达出口，结束查询
        if (path.peek() == mazeExit)
            break;
        // 找出接下来的可选位置
        auto neighbers = generateValidMoves(maze, path.peek());
        // 创建新的带查询路径放入任务队列
        for (const auto &pos : neighbers) {
            if (!visited.contains(pos)) { // 避免回头
                auto copyPath = path;
                copyPath.push(pos);
                todo.enqueue(copyPath);
                visited.add(pos);
            }
        }
    }

    return path;
}
#endif

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
    ifstream in;

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

PROVIDED_TEST("solveMaze on file 21x23") {
    Grid<bool> maze;
    readMazeFile("res/21x23.maze", maze);
    Stack<GridLocation> soln = solveMaze(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

// TODO: add your test cases here
