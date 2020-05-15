#include <getopt.h>
#include "bmp.h"
#include "menu.h"
#include "processings_bmp.h"



int main(int argc, char *argv[]) {
    const char *short_options = "hr:ma:df:u:c:o:l:g:pz:q:jk:b:s:i";

    const struct option long_options[] = {
            {"help",            no_argument,       nullptr, 'h'},

            {"read",            required_argument, nullptr, 'r'}, //0

            {"mirror",          no_argument,       nullptr, 'm'}, //1
            {"axis",            required_argument, nullptr, 'a'},

            {"draw_rectangle",  no_argument,       nullptr, 'd'}, //2
            {"start",           required_argument, nullptr, 'f'},
            {"finish",          required_argument, nullptr, 'u'},
            {"color_rectangle", required_argument, nullptr, 'c'},
            {"is_fill",         required_argument, nullptr, 'o'},
            {"color_fill",      required_argument, nullptr, 'l'},
            {"width_line",      required_argument, nullptr, 'g'},

            {"draw_pentagram",  no_argument,       nullptr, 'p'}, //3
            {"center",          required_argument, nullptr, 'z'},
            {"rad",             required_argument, nullptr, 't'},
            {"color_pentagram", required_argument, nullptr, 'q'},

            {"make_collage",    no_argument,       nullptr, 'j'}, //4
            {"nums",            required_argument, nullptr, 'k'},
            {"picture_list",    required_argument, nullptr, 'b'},

            {"save",            required_argument, nullptr, 's'}, //5

            {"info",            no_argument,       nullptr, 'i'} //6
    };

    Bitmap bitmap;
    bool flag_input = false;

    int rez;
    int option_index;
    try {
        while ((rez = getopt_long(argc, argv, short_options,
                                  long_options, &option_index)) != -1) {
            switch (rez) {
                case 'h': { //help.text
                    printHelp();
                    break;
                }
                case 'i': { //Info
                    if(flag_input)
                        printInfo(bitmap);
                    else {
                        error("logic error");
                        return 0;
                    }
                    break;
                }
                case 'r': { //read
                    if (isNameCorrect(optarg)) {
                        if (readBMP(optarg, bitmap)) {
                            error("Can't open input file");
                            return 0;
                        }
                        flag_input = true;
                        break;
                    } else {
                        error("invalid argument in read.");
                        return 0;
                    }
                }
                case 's': { //save
                    if (!flag_input) {
                        error("You did not enter a input file name");
                        return 0;
                    }
                    if (!isNameCorrect(optarg)) {
                        error("invalid argument in save");
                        return 0;
                    }
                    std::ofstream result(optarg, std::ofstream::binary);
                    bitmap.saveBitmap(result);
                    result.close();
                    break;
                }
                case 'm': { //mirror

                    if (!flag_input) {
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
                                if (used[0]) {
                                    error("too much argument in mirror, axis");
                                    return 0;
                                }
                                axis = optarg;
                                if (axis != "OX" && axis != "ox" && axis != "oy" && axis != "OY") {
                                    error("invalid argument in mirror, axis");
                                    return 0;
                                }
                                used[0] = true;
                                k--;
                                break;
                            }
                            case 'f': { // "start"
                                if (used[1]) {
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
                            }
                            case 'u': { // "finish"
                                if (used[2]) {
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
                            }
                            case '?':
                            default: {
                                error("invalid command in mirror");
                                return 0;
                            }
                        }
                    }
                    if (!checkOXY(start, finish, axis, bitmap)) {
                        error("invalid input in mirror");
                        return 0;
                    }
                    if (bitmap.mirror(start, finish, axis) != 0) {
                        error("invalid input in mirror");
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
                                }
                                case 'u': { // "finish"
                                    if (used[1]) {
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

                                }
                                case 'c': { // "color_rectangle"
                                    if (used[2]) {
                                        error("too much argument in rectangle, color rectangle");
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
                                        return 0;
                                    }
                                    k--;
                                    used[2] = true;
                                    break;
                                }
                                case 'o': { // "is_fill"
                                    if (used[3]) {
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
                                    catch (std::exception &e) {
                                        error("invalid argument in rectangle, is fill");
                                        return 0;
                                    }
                                }
                                case 'l': { // "color_fill"
                                    if (!isFill) {
                                        error("color fill with false is fill");
                                        return 0;
                                    }
                                    if (used[4]) {
                                        error("too much argument in rectangle, color fill");
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
                                        return 0;
                                    }
                                    k--;
                                    used[4] = true;
                                    break;
                                }
                                case 'g': { // "width_line"
                                    if (used[5]) {
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
                                }
                                case '?':
                                default: {
                                    error("invalid option in rectangle");
                                    std::cout << optarg;
                                    return 0;
                                }
                            }
                        }
                        if (!checkXYW(start, finish, width, bitmap)) {
                            error("invalid argument in rectangle");
                            return 0;
                        }
                        bitmap.drawRectangle(start, finish, width, colors.at(colorLine));
                        if (isFill)
                            bitmap.fillRectangle(start, finish, width, colors.at(colorFill));
                        break;
                    } else {
                        error("You did not enter a input file name");
                        return 0;
                    }
                }
                case 'p': { // "draw_pentagram"
                    if (!flag_input) {
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
                                if (used[0]) {
                                    error("too much argument in pentagram, line width");
                                    return 0;
                                }
                                try {
                                    width = std::stoi(optarg);
                                }
                                catch (std::exception &e) {
                                    error("invalid argument in pentagram, line width");
                                    return 0;
                                }
                                used[0] = true;
                                k--;
                                break;
                            }
                            case 'z': { // "center"
                                if (used[1]) {
                                    error("too much argument in pentagram, center point");
                                    return 0;
                                }
                                try {
                                    center.x = std::stoi(strtok(optarg, ",;"));
                                    center.y = std::stoi(strtok(optarg, ",;"));
                                }
                                catch (std::exception &e) {
                                    error("invalid argument in pentagram, center point");
                                    return 0;
                                }
                                k--;
                                used[1] = true;
                                break;
                            }
                            case 't': { // "radius"
                                if (used[2]) {
                                    error("too much argument in pentagram, radius");
                                    return 0;
                                }
                                try {
                                    rad = std::stoi(optarg);
                                }
                                catch (std::exception &e) {
                                    error("invalid argument in pentagram, radius");
                                    return 0;
                                }
                                k--;
                                used[2] = true;
                                break;
                            }
                            case 'q': { // "color_pentagram"
                                if (used[3]) {
                                    error("too much argument in pentagram, color");
                                    return 0;
                                }
                                try {
                                    color = optarg;
                                    if (colors.find(color) == colors.end()) {
                                        throw std::invalid_argument("");
                                    }
                                }
                                catch (std::exception &e) {
                                    error("invalid argument in pentagram, color");
                                    return 0;
                                }
                                k--;
                                used[3] = true;
                                break;
                            }
                            case '?':
                            default: {
                                error("found unknown option in pentagram");
                                return 0;
                            }
                        }
                    }
                    if (checkArg(center, rad, width, bitmap)) {
                        error("invalid argument in pentagram");
                        return 0;
                    }
                    bitmap.drawPentagram(center, rad, width, colors.at(color));
                    break;
                }


                case 'j': { // "make_collage"
                    flag_input = true;
                    int k = 2;
                    std::vector<bool> used(k, false);
                    int n = 0, m = 0;
                    std::vector<char *> names;
                    bool flagNM = false;
                    while (k != 0 && (rez = getopt_long(argc, argv, short_options,
                                                        long_options, &option_index)) != -1) {
                        switch (rez) {
                            case 'b': { // "picture_list"
                                if (!flagNM) {
                                    error("You did not enter a input numbers");
                                    return 0;
                                }
                                if (used[1]) {
                                    error("too much argument in collage, pictures list");
                                    return 0;
                                }
                                try {
                                    int count = 0;
                                    char *name = strtok(optarg, ",;");
                                    while (count != n * m && name != nullptr) {
                                        if (!isNameCorrect(name)) {
                                            error("invalid name in name lost for collage");
                                            return 0;
                                        }
                                        names.push_back(name);
                                        name = strtok(nullptr, ",;");
                                        count++;
                                    }
                                }
                                catch (std::exception &e) {
                                    error("invalid argument in make collage in list");
                                    return 0;
                                }
                                k--;
                                used[1] = true;
                                break;
                            }

                            case 'k': { // "n, m"
                                if (used[0]) {
                                    error("too much argument in collage, numbers");
                                    return 0;
                                }
                                try {
                                    n = std::stoi(strtok(optarg, ",;"));
                                    m = std::stoi(strtok(optarg, ",;"));
                                }
                                catch (std::exception &e) {
                                    error("invalid argument in collage, numbers");
                                    return 0;
                                }
                                flagNM = true;
                                k--;
                                used[0] = true;
                                break;
                            }
                            case '?':{
                                error("found unknown option");
                                return 0;
                            }
                            default: {
                                error("found unknown option in collage");
                                return 0;
                            }
                        }
                    }

                    std::vector<Bitmap> images(n*m);
                    try {
                        for (int i = 0; i < n * m; i++) {
                            if(readBMP(names[i], images[i])) {
                                std:: cout << names[i];
                                return 0;
                            }
                            images[i].isPicture = true;
                        }
                    }
                    catch(std::exception &e) {
                        error("make_collage error");
                        return 0;
                    }
                    bitmap.makeCollage(images, n, m);
                    break;
                }
                case '?': {
                    error("found unknown option");
                    return 0;
                }
                default: {
                    error("found unknown option");
                    return 0;
                }
                }
            }
        }
    catch(std::logic_error &e){
        error("logic error in arguments");
    }
    return 0;
}
