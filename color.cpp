#include "color.h"

int Color::MAX = 255;

Color::Color()
{
    red = 0;
    green = 0;
    blue = 0;
    alpha = MAX;
}

Color::Color(int r, int g, int b)
{
    red = r;
    green = g;
    blue = b;
    alpha = MAX;
}

Color::Color(int r, int g, int b, int a)
{
    red = r;
    green = g;
    blue = b;
    alpha = a;
}

Color::Color(string hex)
{
    // If invalid hex provided, set color to black
    if (hex.length() != 7 && hex.length() != 9) {
        red = 0;
        green = 0;
        blue = 0;
        alpha = MAX;
    } else if (hex[0] != '#') {
        red = 0;
        green = 0;
        blue = 0;
        alpha = MAX;
    } else {
        red = 16*getDecVal(hex[1]) + getDecVal(hex[2]);
        green = 16*getDecVal(hex[3]) + getDecVal(hex[4]);
        blue = 16*getDecVal(hex[5]) + getDecVal(hex[6]);

        if (hex.length() == 9) {
            alpha = 16*getDecVal(hex[7]) + getDecVal(hex[8]);
        } else {
            alpha = MAX;
        }
    }

    // Check if any of the digits are invalid
    for (int i = 1; i < hex.length(); i++) {
        if (getDecVal(hex[i]) <= 0) {
            red = 0;
            green = 0;
            blue = 0;
            alpha = MAX;
            break;
        }
    }
}

int Color::getRed()
{
    return red;
}

int Color::getGreen()
{
    return green;
}

int Color::getBlue()
{
    return blue;
}

int Color::getAlpha()
{
    return alpha;
}

int Color::getDecVal(char digit)
{
    switch(digit)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'a':
            return 10;
        case 'b':
            return 11;
        case 'c':
            return 12;
        case 'd':
            return 13;
        case 'e':
            return 14;
        case 'f':
            return 15;
        default:
            // If invalid hexadeimal digit
            return -1;
    }
}