#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "strinx.hpp"

using namespace std;

int main() {
    strinx yazi = "cok duzgun bir yazi";
    cout << yazi.random() << '\n'; // artik degil
    
    yazi = "bu da cok kelimeli bi yazi"; // harbi oyle
    for (auto i : yazi.split())
        cout << i << '\n';
    
    return 0;
}
