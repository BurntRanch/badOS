#include "graphics.h"

void putpixel(int x,int y, int color) {
    unsigned char* screen = (unsigned char*) 0xA0000;
    unsigned where = x*3 + y*2400;
    screen[where] = color & 255;              // BLUE
    screen[where + 1] = (color >> 8) & 255;   // GREEN
    screen[where + 2] = (color >> 16) & 255;  // RED
}