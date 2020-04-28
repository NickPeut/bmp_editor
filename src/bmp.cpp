#include <fstream>
#include "bmp.h"

size_t Bitmap::normalizeTo4(size_t x) {
    return (x + 3) / 4 * 4;
}

void Bitmap:: scanHeader(std::ifstream &file) {
    std::cout << file.tellg() << " " << sizeof(header) << std::endl;
    file.read((char*)(&header), HEADER_SIZE);
}

void Bitmap:: scanSize(std::ifstream &file) {

    width = height = 0;
    widthBytes = 0;
    memcpy(&width, header.biWidth, WIDTH_BYTES_SIZE);
    memcpy(&height, header.biHeight, HEIGHT_BYTES_SIZE);
    widthBytes = normalizeTo4(width * PIXEL_SIZE);
}

int Bitmap:: initPixelArray() {
    picture = new Pixel* [height];//(Pixel**)malloc(height * sizeof(Pixel*));
    if (picture == nullptr)
        return 1;

    picture[0] = new Pixel [widthBytes* height];//(Pixel*)malloc(widthBytes * height);
    memset(picture[0], 0, widthBytes * height);

    if (picture[0] == nullptr)
    {
        free(picture);
        return 1;
    }

    for (size_t i = 1; i < height; i++)
    {
        picture[i] = (Pixel*)((char*)picture[i - 1] + widthBytes);
    }
    return 0;
}

void Bitmap:: reverse() {
    for (size_t i = 0; i * 2 < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            Pixel tmp = picture[i][j];
            picture[i][j] = picture[height - i - 1][j];
            picture[height - i - 1][j] = tmp;
        }
    }
}

void Bitmap:: scanPicture(std::ifstream &file) {
    file.read((char*)(&picture[0][0]), widthBytes * height);// widthBytes * height -> 1
    reverse();
}

void Bitmap:: printHeader(std::ofstream &file) {
    file.write((char*)(&header), HEADER_SIZE); //HEADER_SIZE -> 1
}

void Bitmap:: printPicture(std::ofstream &file) {
    reverse();
    file.write((char*)(&picture[0][0]), height * widthBytes); //height * widthBytes -> 1
    reverse();
}

void Bitmap:: saveBitmap(std::ofstream &file) {
    printHeader(file);
    printPicture(file);
}

void Bitmap:: clearBitmap() {
    free(picture[0]);
    free(picture);
}

int Bitmap:: readBitmap(std::ifstream &file) {
    scanHeader(file);
    scanSize(file);
    if (initPixelArray() != 0)
    {
        return 1;
    }
    scanPicture(file);
    return 0;
}

int Bitmap:: getBitmapFromFile(std::ifstream &file) {
    if (readBitmap(file) != 0) {
        //error("Memory allocation failed");
        return 7;
    }
    return 0;
}

Bitmap::Bitmap(std::ifstream &file) {
    getBitmapFromFile(file);
}


