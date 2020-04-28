#include <fstream>
#include "bmp.h"



int main(int argc, char *argv[]) {
    std::ifstream file(argv[2], std::ifstream::binary);
    if (!file.is_open()) {
        //error("Can't open input file");
        return 1;
    }
    Bitmap bitmap(file);
    file.close();

    std::ofstream result("result.bmp", std::ofstream::binary);
    bitmap.saveBitmap(result);
    result.close();

 //   bitmap.clearBitmap();
    return 0;
}