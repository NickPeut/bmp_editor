#include "bmp.h"



int main(int argc, char **argv) {

    Bitmap bitmap(<#initializer#>);
    std::string fileName = argv[1];
    fileName = "../" + fileName;
    if (bitmap.getBitmapFromFile(fileName) != 0)
        return 1;
    FILE *f = fopen("result", "wb");
    bitmap.saveBitmap(f);
    bitmap.clearBitmap();
    return 0;
}