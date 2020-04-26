#include "bmp.h"

size_t Bitmap::normalizeTo4(size_t x) {
    return (x + 3) / 4 * 4;
}

void Bitmap:: scanHeader(FILE *file)
{
    fseek(file, 0, SEEK_SET);
    fread(&header, HEADER_SIZE, 1, file);
}

void Bitmap:: scanSize(FILE *file)
{
    fseek(file, WIDTH_POSITION, SEEK_SET);

    width = height = 0;

    fread(&width, WIDTH_BYTES_SIZE, 1, file);
    fread(&height, HEIGHT_BYTES_SIZE, 1, file);

    widthBytes = normalizeTo4(width * PIXEL_SIZE);
}

int Bitmap:: initPixelArray()
{
    picture = (Pixel**)malloc(height * sizeof(Pixel*));
    if (picture == nullptr)
        return 1;

    picture[0] = (Pixel*)malloc(widthBytes * height);
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

void Bitmap:: reverse()
{
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


void Bitmap:: scanPicture(FILE *file)
{
    fseek(file, sizeof(header), SEEK_SET);
    fread(&picture[0][0], 1, widthBytes * height, file);
    reverse();
}



void Bitmap:: printHeader(FILE *file)
{
    fwrite(&header, HEADER_SIZE, 1, file);
}

void Bitmap:: printPicture(FILE *file)
{
    fseek(file, sizeof(header), SEEK_SET);

    reverse();

    fwrite(&picture[0][0], height * widthBytes, 1, file);

    reverse();
}

void Bitmap:: saveBitmap(FILE *file)
{
    printHeader(file);
    printPicture(file);
}

void Bitmap:: clearBitmap()
{
    free(picture[0]);
    free(picture);
}

int Bitmap:: readBitmap(FILE *file)
{
    scanHeader(file);
    scanSize(file);
    if (initPixelArray() != 0)
    {
        return 1;
    }
    scanPicture(file);
    return 0;
}

int Bitmap:: getBitmapFromFile( fileName)
{
    FILE *file = fopen(fileName, "rb");

    if (file == nullptr) {
    //TODO
        //error("Can't open input file");
        return 1;
    }

    if (readBitmap(file) != 0)
    {
        fclose(file);
        //error("Memory allocation failed");
        return 7;
    }

    fclose(file);
    return 0;
}

Bitmap::Bitmap(const std::string &fileName) {

}


