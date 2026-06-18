//g++ -Wall -Wextra src/vec2_test.cpp -o vec2_test.exe && ./vec2_test.exe
#include <iostream>
#include "vec2.h"
using namespace std;

int main(){
    Vec2 a{3, 4};
    Vec2 b{1, -2};

    cout << "a = (" << a.x << ", " << a.y << ")\n";
    cout << "b = (" << b.x << ", " << b.y << ")\n";

    cout << "a + b = (" << (a+b).x << ", " << (a+b).y << ")\n";
    cout << "a - b = (" << (a-b).x << ", " << (a-b).y << ")\n";
    cout << "a * 2 = (" << (a*2).x << ", " << (a*2).y << ")\n";

    cout << "|a| = (" << a.length() << ")\n";
}