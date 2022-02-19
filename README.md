## strinx

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Strinx.hpp"

using namespace std;

int main() {
    strinx yazi = "cok duzgun bir yazi";
    cout << yazi.random() << '\n'; // artik degil
    
    putchar('\n');
    
    strinx cumle = "bu da cok kelimeli bi yazi"; // harbi oyle
    for (auto i : cumle.split())
        cout << i << '\n';
        
    putchar('\n');
    
    strinx fikir = "Turkiye'de yoneticiler baskici ve gericidir.";
    fikir = fikir.filter("baskici", "#####");
    fikir = fikir.filter("gerici", "harika");
    fikir.print();
    
    putchar('\n');
    
    strinx ters_yazi = "ad ub etsi izay zud"; // cok dogru
    cout << ters_yazi.reverse() << '\n';
    
    return 0;
}
```
