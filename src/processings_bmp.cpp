#include "processings_bmp.h"
#include "bmp.h"
void Bitmap::mirror(Point &point1, Point &point2, std::string &oxy) {
    if(oxy == "OY") {
        for(int x = 0; x <= (point2.x - point1.x) / 2; x++) {
            for(int y = point1.y; y < point2.y; y++) {
                std::swap((picture[y][x + point1.x]), (picture[y][point2.x - x]));
            }
        }
    }
    if(oxy == "OX") {
        for(int x = point1.x; x < point2.x; x++) {
            for(int y = 0; y < (point2.y - point1.y) / 2; y++) {
                std::swap((picture[y + point1.y][x]), (picture[point2.y - y][x]));
            }
        }
    }
    Pixel red;
    red.b = 0;
    red.g = 0;
    red.r = 255;
    picture[point2.y][point2.x] = red;
}
