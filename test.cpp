#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "strinx.hpp"

using namespace std;

auto main() -> int {
    stx yazi;
    yazi += "yaziiii ";
    yazi = 67.f;
    yazi -= 6;
    int num = (int)yazi;
    yazi = yazi(3, 8);
    yazi *= 3;
    yazi % "qweq";
    yazi /= 'w';
    yazi.fill("woaw");
    yazi.filter('a', "#");
    yazi.lower();
    yazi.random();
    yazi.reverse();
    yazi.starts_with('!');
    yazi.takeout("w");
    yazi.upper();
    yazi.pop();
    yazi.push("woaooaow");
    yazi.in('a');
    yazi.is_lower();
    yazi.is_upper();
    return 0;
};
