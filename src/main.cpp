#include <regex.h>
#include <getopt.h>
#include "bmp.h"
#include "processings_bmp.h"

bool checkXYW(Point s, Point f, int width, Bitmap &bitmap);

bool checkArg(Point s, int rad, int width, Bitmap bitmap);

void error(const std::string& str);

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
    Bitmap bitmap;
    std::vector<int> func;

    const char *short_options = "hr:ma:df:u:c:i:l:g:pz:q:jk:b:s:";

    const struct option long_options[] = {
            {"help",             no_argument,       nullptr, 'h'},

            {"read",             required_argument, nullptr, 'r'}, //0

            {"mirror",           no_argument,       nullptr, 'm'}, //1
            {"axis",             required_argument, nullptr, 'a'},

            {"draw_rectangle", no_argument,       nullptr, 'd'}, //2
            {"start",          required_argument, nullptr, 'f'},
            {"finish",         required_argument, nullptr, 'u'},
            {"color_rectangle",  required_argument, nullptr, 'c'},
            {"is_fill",          required_argument, nullptr, 'i'},
            {"color_fill",       required_argument, nullptr, 'l'},
            {"width_line",       required_argument, nullptr, 'g'},

            {"draw_pentagram",   no_argument,       nullptr, 'p'}, //3
            {"center",         required_argument, nullptr, 'z'},
            {"rad",         required_argument, nullptr, 't'},
            {"color_pentagram",  required_argument, nullptr, 'q'},

            {"make_collage",     no_argument,       nullptr, 'j'}, //4
            {"nums",           required_argument, nullptr, 'k'},
            {"picture_list",     required_argument, nullptr, 'b'},

            {"save",             required_argument,       nullptr, 's'} //5
    };


    std::map<std::string, Bitmap::Pixel> colors = {
            {"cyan",  {2, 2, 8}},
            {"black", {0, 0, 0}},
            {"gray", {128, 128, 128}},
            {"white", {255, 255, 255}},
            {"fuchsia", {255, 0, 255}},
            {"purple", {128, 0, 128}},
            {"red", {255, 0, 0}},
            {"maroon", {128, 0, 0}},
            {"yellow", {255, 255, 0}},
            {"olive", {128, 128, 0}},
            {"lime", {0, 255, 0}},
            {"aqua", {0, 255, 255}},
            {"teal", {0, 128, 128}},
            {"blue", {0, 0, 255}},
            {"navy", {0, 0, 128}}
    };
    bool flag_input = false;
    int rez;
    int option_index;
    while ((rez = getopt_long(argc, argv, short_options,
                              long_options, &option_index)) != -1) {
        switch (rez) {
            case 'h': { //help
                //help
                break;
            }
            case 'r': { //read
                if (isNameCorrect(optarg)) {
                    std::ifstream file(optarg, std::ifstream::binary);
                    if (!file.is_open()) {
                        error("Can't open input file");
                        return 0;
                    }
                    bitmap.getBitmapFromFile(file);
                    file.close();
                    flag_input = true;
                    break;
                } else {
                    error("invalid argument in read.");
                    return 0;
                }
            }
            case 's': { //save
                if(!flag_input) {
                    error("You did not enter a input file name");
                    return 0;
                }
                if(!isNameCorrect(optarg)) {
                    error("invalid argument in save");
                    bitmap.clearBitmap();
                    return 0;
                }
                std::ofstream result(optarg, std::ofstream::binary);
                bitmap.saveBitmap(result);
                result.close();
                flag_input = false;
                break;
            }
            case 'm': { //mirror

                if(!flag_input) {
                    error("You did not enter a input file name");
                    return 0;
                }

                int k = 3;
                std::vector<bool> used(3, false);
                std::string axis;
                Point start, finish;

                while (k > 0 && (rez = getopt_long(argc, argv, short_options,
                                          long_options, &option_index)) != -1) {
                    switch (rez) {
                        case 'a': { //OX | OY (axis)
                            if(used[0]) {
                                error("too much argument in mirror, axis");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            axis = optarg;
                            if(axis != "OX" && axis != "ox" && axis != "oy" && axis != "OY") {
                                error("invalid argument in mirror, axis");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            used[0] = true;
                            k--;
                            break;
                        }
                        case 'f': { // "start"
                            if(used[1]) {
                                error("too much argument in mirror, start point");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            try {
                                start.x = std::stoi(strtok(optarg, ",;"));
                                start.y = std::stoi(strtok(optarg, ",;"));
                            }
                            catch (std::exception &e) {
                                error("invalid argument in mirror, start point");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            k--;
                            used[1] = true;
                            break;
                        }
                        case 'u': { // "finish"
                            if(used[2]) {
                                error("too much argument in mirror, finish point");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            try {
                                finish.x = std::stoi(strtok(optarg, ",;"));
                                finish.y = std::stoi(strtok(optarg, ",;"));
                            }
                            catch (std::exception &e) {
                                error("invalid argument in mirror, finish point");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            k--;
                            used[2] = true;
                            break;
                        }
                        case '?':
                        default: {
                            error("invalid command in mirror");
                            bitmap.clearBitmap();
                            return 0;
                        }
                    }
                }
                if(!checkOXY(start, finish, axis, bitmap)) {
                    error("invalid input in mirror");
                    bitmap.clearBitmap();
                    return 0;
                }
                if(bitmap.mirror(start, finish, axis) != 0) {
                    error("invalid input in mirror");
                    bitmap.clearBitmap();
                    return 0;
                }
                break;
            }
            case 'd': { //draw_a_rectangle

                if (flag_input) {
                    int k = 5;
                    std::vector<bool> used(5, false);
                    Point start, finish;
                    bool isFill = false;
                    int width = 0;
                    std::string colorLine, colorFill;
                    while (k != 0 && (rez = getopt_long(argc, argv, short_options,
                                                        long_options, &option_index)) != -1) {
                        switch (rez) {
                            case 'f': { // "start"
                                if (used[0]) {
                                    error("too much argument in rectangle, start point");
                                    bitmap.clearBitmap();
                                    return 0;
                                }
                                try {
                                    start.x = std::stoi(strtok(optarg, ",;"));
                                    start.y = std::stoi(strtok(optarg, ",;"));
                                }
                                catch (std::exception &e) {
                                    error("invalid argument in rectangle, start point");
                                    bitmap.clearBitmap();
                                    return 0;
                                }
                                k--;
                                used[0] = true;
                                break;
                            }
                            case 'u': { // "finish"
                                if (used[1]) {
                                    error("too much argument in rectangle, finish point");
                                    bitmap.clearBitmap();
                                    return 0;
                                }
                                try {
                                    finish.x = std::stoi(strtok(optarg, ",;"));
                                    finish.y = std::stoi(strtok(optarg, ",;"));
                                }
                                catch (std::exception &e) {
                                    error("invalid argument in rectangle, finish point");
                                    bitmap.clearBitmap();
                                    return 0;
                                }
                                k--;
                                used[1] = true;
                                break;

                            }
                            case 'c': { // "color_rectangle"
                                if (used[2]) {
                                    error("too much argument in rectangle, color rectangle");
                                    bitmap.clearBitmap();
                                    return 0;
                                }
                                try {
                                    colorLine = optarg;
                                    if (colors.find(colorLine) == colors.end()) {
                                        throw std::invalid_argument("colorLine");
                                    }
                                }
                                catch (std::exception &e) {
                                    error("invalid argument colorLine in  in rectangle, color rectangle");
                                    bitmap.clearBitmap();
                                    return 0;
                                }
                                k--;
                                used[2] = true;
                                break;
                            }
                            case 'i': { // "is_fill"
                                if (used[3]) {
                                    error("too much argument in rectangle, is fill");
                                    bitmap.clearBitmap();
                                    return 0;
                                }
                                try {
                                    std::string str = optarg;
                                    if (str == "yes" || str == "Yes" || str == "YES") {
                                        isFill = true;
                                        used[3] = true;
                                        break;
                                    } else if (str == "no" || str == "NO" || str == "No") {
                                        k--;
                                        used[3] = true;
                                        break;
                                    } else {
                                        throw std::invalid_argument("");
                                    }
                                }
                                catch (std::exception &e) {
                                    error("invalid argument in rectangle, is fill");
                                    bitmap.clearBitmap();
                                    return 0;
                                }
                            }
                            case 'l': { // "color_fill"
                                if (!isFill) {
                                    error("color fill with false is fill");
                                    bitmap.clearBitmap();
                                    return 0;
                                }
                                if (used[4]) {
                                    error("too much argument in rectangle, color fill");
                                    bitmap.clearBitmap();
                                    return 0;
                                }
                                try {
                                    colorFill = optarg;
                                    if (colors.find(colorFill) == colors.end()) {
                                        throw std::invalid_argument("color fill");
                                    }
                                }
                                catch (std::exception &e) {
                                    error("invalid argument in rectangle, color fill");
                                    bitmap.clearBitmap();
                                    return 0;
                                }
                                k--;
                                used[4] = true;
                                break;
                            }
                            case 'g': { // "width_line"
                                if (used[5]) {
                                    error("too much argument in rectangle, line width");
                                    bitmap.clearBitmap();
                                    return 0;
                                }
                                try {
                                    width = std::stoi(optarg);
                                }
                                catch (std::exception &e) {
                                    error("invalid argument in rectangle, line width");
                                    bitmap.clearBitmap();
                                    return 0;
                                }
                                k--;
                                break;
                            }
                            case '?':
                            default: {
                                error("invalid option in rectangle");
                                std::cout << optarg;
                                bitmap.clearBitmap();
                                return 0;
                            }
                        }
                    }
                    if (!checkXYW(start, finish, width, bitmap)) {
                        error("invalid argument in rectangle");
                        bitmap.clearBitmap();
                        return 0;
                    }
                    bitmap.drawRectangle(start, finish, width, colors[colorLine]);
                    if (isFill) bitmap.fillRectangle(start, finish, width, colors[colorFill]);
                    break;
                } else {
                    error("You did not enter a input file name");
                    return 0;
                }
            }
            case 'p': { // "draw_pentagram"
                if(!flag_input) {
                    error("You did not enter a input file name");
                    return 0;
                }
                int k = 4;
                std::vector<bool> used(k, false);
                int rad = 0;
                int width = 0;
                Point center;
                std::string color;

                while (k != 0 && (rez = getopt_long(argc, argv, short_options,
                                          long_options, &option_index)) != -1) {
                    switch (rez) {
                        case 'g': { // "width_line"
                            if(used[0]) {
                                error("too much argument in pentagram, line width");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            try {
                                width = std::stoi(optarg);
                            }
                            catch (std::exception &e) {
                                error("invalid argument in pentagram, line width");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            used[0] = true;
                            k--;
                            break;
                        }
                        case 'z': { // "center"
                            if(used[1]) {
                                error("too much argument in pentagram, center point");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            try {
                                center.x = std::stoi(strtok(optarg, ",;"));
                                center.y = std::stoi(strtok(optarg, ",;"));
                            }
                            catch (std::exception &e) {
                                error("invalid argument in pentagram, center point");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            k--;
                            used[1] = true;
                            break;
                        }
                        case 't': { // "radius"
                            if(used[2]) {
                                error("too much argument in pentagram, radius");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            try {
                                rad = std::stoi(optarg);
                            }
                            catch (std::exception &e) {
                                error("invalid argument in pentagram, radius");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            k--;
                            used[2] = true;
                            break;
                        }
                        case 'q': { // "color_pentagram"
                            if(used[3]) {
                                error("too much argument in pentagram, color");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            try {
                                color = optarg;
                                if(colors.find(color) == colors.end()) {
                                    throw std::invalid_argument("");
                                }
                            }
                            catch (std::exception &e) {
                                error("invalid argument in pentagram, color");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            k--;
                            used[3] = true;
                            break;
                        }
                        case '?':
                        default: {
                            error("found unknown option in pentagram");
                            bitmap.clearBitmap();
                            return 0;
                        }
                    }
                }
                if(checkArg(center, rad, width, bitmap)) {
                    error("invalid argument in pentagram");
                    bitmap.clearBitmap();
                    return 0;
                }
                bitmap.drawPentagram(center, rad, width, colors[color]);
                break;
            }


            case 'j': { // "make_collage"
                if(!flag_input) {
                    error("logic error");
                    return 0;
                }
                flag_input = true;
                int k = 2;
                std::vector<bool> used(k, false);
                int n = 0, m = 0;
                std::vector<char*> names;
                bool flagNM = false;
                while (k != 0 && (rez = getopt_long(argc, argv, short_options,
                                          long_options, &option_index)) != -1) {
                    switch (rez) {
                        case 'b': { // "picture_list"
                            if(!flagNM) {
                                error("You did not enter a input numbers");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            if(used[1]) {
                                error("too much argument in collage, pictures list");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            try {
                                int count = 0;
                                char *name = strtok(optarg, ",;");
                                while (count != n * m && name != nullptr) {
                                    if(!isNameCorrect(name)) {
                                        error("invalid name in name lost for collage");
                                        bitmap.clearBitmap();
                                        return 0;
                                    }
                                    names.push_back(name);
                                    name = strtok(nullptr, ",;");
                                    count++;
                                }
                            }
                            catch(std::exception &e){
                                error("invalid argument in make collage in list");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            k--;
                            used[1] = true;
                            break;
                        }

                        case 'k': { // "n, m"
                            if(used[0]) {
                                error("too much argument in collage, numbers");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            try {
                                n = std::stoi(strtok(optarg, ",;"));
                                m = std::stoi(strtok(optarg, ",;"));
                            }
                            catch (std::exception &e) {
                                error("invalid argument in collage, numbers");
                                bitmap.clearBitmap();
                                return 0;
                            }
                            flagNM = true;
                            k--;
                            used[0] = true;
                            break;
                        }
                        case '?':
                        default: {
                            error("found unknown option in collage");
                            bitmap.clearBitmap();
                            return 0;
                        }
                    }
                }
                std::vector<Bitmap> images;
                try {
                    for (int i = 0; i < n * m; i++) {
                        std::ifstream file(names[i], std::ifstream::binary);
                        if (!file.is_open()) {
                            std::cout << "names " << names[i] << std::endl;
                            throw std::invalid_argument("Can't open input file");
                        }
                        Bitmap image(file);
                        images.emplace_back(image);
                        file.close();
                    }
                }
                catch(std::exception &e) {
                    error("make_collage error");
                    bitmap.clearBitmap();
                    return 0;
                }
                bitmap.makeCollage(images, n, m);
                for(int i = 0; i < n*m; i++) {
                    images[i].clearBitmap();
                }
                break;
            }
            case '?': {
                error("found unknown option");
                bitmap.clearBitmap();
                return 0;
            }
            default: {
                error("found unknown option");
                bitmap.clearBitmap();
                return 0;
            }
        }
    }
    bitmap.clearBitmap();
    return 0;
}

void error(const std::string& str) {
    std::cout << str << std::endl;
}

bool checkArg(Point s, int rad, int width, Bitmap bitmap) {
    return !(checkPoint(s, bitmap)) &&
        !checkPoint({s.x + rad + width,s.y + rad + width}, bitmap) &&
            !checkPoint({s.x - rad - width,s.y - rad - width}, bitmap) &&
                rad < 3 && width <= 0;
}


bool checkXYW(Point s, Point f, int width, Bitmap &bitmap) {
    return checkPoint(s, bitmap) && checkPoint(f, bitmap)
            && s.x <= f.x && s.y <= f.y && (width <= std::min(f.x-s.x, f.y-s.y));
}