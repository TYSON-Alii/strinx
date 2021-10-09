## strinx

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "strinx.hpp"

using namespace std;

int main() {
    strinx yazi = "cok duzgun bir yazi";
    cout << yazi.random() << '\n'; // artik degil
    
    strinx cumle = "bu da cok kelimeli bi yazi"; // harbi oyle
    for (auto i : cumle.split())
        cout << i << '\n';
    
    strinx fikir = "Turkiye'de yoneticiler baskici ve gericidir.";
    fikir = fikir.filter("baskici", "#######");
    fikir = fikir.filter("gerici", "harika");
    yazi.print();
    
    return 0;
}
```
