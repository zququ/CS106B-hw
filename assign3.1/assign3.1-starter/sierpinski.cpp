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

    GPoint mid_one;
    GPoint mid_two;
    GPoint mid_three;

    if (order==0){
        fillBlackTriangle(window, one, two, three);
        return 0;
    }

    mid_one = {0.5 * (one.x + two.x), 0.5 * (one.y + two.y)};
    mid_two = {0.5 * (one.x+three.x), 0.5 * (one.y + three.y)};
    mid_three = {0.5 * (two.x + three.x), 0.5 * (two.y + three.y)};

    return     drawSierpinskiTriangle(window, one, mid_one, mid_two, order - 1) +
               drawSierpinskiTriangle(window, mid_one, two, mid_three, order - 1) +
               drawSierpinskiTriangle(window, mid_two, mid_three, three, order - 1);

    return 1;
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

