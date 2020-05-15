#ifndef COURSECPP_BMP_H
#define COURSECPP_BMP_H

#include<iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <fstream>
#include "processings_bmp.h"

static const size_t PIXEL_SIZE = 3;
static const size_t WIDTH_BYTES_SIZE = 4;
static const size_t HEIGHT_BYTES_SIZE = 4;

class Bitmap {

#pragma pack(push, 1)
    struct Header{
        char bfType[2];// Сигнатура формата
        char bfSizeFile[4]; //Changing Размер файла в байтах
        char reserved1[2];// Зарезервированное поля = 0
        char reserved2[2];// Зарезервированное поля = 0
        char pixelArrOffset[4];// Положение пиксельных данных относительно начала
    };
    struct BitmapData {
        //INFO
        char headerSize[4]; // Размер данной структуры в байтах
        char biWidth[4];// Ширина растра в пикселях
        char biHeight[4];// Высота растра в пикселях
        char planes[2];// Константа = 1
        short bitsPerPixel;// Количество бит на пиксель
        char compression[4];// Способ хранения пикселей
        char imageSize[4];// Размер пиксельных данных
        char xPixelsPerMeter[4];// Количество пикселей на метр по горизонатли
        char yPixelsPerMeter[4];// Количество пикселей на метр по вертикали
        int colorsInColorTable;// Размер таблицы цветов в ячейках ||| если 0 - таблицы нет.
        char importantColorCount[4];// Количество ячеек от начала таблицы цветов до последней используемой
    };
#pragma pack(pop)

public:

    struct Pixel {
        Pixel(int red, int green, int blue);
        Pixel();

        unsigned char b;
        unsigned char g;
        unsigned char r;
    };

    size_t height;
    size_t widthBytes;
    size_t width;
    Header header;
    BitmapData data;
    Pixel** picture;
    bool isPicture;

    virtual ~Bitmap();

    explicit Bitmap();

    Bitmap& operator = (const Bitmap &other);

    explicit Bitmap(std::ifstream &file);

    void saveBitmap(std::ofstream &file);

    int mirror(Point &point1, Point &point2, std::string &oxy);

    void drawRectangle(Point left, Point right, int w, Pixel color);

    void fillRectangle(Point s, Point f, int w, Pixel color);

    void drawPentagram(Point center, int radius, int w, Pixel color);

    void makeCollage(std::vector<Bitmap> &images, const int &n, const int &m);

    bool getBitmapFromFile(std::ifstream &file);

private:

    void drawLine(Point a, Point b, Pixel color);

    void drawCircle(Point center, int rad, Bitmap::Pixel color, std::vector<std::pair<Point, bool>> &circle, bool flag);

    void drawStar(const Point &center, int radius, Bitmap::Pixel color);

    int readBitmap(std::ifstream &file);

    static size_t normalizeTo4(size_t x);

    int scanHeader(std::ifstream &file);

    void scanSize();

    int initPixelArray();

    void reverse();

    void scanPicture(std::ifstream &file);

    void printHeader(std::ofstream &file);

    void printPicture(std::ofstream &file);

    bool isCorrect(std::ifstream &file);

    void fillCircle(std::vector<std::pair<Point, bool>> circle, const Bitmap::Pixel &color);
};
#endif //COURSECPP_BMP_H
