#include <regex.h>
#include <getopt.h>
#include "bmp.h"
#include "processings_bmp.h"

bool checkXYW(Point s, Point f, int width, Bitmap &bitmap);

bool checkArg(Point s, int rad, int width, Bitmap bitmap);

Bitmap makeCollage(std::vector<Bitmap> images, int n, int m);

void error(std::string str);

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
    /*
        isNameCorrect(argv[2]);
        std::ifstream file(argv[2], std::ifstream::binary);
        if (!file.is_open()) {
            throw std::invalid_argument("Can't open input file");
        }
        Bitmap bitmap(file);
        file.close();
*/
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
    //draw pentagram
    /*
        Point s;
        int rad, width;
        int r, g, b;
        std::cin >> s.x >> s.y >> rad >> width >> r >> g >> b;
        Bitmap::Pixel color(b, g, r);
        if(checkArg(s, rad, width, bitmap))
            throw std::invalid_argument("");
    bitmap.drawPentagram(s, rad, width, color);
*/
    //make collage
    /*
    int n, m;
    std::cin >> n >> m;
    std::vector<Bitmap> images;
    for(int i = 0; i < n * m; i++) {
        isNameCorrect(argv[i + 2]);
        std::cout << argv[i + 2] << std::endl;
        std::ifstream file(argv[i + 2], std::ifstream::binary);
        if (!file.is_open()) {
            throw std::invalid_argument("Can't open input file");
        }
        Bitmap bitmap(file);
        images.emplace_back(bitmap);
        file.close();
    }
    Bitmap new_bitmap;
    new_bitmap.makeCollage(images, n, m);
    std::ofstream result("result.bmp", std::ofstream::binary);
    new_bitmap.saveBitmap(result);
    result.close();
    new_bitmap.clearBitmap();
*/
    //save
    /*
        std::ofstream result("result.bmp", std::ofstream::binary);
        bitmap.saveBitmap(result);
        result.close();
        bitmap.clearBitmap();
    */

    Bitmap bitmap;
    std::vector<int> func;
    int arg = 0;

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

            {"draw pentagram",   no_argument,       nullptr, 'p'}, //3
            {"center",         required_argument, nullptr, 'z'},
            {"rad",         required_argument, nullptr, 't'},
            {"color_pentagram",  required_argument, nullptr, 'q'},

            {"make collage",     no_argument,       nullptr, 'j'}, //4
            {"num",           required_argument, nullptr, 'k'},
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
                std::cout << "-h or --help to output of this help" << std::endl;
                std::cout << "-r or --read [fileName.bmp] to read pictures from a file with the name \"fileName.bmp\""
                          << std::endl;
                std::cout << "-s or --save [fileName.bmp] to save pictures to a file with the name \"fileName.bmp\""
                          << std::endl;
                break;
            };
            case 'r': { //read
                if(!isNameCorrect(optarg)) {
                    error("invalid argument in read.");
                    return 0;
                }
                std::ifstream file(optarg, std::ifstream::binary);
                if (!file.is_open()) {
                    error("Can't open input file");
                    return 0;
                }
                bitmap.getBitmapFromFile(file);
                file.close();
                flag_input = true;
                break;
            };
            case 's': { //save
                if(!flag_input) {
                    error("You did not enter a input file name");
                    return 0;
                }
                if(!isNameCorrect(optarg)) {
                    error("invalid argument in save");
                    return 0;
                }
                std::ofstream result(optarg, std::ofstream::binary);
                bitmap.saveBitmap(result);
                result.close();
                bitmap.clearBitmap();
                break;
            };
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
                                return 0;
                            }
                            axis = optarg;
                            if(axis != "OX" && axis != "ox" && axis != "oy" && axis != "OY") {
                                error("invalid argument in mirror, axis");
                                return 0;
                            }
                            used[0] = true;
                            k--;
                            break;
                        };
                        case 'f': { // "start"
                            if(used[1]) {
                                error("too much argument in mirror, start point");
                                return 0;
                            }
                            try {
                                start.x = std::stoi(strtok(optarg, ",;"));
                                start.y = std::stoi(strtok(optarg, ",;"));
                            }
                            catch (std::exception &e) {
                                error("invalid argument in mirror, start point");
                                return 0;
                            }
                            k--;
                            used[1] = true;
                            break;
                        };
                        case 'u': { // "finish"
                            if(used[2]) {
                                error("too much argument in mirror, finish point");
                                return 0;
                            }
                            try {
                                finish.x = std::stoi(strtok(optarg, ",;"));
                                finish.y = std::stoi(strtok(optarg, ",;"));
                            }
                            catch (std::exception &e) {
                                error("invalid argument in mirror, finish point");
                                return 0;
                            }
                            k--;
                            used[2] = true;
                            break;
                        };
                        case '?':
                        default: {
                            error("invalid command in mirror");
                            return 0;
                        };
                    };
                };
                if(!checkOXY(start, finish, axis, bitmap)) {
                    error("invalid input in mirror");
                    return 0;
                }
                if(bitmap.mirror(start, finish, axis) != 0) {
                    error("invalid input in mirror");
                    return 0;
                }
                break;
            };
            case 'd': { //draw_a_rectangle

                if(!flag_input) {
                    error("You did not enter a input file name");
                    return 0;
                }

                int k = 5;
                std::vector<bool> used(5, false);
                Bitmap:Point start, finish;
                bool isFill = false;
                int width = 0;
                std::string colorLine, colorFill;
                while (k != 0 && (rez = getopt_long(argc, argv, short_options,
                                          long_options, &option_index)) != -1) {
                    switch (rez) {
                        case 'f': { // "start"
                            if(used[0]) {
                                error("too much argument in rectangle, start point");
                                return 0;
                            }
                            try {
                                start.x = std::stoi(strtok(optarg, ",;"));
                                start.y = std::stoi(strtok(optarg, ",;"));
                            }
                            catch (std::exception &e) {
                                error("invalid argument in rectangle, start point");
                                return 0;
                            }
                            k--;
                            used[0] = true;
                            break;
                        };
                        case 'u': { // "finish"
                            if(used[1]) {
                                error("too much argument in rectangle, finish point");
                                return 0;
                            }
                            try {
                                finish.x = std::stoi(strtok(optarg, ",;"));
                                finish.y = std::stoi(strtok(optarg, ",;"));
                            }
                            catch (std::exception &e) {
                                error("invalid argument in rectangle, finish point");
                                return 0;
                            }
                            k--;
                            used[1] = true;
                            break;

                        };
                        case 'c': { // "color_rectangle"
                            if(used[2]) {
                                error("too much argument in rectangle, color rectangle");
                                return 0;
                            }
                            try {
                                colorLine = optarg;
                                if(colors.find(colorLine) == colors.end()) {
                                    throw std::invalid_argument("colorLine");
                                }
                            }
                            catch (std::exception &e) {
                                error("invalid argument colorLine in  in rectangle, color rectangle");
                                return 0;
                            }
                            k--;
                            used[2] = true;
                            break;
                        };
                        case 'i': { // "is_fill"
                            if(used[3]) {
                                error("too much argument in rectangle, is fill");
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
                            catch(std::exception &e){
                                error("invalid argument in rectangle, is fill");
                                return 0;
                            }
                        };
                        case 'l': { // "color_fill"
                            if(!isFill) {
                                error("color fill with false is fill");
                                return 0;
                            }
                            if(used[4]) {
                                error("too much argument in rectangle, color fill");
                                return 0;
                            }
                            try {
                                colorFill = optarg;
                                if(colors.find(colorFill) == colors.end()) {
                                    throw std::invalid_argument("color fill");
                                }
                            }
                            catch (std::exception &e) {
                                error("invalid argument in rectangle, color fill");
                                return 0;
                            }
                            k--;
                            used[4] = true;
                            break;
                        };
                        case 'g': { // "width_line"
                            if(used[5]) {
                                error("too much argument in rectangle, line width");
                                return 0;
                            }
                            try {
                                width = std::stoi(optarg);
                            }
                            catch (std::exception &e) {
                                error("invalid argument in rectangle, line width");
                                return 0;
                            }
                            k--;
                            break;
                        };
                        case '?':
                        default: {
                            error("invalid option in rectangle");
                            std::cout << optarg;
                            return 0;
                        };
                    };
                };
                if(!checkXYW(start, finish, width, bitmap)) {
                    error("invalid argument in rectangle");
                    return 0;
                }
                bitmap.drawRectangle(start, finish, width, colors[colorLine]);
                if(isFill) bitmap.fillRectangle(start, finish, width, colors[colorFill]);
                break;
            };



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
                Bitmap::Pixel color;

                while (k != 0 && (rez = getopt_long(argc, argv, short_options,
                                          long_options, &option_index)) != -1) {
                    switch (rez) {
                        case 'g': { // "width_line"
                            if(used[0]) {
                                error("too much argument in pentagram, line width");
                                return 0;
                            }
                            try {
                                width = std::stoi(optarg);
                            }
                            catch (std::exception &e) {
                                error("invalid argument");
                                return 0;
                            }
                            used[0] = true;
                            k--;
                            break;
                        };
                        case 'z': { // "center"
                            if(used[1]) {
                                error("too much argument in pentagram, center point");
                                return 0;
                            }
                            try {
                                center.x = std::stoi(strtok(optarg, ",;"));
                                center.y = std::stoi(strtok(optarg, ",;"));
                            }
                            catch (std::exception &e) {
                                error("invalid argument");
                                return 0;
                            }
                            k--;
                            used[1] = true;
                            break;
                        };
                        case 't': { // "radius"
                            if(used[2]) {
                                error("too much argument in pentagram, radius");
                                return 0;
                            }
                            try {
                                rad = std::stoi(optarg);
                            }
                            catch (std::exception &e) {
                                error("invalid argument");
                                return 0;
                            }
                            k--;
                            used[2] = true;
                            break;
                        };
                        case 'q': { // "color_pentagram"
                            if(used[3]) {
                                error("too much argument in pentagram, color");
                                return 0;
                            }
                            try {
                                color.r = std::stoi(strtok(optarg, ",;"));
                                color.g = std::stoi(strtok(optarg, ",;"));
                                color.b = std::stoi(strtok(optarg, ",;"));
                            }
                            catch (std::exception &e) {
                                error("invalid argument");
                                return 0;
                            }
                            k--;
                            used[3] = true;
                            break;
                        };
                        case '?':
                        default: {
                            printf("found unknown option\n");
                            break;
                        };
                    };
                };
                bitmap.drawPentagram(center, rad, width, color);
                break;
            };


            case 'j': { // "make_collage"

                if(!flag_input) {
                    error("You did not enter a input file name");
                    return 0;
                }

                int k = 3;
                std::vector<bool> used(k, false);
                int n = 0, m = 0;
                std::vector<std::string> name;

                while (k != 0 && (rez = getopt_long(argc, argv, short_options,
                                          long_options, &option_index)) != -1) {
                    switch (rez) {
                        case 'b': { // "picture_list"
                            if(used[3]) {
                                error("too much argument in collage, pictures list");
                                return 0;
                            }
                            /*while() {
                                name.emplace_back(strtok(optarg, ",;"));
                            }*/
                            k--;
                            used[3] = true;
                            break;
                        };

                        case 'k': { // "n, m"
                            if(used[3]) {
                                error("too much argument in collage, numbers");
                                return 0;
                            }
                            try {
                                n = std::stoi(strtok(optarg, ",;"));
                                m = std::stoi(strtok(optarg, ",;"));
                            }
                            catch (std::exception &e) {
                                error("invalid argument");
                                return 0;
                            }
                            k--;
                            used[3] = true;
                            break;
                        };
                        case '?':
                        default: {
                            printf("found unknown option\n");
                            break;
                        };
                    };
                };
                std::cout << "\ncollage\n";
                break;
            };
            case '?':
            default: {
                printf("found unknown option\n");
                break;
            };
        };
    };
    return 0;
}

void error(std::string str) {
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