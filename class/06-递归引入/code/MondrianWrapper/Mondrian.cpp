#include "gthread.h"
#include "gtypes.h"
#include "gwindow.h"
#include <iostream>
#include <string>
using namespace std;

static const double MAX_ORDER = 10;

// Recursive Function
void subdivideCanvasRec(GWindow &window, double x, double y, double width, double height, int order) {
    // 用阶定义复杂度
    if (order == 0) {
        return;
    }
    // 判断长短边
    if (width > height) {
        // 在长边取一个分割点
        double mid = 0.618 * width;
        // 画线将大矩形分割为两个小矩形
        window.drawLine(x + mid, y, x + mid, y + height);
        // 对两个小矩形继续分割，同时控制复杂度 order
        subdivideCanvasRec(window, x, y, mid, height, order - 1);
        subdivideCanvasRec(window, x + mid, y, width - mid, height, order - 1);
    } else {
        // 在长边取一个分割点
        double mid = 0.618 * width;
        // 画线将大矩形分割为两个小矩形
        window.drawLine(x, y + mid, x + width, y + mid);
        // 对两个小矩形继续分割，同时控制复杂度 order
        subdivideCanvasRec(window, x, y, width, mid, order - 1);
        subdivideCanvasRec(window, x, y + mid, width, height - mid, order - 1);
    }
}

// Wrapper Function
void subdivideCanvas(GWindow &window, int order) {
    subdivideCanvasRec(window, 0, 0, window.getWidth(), window.getHeight(), order);
}

// ************************ 以下代码无需修改 ******************************

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

int main() {
    GWindow window;
    window.setExitOnClose(true);
    window.setTitle("Mondrian");
    window.setColor("BLACK");

    while (true) {
        for (int order = 0; order < MAX_ORDER; order++) {
            clear(window);
            window.drawString(string("Order ") + integerToString(order), 5, window.getHeight() - 5);
            subdivideCanvas(window, order);
            pause(3000);
        }
    }

    return 0;
}
