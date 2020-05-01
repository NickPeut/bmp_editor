#include <regex.h>
#include <getopt.h>
#include "bmp.h"
#include "processings_bmp.h"

bool checkXYW(Point s, Point f, int width, Bitmap &bitmap);

bool isNameCorrect(char *name) {
    bool ans = false;
    regex_t regexPattern;
    regcomp(&regexPattern, "^.*\\.bmp$", REG_EXTENDED);
    regmatch_t regexMatch[3];
    if (regexec(&regexPattern, name, 3, regexMatch, 0) == 0) {
        ans = true;
    }
    regfree(&regexPattern);
    return ans;
}

bool checkOXY(Point point1, Point point2, std::string &oxy, Bitmap &bitmap) {
    return (oxy == "OX" || oxy == "OY") && (point1.x >= 1 && point1.x <= bitmap.width) && (point1.x <= point2.x && point2.x >= 1 && point2.x <= bitmap.width)
           && (point1.y >= 1 && point1.y <= bitmap.height) && (point1.y <= point2.y && point2.y >= 1 && point2.y <= bitmap.height);
}

int main(int argc, char *argv[]) {
    //read
        isNameCorrect(argv[2]);
        std::ifstream file(argv[2], std::ifstream::binary);
        if (!file.is_open()) {
            throw std::invalid_argument("Can't open input file");
        }
        Bitmap bitmap(file);
        file.close();

    //mirror
    /*    Point point1, point2;
        std::string oxy;
        std::cin >> point1.x >> point1.y >> point2.x >> point2.y >> oxy;
        if(!checkOXY(point1, point2, oxy, bitmap)) {
            throw std::invalid_argument("wrong axis!");
        }
        bitmap.mirror(point1, point2, oxy);
    */

    //draw a rectangle
        Point s, f;
        int width;
        bool fill;
        int r, g, b;
        std::cin >> s.x >> s.y >> f.x >> f.y >> width >> r >> g >> b;
        if(!checkXYW(s, f, width, bitmap)){
            throw std::invalid_argument("wrong axis!");
        }
        Bitmap::Pixel color{b, g, r};
        bitmap.drawRectangle(s, f, width, color);

        std::cin >> fill;
        if(fill) {
            std::cin >> r >> g >> b;
            Bitmap::Pixel colorFill{b, g, r};
            bitmap.fillRectangle(s, f, width, colorFill);
        }
    //save
        std::ofstream result("result.bmp", std::ofstream::binary);
        bitmap.saveBitmap(result);
        result.close();
        bitmap.clearBitmap();
    return 0;
}

bool checkXYW(Point s, Point f, int width, Bitmap &bitmap) {
    return (s.x >= 1 && s.x <= bitmap.width) && (s.x <= f.x && f.x >= 1 && f.x <= bitmap.width)
           && (s.y >= 1 && s.y <= bitmap.height) && (s.y <= f.y && f.y >= 1 && f.y <= bitmap.height) &&
           (width <= std::min(f.x-s.x, f.y-s.y));
}