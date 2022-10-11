#include "gthread.h"
#include "gwindow.h"
#include "random.h"
#include <iostream>
#include <string>
using namespace std;
void fillColor(GWindow &, double, double, double, double);

static const double MIN_AREA = 10000;
static const double MIN_EDGE = 20;

/**
 * @brief subdivideCanvas
 * @param x
 * @param y
 * @param width
 * @param height
 */
void subdivideCanvas(GWindow &window, double x, double y, double width, double height) {
    if (width * height < MIN_AREA) {
        fillColor(window, x, y, width, height);
        return;
    }

    if (width > height) {
        double mid = randomReal(MIN_EDGE, width - MIN_EDGE);
        subdivideCanvas(window, x, y, mid, height);
        subdivideCanvas(window, x + mid, y, width - mid, height);
        auto copyColor = window.getColor();
        window.setColor("black");
        window.drawLine(x + mid, y, x + mid, y + height);
        window.setColor(copyColor);
    } else {
        double mid = randomReal(MIN_EDGE, height - MIN_EDGE);
        subdivideCanvas(window, x, y, width, mid);
        subdivideCanvas(window, x, y + mid, width, height - mid);
        auto copyColor = window.getColor();
        window.setColor("black");
        window.drawLine(x, y + mid, x + width, y + mid);
        window.setColor(copyColor);
    }
}

// ********************* 以下代码无需修改 ************************

/**
 * @brief repaintWindow - 重绘窗口
 */
void repaintWindow(GWindow &window) {
    GThread::runOnQtGuiThread([&] { window.repaint(); });
}

/**
 * @brief clear - 清空窗口
 */
void clear(GWindow &window) {
    window.clearCanvasPixels();
    repaintWindow(window);
}

/**
 * @brief fillColor - 设置分区颜色
 * @param x
 * @param y
 * @param width
 * @param height
 */
void fillColor(GWindow &window, double x, double y, double width, double height) {
    window.fillRect(x, y, width, height);
    switch (randomInteger(1, 4)) {
    case 1:
        window.setColor("#fac901");
        break;
    case 2:
        window.setColor("#225095");
        break;
    case 3:
        window.setColor("#dd0100");
        break;
    default:
        window.setColor("#ffffff");
        break;
    }
}

/**
 * @brief studentMain - 主程序
 * @return 
 */
int main() {
    GWindow window;
    window.setExitOnClose(true);
    window.setTitle("Mondrian");

    while (true) {
        clear(window);
        subdivideCanvas(window, 0, 0, window.getWidth(), window.getHeight());
        pause(3000);
    }

    return 0;
}
