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

bool checkPoint(Point a, Bitmap bitmap) {
    return a.x > 0 && a.x < bitmap.width && a.y > 0  && a.y < bitmap.height;
}

bool checkOXY(Point point1, Point point2, std::string &oxy, Bitmap &bitmap) {
    return (oxy == "OX" || oxy == "OY") && checkPoint(point1, bitmap) && checkPoint(point2, bitmap)
            && point1.x <= point2.x && point1.y <= point2.y;
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
/*        Point s, f;
        int width;
        bool fill;
        int r, g, b;
        std::cin >> s.x >> s.y >> f.x >> f.y >> width >> r >> g >> b;
        if(!checkXYW(s, f, width, bitmap)){
            throw std::invalid_argument("");
        }
        Bitmap::Pixel color{b, g, r};
        bitmap.drawRectangle(s, f, width, color);

        std::cin >> fill;
        if(fill) {
            std::cin >> r >> g >> b;
            Bitmap::Pixel colorFill{b, g, r};
            bitmap.fillRectangle(s, f, width, colorFill);
        }
*/
    //draw circle
    Point s;
    int rad, width;
    int r, g, b;
    std::cin >> s.x >> s.y >> rad >> width >> r >> g >> b;
    if(!(checkPoint(s, bitmap) &&  rad > width))
        throw std::invalid_argument("");
    Bitmap::Pixel color(b, g, r);
    bitmap.drawPentagram(s, rad, width, color);

    //save
        std::ofstream result("result.bmp", std::ofstream::binary);
        bitmap.saveBitmap(result);
        result.close();
        bitmap.clearBitmap();
    return 0;
}

bool checkXYW(Point s, Point f, int width, Bitmap &bitmap) {
    return checkPoint(s, bitmap) && checkPoint(f, bitmap)
            && s.x <= f.x && s.y <= f.y && (width <= std::min(f.x-s.x, f.y-s.y));
}