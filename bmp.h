#ifndef COURSECPP_BMP_H
#define COURSECPP_BMP_H

#include<iostream>
#include <cstring>

static const size_t PIXEL_SIZE = 3;
static const size_t WIDTH_POSITION = 18;
static const size_t WIDTH_BYTES_SIZE = 4;
static const size_t HEIGHT_BYTES_SIZE = 4;
static const size_t HEADER_SIZE = 54;


typedef struct Pixel_s
{
    std::string data[3];
} Pixel;

typedef struct BitmapData_s
{
    //HEADER
    std::string bfType[2];
    char bfSizeFile[4]; //Changing

    //BOTH
    char bfHeaderOtherFirst[12];

    //INFO
    char biWidth[4];
    char biHeight[4];
    char biOtherFirst[8]; //biPlanes, biBitCount, biCompression
    char biSizeImage[4]; //Changing
    char biOtherSecond[16]; //biXPelsPerMeters, biYPelsPerMeter, biClrUsed, biClrImportant

}  __attribute__((packed)) BitmapData;

class Bitmap {
     size_t width;
     size_t height;
     size_t widthBytes;
     BitmapData header;
     Pixel** picture;
public:
    Bitmap(const std::string &fileName);

    void saveBitmap(FILE *file);

    void clearBitmap();

    int getBitmapFromFile(char *fileName);

private:
    int readBitmap(FILE *file);

    static size_t normalizeTo4(size_t x);

    void scanHeader(FILE *file);

    void scanSize(FILE *file);

    int initPixelArray();

    void reverse();

    void scanPicture(FILE *file);

    void printHeader(FILE *file);

    void printPicture(FILE *file);

};
#endif //COURSECPP_BMP_H
