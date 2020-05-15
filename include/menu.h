#ifndef COURSECPP_MENU_H
#define COURSECPP_MENU_H

#include "bmp.h"
const std::map<std::string, Bitmap::Pixel> colors = {
        {"cyan",    {2,   2,   8}},
        {"black",   {0,   0,   0}},
        {"gray",    {128, 128, 128}},
        {"white",   {255, 255, 255}},
        {"fuchsia", {255, 0,   255}},
        {"purple",  {128, 0,   128}},
        {"red",     {255, 0,   0}},
        {"maroon",  {128, 0,   0}},
        {"yellow",  {255, 255, 0}},
        {"olive",   {128, 128, 0}},
        {"lime",    {0,   255, 0}},
        {"aqua",    {0,   255, 255}},
        {"teal",    {0,   128, 128}},
        {"blue",    {0,   0,   255}},
        {"navy",    {0,   0,   128}}
};

void error(const std::string &str);

bool checkXYW(Point s, Point f, int width, Bitmap &bitmap);

bool checkArg(Point s, int rad, int width, Bitmap &bitmap);

bool readBMP(char *optarg, Bitmap &bitmap);

bool isNameCorrect(char *name);

bool checkPoint(Point a, Bitmap &bitmap);

bool checkOXY(Point point1, Point point2, std::string &oxy, Bitmap &bitmap);

void printInfo(Bitmap &bitmap);

void printHelp();
#endif //COURSECPP_MENU_H
