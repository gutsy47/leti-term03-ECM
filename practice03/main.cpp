#include "iostream.h"
#include "dos.h"
#include "stdio.h"
#include "conio.h"
#include "math.h"
#include "graphics.h"
#include "string.h"


int GrDriver = DETECT;
int GrMode;
const int DotCount = 10000;
const float RangeStart = 3.14;
const float RangeEnd = 3.14 * 9;


/// Math for drawGraph function
float f(float x) {
    return (float) pow(cos(x/2), 3) - sqrt(x);
}


/// Draw the graph and return max point at the range
float drawGraph(int x1, int y2) {
    float res = f(RangeStart);
    float fMax = res;
    float dx = (RangeEnd - RangeStart) / DotCount;
    for (float x = RangeStart; x <= RangeEnd; x += dx) {
        res = f(x);
        if (res > fMax) fMax = res;
        putpixel(x1 + 10 * x, y2 - 10 * res, YELLOW);
    }
    return fMax;
}


int main() {
    clrscr();

    // Graph init
    initgraph(&GrDriver, &GrMode, "C:\\TurboC3\\BGI");
    auto *grRes = new int (graphresult());
    if (*grRes != grOk) {
    	cputs(grapherrormsg(*grRes));
        cputs("\n\rPress anything to exit...");
        getch();
        return *grRes;
    } else {
	    delete grRes;
    }

    // Windows max cords
    int xMax = getmaxx(),
	    yMax = getmaxy();

    // Edges of a function graph
    int x1 = 30, x2 = xMax - 40,
        y1 = 40, y2 = yMax - 200;

    setlinestyle(SOLID_LINE, 0, THICK_WIDTH); // Border line style
    setcolor(BLUE);                           // Border color
    rectangle(5, 5, xMax - 5, yMax - 5);      // Border

    setcolor(WHITE);                          // Axes color
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);  // Axes line style
    line(x1, y1, x1, y2 + (y2 - y1) / 2);     // y-axis
    line(x2, y2, x1, y2);                     // x-axis

    setcolor(YELLOW);                // Labels style
    outtextxy(x1 - 4, y1 - 20, "Y"); // y-axis label
    outtextxy(x2 + 5, y2 - 3, "X");  // x-axis label
    setcolor(WHITE);

    // Axes values and separators
    int i;
    char iVal[15][2];

    // x-axis
    for (i = 1; i <= 56; ++i) {
        int len = i % 4 == 0 ? 5 : 2;
        line(x1 + 10 * i, y2 + len, x1 + 10 * i, y2 - len);
        if (i % 4 == 0) {
            sprintf(iVal[i / 4 - 1], "%d", i);
            outtextxy(x1 + 10 * i - 3, y2 + 10, iVal[i / 4 - 1]);
        }
    }

    // y-axis
    for (i = -11; i <= 23; ++i) {
        int len = i % 4 == 0 ? 5 : 2;
        line(x1 - len, y2 - 10 * i, x1 + len, y2 - 10 * i);
        if (i % 4 == 0) {
            sprintf(iVal[(i + 11) / 4 - 1], "%d", i);
            outtextxy(x1 - 20, y2 - 10 * i - 3, iVal[(i + 11) / 4 - 1]);
        }
    }

    // Function graph
    float fMax = drawGraph(x1, y2);

    // Print function data
    char cFMax[15];
    sprintf(cFMax, "Max = %f", fMax);
    setcolor(YELLOW);
    outtextxy(30, yMax - 60, "cos(x/2)^3 - sqrt(x)");
    outtextxy(30, yMax - 50, cFMax);

    getch();
    closegraph();

    return 0;
}
