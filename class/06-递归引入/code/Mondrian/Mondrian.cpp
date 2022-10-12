#include "gthread.h"
#include "gtypes.h"
#include "gwindow.h"
#include <iostream>
#include <string>
using namespace std;

static const double MAX_ORDER = 10;

#define subdivideCanvas1
#ifdef subdivideCanvas1

void subdivideCanvas(GWindow &window, double x, double y, double width, double height, int order) {
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
        subdivideCanvas(window, x, y, mid, height, order - 1);
        subdivideCanvas(window, x + mid, y, width - mid, height, order - 1);
    } else {
        // 在长边取一个分割点
        double mid = 0.618 * width;
        // 画线将大矩形分割为两个小矩形
        window.drawLine(x, y + mid, x + width, y + mid);
        // 对两个小矩形继续分割，同时控制复杂度 order
        subdivideCanvas(window, x, y, width, mid, order - 1);
        subdivideCanvas(window, x, y + mid, width, height - mid, order - 1);
    }
}
#endif


#ifdef subdivideCavas2
void subdivideCanvas(GWindow &window, double x, double y, double width, double height, int order) {
    if (width > height){
        double mid = 0.618 * width;

        window.drawLine(x + mid, y, x + mid, y + height);

        subdivideCanvas(window, x, y, mid, height, order - 1);
        subdivideCanvas(window, x + mid, y, width - mid, height, order-1);
    }

    else {
        double mid = 0.618 * width;

        window.drawLine(x, y + mid, x + width, y + mid);

        subdivideCanvas(window, x, y, width, mid, order - 1);
        subdivideCanvas(window, x, y + mid, width, height -mid, order -1);
    }
}

#endif

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
            string text = string("Order ") + integerToString(order);
            window.drawString(text, 5, window.getHeight() - 5);
            subdivideCanvas(window, 0, 0, window.getWidth(), window.getHeight(), order);
            pause(3000);

        }
    }

    return 0;
}
