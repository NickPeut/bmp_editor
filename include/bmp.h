#ifndef COURSECPP_BMP_H
#define COURSECPP_BMP_H

#include<iostream>
#include <cstring>
#include <vector>

static const size_t PIXEL_SIZE = 3;
static const size_t WIDTH_POSITION = 18;
static const size_t HEADER_SIZE_POSITION = 14;
static const size_t WIDTH_BYTES_SIZE = 4;
static const size_t HEIGHT_BYTES_SIZE = 4;
static const size_t HEADER_SIZE = 54;



class Bitmap {

    struct Pixel {
        char data[3];
    };
    using PixelContainer = std::vector<std::vector<Pixel>>;
#pragma pack(push, 1)
    struct BitmapData {
        //HEADER
        char bfType[2];
        char bfSizeFile[4]; //Changing

        //BOTH
        char bfHeaderOtherFirst[8];


        //INFO
        char headerSize[4];
        char biWidth[4];
        char biHeight[4];
        char planes[2];
        char bitsPerPixel[2];
        char compression[4];
        char imageSize[4];
        char xPixelsPerMeter[4];
        char yPixelsPerMeter[4];
        char colorsInColorTable[4];
        char importantColorCount[4];
        /*//INFO
        char headerSize[4];
        char biWidth[4];
        char biHeight[4];
        char biOtherFirst[8]; //biPlanes, biBitCount, biCompression
        char biSizeImage[4]; //Changing
        char biOtherSecond[16]; //biXPelsPerMeters, biYPelsPerMeter, biClrUsed, biClrImportant
         */
    };
#pragma pack(pop)
     size_t width;
     size_t height;
     size_t widthBytes;
     BitmapData header;
     Pixel** picture;

public:

    void saveBitmap(std::ofstream &file);

    void clearBitmap();

    int getBitmapFromFile(std::ifstream &file);

    Bitmap(std::ifstream &file);

private:
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
};
#endif //COURSECPP_BMP_H
