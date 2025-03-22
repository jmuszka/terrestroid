#include <string>
using namespace std;

class Color
{
private:
    string hex;
    int red;
    int green;
    int blue;
    int alpha;
    static int MAX;
    int getDecVal(char digit);
public:
    Color();
    Color(int r, int g, int b);
    Color(int r, int g, int b, int a);
    Color (string hex);
    
    int getRed();
    int getGreen();
    int getBlue();
    int getAlpha();
};