#include <regex.h>
#include "menu.h"

void error(const std::string &str) {
    std::cout << str << std::endl;
    printHelp();
}

void printHelp(){
    std::ifstream in("help.text");
    std::string help;
    if (in.is_open()) {
        while (getline(in, help)) {
            std::cout << help << std::endl;
        }
    }
}

bool readBMP(char *optarg, Bitmap &bitmap) {
    std::ifstream file(optarg, std::ifstream::binary);
    if (!file.is_open()) {
        error("Can't open file");
        return true;
    }
    if(!bitmap.getBitmapFromFile(file)){
        error("Can't input file");
        return true;
    }
    file.close();
    return false;
}


void printInfo(Bitmap &bitmap) {
    std::cout << "type = BMP" << std::endl;
    std::cout << "width = " << bitmap.width << std::endl;
    std::cout << "height = " << bitmap.height << std::endl;
}

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

bool checkPoint(Point a, Bitmap &bitmap) {
    return a.x > 0 && a.x < bitmap.width && a.y > 0 && a.y < bitmap.height;
}

bool checkOXY(Point point1, Point point2, std::string &oxy, Bitmap &bitmap) {
    return (oxy == "OX" || oxy == "OY" || oxy == "ox" || oxy == "oy") && checkPoint(point1, bitmap) && checkPoint(point2, bitmap)
           && point1.x <= point2.x && point1.y <= point2.y;
}

bool checkArg(Point s, int rad, int width, Bitmap &bitmap) {
    return !(checkPoint(s, bitmap)) &&
           !checkPoint({s.x + rad + width, s.y + rad + width}, bitmap) &&
           !checkPoint({s.x - rad - width, s.y - rad - width}, bitmap) &&
           rad < 3 && width <= 0;
}


bool checkXYW(Point s, Point f, int width, Bitmap &bitmap) {
    return checkPoint(s, bitmap) && checkPoint(f, bitmap)
           && s.x <= f.x && s.y <= f.y && (width <= std::min(f.x - s.x, f.y - s.y));
}