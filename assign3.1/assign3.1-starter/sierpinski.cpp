/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include "recursion.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * This function draws a filled, black triangle on the provided GWindow
 * that is defined by the corner GPoints one, two, and three. This
 * function has been provided for you and does not need to be modified.
 */
void fillBlackTriangle(GWindow& window, GPoint one, GPoint two, GPoint three) {
    window.setColor("black");
    window.fillPolygon( {one, two, three} );
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
int drawSierpinskiTriangle(GWindow& window, GPoint one, GPoint two, GPoint three, int order) {
    /* TODO: Implement this function. */
    GPoint   mid_one(double mid_x, double mid_y);
    GPoint   mid_two(double mid_x, double mid_y);
    GPoint mid_three(double mid_x, double mid_y);

    mid_one.mid_x = 1/2 * (one.x + two.x);
    mid_one.mid_y = 1/2 * (one.y + two.y);
    mid_two.mid_x = 1/2 * (two.x + two.y);
    mid_two.mid_y = 1/2 * (two.y + two.y);
    mid_three.mid_x = 1/2 * (three.x + three.x);
    mid_three.mid_y = 1/2 * (three.y + three.y);

    fillBlackTriangle(window, one, mid_one, mid_two);
    return 0;
}


/* * * * * * Test Cases * * * * * */

/*
 * Do not modify the code beyond this line! There are no
 * unit tests for this problem. You should do all testing
 * via the interactive demo.
 */

PROVIDED_TEST("Test fractal drawing interactively using graphical demo") {
    runInteractiveDemo();
}

