#include "processings_bmp.h"
#include "bmp.h"
void Bitmap::mirror(Point &point1, Point &point2, std::string &oxy) {
    if(oxy == "OY") {
        for(int x = 0; x <= (point2.x - point1.x) / 2; x++) {
            for(int y = point1.y; y < point2.y; y++) {
                std::swap((picture[y][x + point1.x]), (picture[y][point2.x - x]));
            }
        }
    }
    if(oxy == "OX") {
        for(int x = point1.x; x < point2.x; x++) {
            for(int y = 0; y < (point2.y - point1.y) / 2; y++) {
                std::swap((picture[y + point1.y][x]), (picture[point2.y - y][x]));
            }
        }
    }
    Pixel red;
    red.b = 0;
    red.g = 0;
    red.r = 255;
    picture[point2.y][point2.x] = red;
}


void Bitmap::drawRectangle(Point left, Point right, int w, Bitmap::Pixel color) {
    if (w == 0) return;
    for (int x = left.x; x <= right.x; x++) {
        picture[left.y][x] = color;
        picture[right.y][x] = color;
    }
    for (int y = left.y; y <= right.y; y++) {
        picture[y][left.x] = color;
        picture[y][right.x] = color;
    }
    Point new_left;
    new_left.x = left.x + 1;
    new_left.y = left.y + 1;
    Point new_right;
    new_right.x = right.x - 1;
    new_right.y = right.y - 1;
    drawRectangle(new_left, new_right, w - 1, color);
}

void Bitmap::fillRectangle(Point s, Point f, int w, Bitmap::Pixel color) {
    for (int x = s.x + w; x <= f.x - w; x++) {
        for (int y = s.y + w; y <= f.y - w; y++) {
            picture[y][x] = color;
        }
    }
}
/*
void Bitmap::drawCircle(Point center, int rad, Bitmap::Pixel color, int w) {
    int x = 0;
    int y = rad;
    int delta = 3 - 2 * rad;
    int error = 0;
    while (y >= 0) {
        picture[center.x + x][center.y + y] = color;
        picture[center.x + x][center.y - y] = color;
        picture[center.x - x][center.y + y] = color;
        picture[center.x - x ][center.y - y] = color;
        error = 2 * (delta + y) - 1;
        if (delta < 0 && error <= 0) {
            ++x;
            delta += 2 * x + 1;
            continue;
        }
        error = 2 * (delta - x) - 1;
        if (delta > 0 && error > 0) {
            --y;
            delta += 1 - 2 * y;
            continue;
        }
        ++x;
        delta += 2 * (x - y);
        --y;
    }
}*/

void Bitmap::drawCircle(Point center, int rad, Bitmap::Pixel color, int w, std::vector<std::pair<Point, bool>> &circle,
                        bool flag) {
    int x = 0;
    int y = rad;
    int delta = 1 - 2 * rad;
    int error = 0;
    while (y >= 0) {

        /*
        picture[center.y + y][center.x + x] = Pixel(0, 0, 0);
        picture[center.y + y][center.x - x] = Pixel(0, 0, 0);
        picture[center.y - y][center.x + x] = Pixel(0, 0, 0);
        picture[center.y - y][center.x - x] = Pixel(0, 0, 0);
        circle.push_back(std::make_pair(Point(center.x + x, center.y + y), flag));
        circle.push_back(std::make_pair(Point(center.x - x, center.y + y), flag));
        circle.push_back(std::make_pair(Point(center.x + x, center.y - y), flag));
        circle.push_back(std::make_pair(Point(center.x - x, center.y - y), flag));
        */

        for (auto ny : {+y, -y})
            for (auto nx : {+x, -x})
            {
                picture[center.y + ny][center.x + nx] = {0, 0, 0};
                circle.emplace_back(Point(center.x, center.y), flag);
            }

        error = 2 * (delta + y) - 1;
        if (delta < 0 && error <= 0) {
            ++x;
            delta += 2 * x + 1;
            continue;
        }
        error = 2 * (delta - x) - 1;
        if (delta > 0 && error > 0) {
            --y;
            delta += 1 - 2 * y;
            continue;
        }
        ++x;
        delta += 2 * (x - y);
        --y;
    }
}

void Bitmap::drawLine(Point a, Point b, Bitmap::Pixel color) {
    int deltaX = abs(b.x - a.x);
    int deltaY = abs(b.y - a.y);
    const int signX = a.x < b.x ? 1 : -1;
    const int signY = a.y < b.y ? 1 : -1;

    int error = deltaX - deltaY;

    picture[b.y][b.x] = color;
    while (a.x != b.x || a.y != b.y)
    {
        picture[a.y][a.x] = color;
        const int error2 = error * 2;

        if (error2 > -deltaY)
        {
            error -= deltaY;
            a.x += signX;
        }
        if (error2 < deltaX)
        {
            error += deltaX;
            a.y += signY;
        }
    }
}


void Bitmap::drawPentagram(Point center, int radius, int w, Bitmap::Pixel color) {
    std::vector<std::pair<Point, bool>> circle;
    drawCircle(center, radius - 0, Pixel(0, 0, 0), w, circle, false);
    drawCircle(center, radius - w + 1, Pixel(0, 0, 0), w, std::vector<Point, bool>(), false);

    for(double i = 0; i < w; i++) {
        drawStar(center, radius - i, w, color);
    }
}

void Bitmap::drawStar(const Point &center, int radius, int w, Bitmap::Pixel color) {
    Point vector(0, -radius);
    const Point base(0, -radius);
    const int STAR_ANGLE = 72;
    const double STAR_ANGLE_RADS = (STAR_ANGLE / 180.0)* M_PI;
    double angle = STAR_ANGLE_RADS;
    std::vector<Point> peaks;
    for (size_t i = 0; i < 5; i++) {
        peaks.push_back(vector);
        vector = base;
        vector.rotate(angle);
        angle += STAR_ANGLE_RADS;
    }

    for (auto& peak : peaks) {
        peak += center;
    }

    int i = 0;
    do {
        drawLine(peaks[i], peaks[(i + 2) % 5], color);
        i = (i + 2) % 5;
    } while(i != 0);
}



Point::Point() {}

Point::Point(int x, int y) : x(x), y(y) {}

Point operator+(const Point &first, const Point &second) {
    return {first.x + second.x, first.y + second.y};
}

Point &Point::operator += (const Point &other) {
    *this = *this + other;
    return *this;
}

Point &Point::rotate(double angle) {
    auto save_x = x;
    auto save_y = y;
    x = save_x * cos(angle) - save_y * sin(angle);
    y = save_x * sin(angle) + save_y * cos(angle);
    //TODO
}
