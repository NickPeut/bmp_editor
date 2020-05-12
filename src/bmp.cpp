#include <fstream>
#include "bmp.h"

size_t Bitmap::normalizeTo4(size_t x) {
    return (x + 3) / 4 * 4;
}

int Bitmap:: scanHeader(std::ifstream &file) {
    try {
        if (isCorrect(file)) {
            return 0;
        }
        else
            throw std::logic_error("not supported file format");
    }
    catch (std::logic_error* err) {
        std::cout << err;
        return 1;
    }

    file.read((char *) (&header), sizeof(header));
    file.read((char *) (&data), sizeof(data));
    return 0;
}

void Bitmap::scanSize() {

    width = height = 0;
    widthBytes = 0;
    memcpy(&width, data.biWidth, WIDTH_BYTES_SIZE);
    memcpy(&height, data.biHeight, HEIGHT_BYTES_SIZE);
    widthBytes = normalizeTo4(width * PIXEL_SIZE);
}

int Bitmap:: initPixelArray() {
    try {
        picture = (Pixel**)malloc(height * sizeof(Pixel*));
        if (picture == nullptr)
            throw 1;
        picture[0] = (Pixel*)malloc(widthBytes * height);
        memset(picture[0], 0, widthBytes * height);

        if (picture[0] == nullptr) {
            free(picture);
            throw 1;
        }

        for (size_t i = 1; i < height; i++) {
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
    for (size_t i = 0; i * 2 < height; i++) {
        for (size_t j = 0; j < width; j++) {
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
    file.write((char*)(&header), sizeof(header));
    file.write((char*)(&data), sizeof(data));
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
    if (scanHeader(file) != 0) {
        return 1;
    }
    scanSize();
    if (initPixelArray() != 0) {
        return 1;
    }
    scanPicture(file);
    return 0;
}

void Bitmap:: getBitmapFromFile(std::ifstream &file) {
        if (readBitmap(file) != 0) {
            throw std::logic_error("Memory allocation failed");
        }
}

Bitmap::Bitmap(std::ifstream &file) {
    getBitmapFromFile(file);
}

Bitmap::Bitmap() {}

bool Bitmap::isCorrect(std::ifstream &file) {
    file.read((char*)(&header), sizeof(header));
    file.read((char*)(&data), sizeof(data));
    if (data.bitsPerPixel != 24)
        throw std::invalid_argument("format not supported");
    return data.colorsInColorTable == 0;
}


Bitmap::Pixel::Pixel(int red, int green, int blue) : b(blue), g(green), r(red) {}

Bitmap::Pixel::Pixel() {}
