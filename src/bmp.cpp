#include <fstream>
#include "bmp.h"

size_t Bitmap::normalizeTo4(size_t x) {
    return (x + 3) / 4 * 4;
}

int Bitmap:: scanHeader(std::ifstream &file) {
    try {
        if (isCorrect(file)) {
            file.read((char *) (&header), HEADER_SIZE);
            return 0;
        }
        else
            throw std::logic_error("don't supported file format");
    }
    catch (std::logic_error* err) {
        std::cout << err;
        return 1;
    }
    file.read((char *) (&header), HEADER_SIZE);
    return 0;
}

void Bitmap::scanSize() {

    width = height = 0;
    widthBytes = 0;
    memcpy(&width, header.biWidth, WIDTH_BYTES_SIZE);
    memcpy(&height, header.biHeight, HEIGHT_BYTES_SIZE);
    widthBytes = normalizeTo4(width * PIXEL_SIZE);
}

int Bitmap:: initPixelArray() {
    try{
        picture = new Pixel* [height];
        if (picture == nullptr)
            throw 1;

        picture[0] = new Pixel [widthBytes* height];
        memset(picture[0], 0, widthBytes * height);

        if (picture[0] == nullptr)
        {
            delete(picture);
            throw 1;
        }

        for (size_t i = 1; i < height; i++)
        {
            picture[i] = (Pixel*)((char*)picture[i - 1] + widthBytes);
        }
    }
    catch (int err) {
        std::cout << "Error " << err << " ";
        return err;
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
    file.read((char*)(&picture[0][0]), widthBytes * height);
    reverse();
}

void Bitmap:: printHeader(std::ofstream &file) {
    file.write((char*)(&header), HEADER_SIZE);
}

void Bitmap:: printPicture(std::ofstream &file) {
    reverse();
    file.write((char*)(&picture[0][0]), height * widthBytes);
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
    if(scanHeader(file) != 0) {
        return 1;
    }
    scanSize();
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

bool Bitmap::isCorrect(std::ifstream &file) {
    file.read(header.bfType, sizeof(header.bfType));
    file.seekg(HEADER_SIZE_POSITION, std::ios_base::beg);
    file.read(header.headerSize, sizeof(header.headerSize));
    file.seekg(0, std::ios_base::beg);
    //return ;
}
