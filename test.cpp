#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "strinx.hpp"

using namespace std;

int main() {
    strinx yazi;
    yazi += "yaziiii ";     // ok
    yazi += 67.f;           // ok
    yazi -= 6;              // takeout 6
    yazi = yazi(3, 8);      // elements 3 to 8
    yazi *= 3;              // multiply
    yazi.back();            // char&: first element
    yazi.canmove();         // bool: can move iterator
    yazi.canmoveback();     // bool: cam move back iterator
    yazi.canmoveline();     // bool: can move line iterator
    yazi.capitalize();      // strinx: capitalize
    yazi.check('a');        // bool: check if value in
    yazi.clear();           // void: clear all element
    yazi.c_str();           // const char*: convert const char*
    yazi.data();            // char&: returning char*
    yazi.ends_with(".png"); // bool: check if it ends with value
    yazi.fill('a');         // void: fill all elements
    yazi.filter('a', "#");  // strinx: replace all value
    yazi.find('a');         // size_t: find value pos 
    yazi.first();           // strinx: first element
    yazi.format();          // soon..
    yazi.front();           // char&: last element
    yazi.get();             // bool: get char by char
    yazi.getline();         // bool: get line by line
    yazi.insert();          // void: insert value
    yazi.iterator();        // size_t&: current iterator
    yazi.last();            // strinx: last element
    yazi.len();             // size_t&: lenght
    yazi.lenght();          // size_t&: lenght
    yazi.linesplit();       // soon..
    yazi.low();             // bool: lower case current char
    yazi.lower();           // strinx: lower case all elements
    yazi.middle();          // char&: middle element
    yazi.move();            // bool: move iterator
    yazi.moveback();        // bool: move back iterator
    yazi.numbers();         // strinx: find all number
    yazi.parse();           // soon..
    yazi.pop_first();       // void: remove first element
    yazi.pop_last();        // void: remove las element
    yazi.print();           // void: print
    yazi.random();          // strinx: randomly sort
    yazi.replace('3', '1'); // void: replace values
    yazi.reset();           // void: reset iterator
    yazi.resize(5);         // void: resize
    yazi.reverse();         // strinx: reverse all elements
    yazi.scan('a');         // size_t: finding values number
    yazi.size();            // size_t: lenght
    yazi.split();           // std::vector<strinx>&:
    yazi.starts_with('!');  // bool: check if it starts with value
    yazi.str();             // string: convert string
    yazi.strip();           // strinx: strip
    yazi.swap();            // void: swap two element
    yazi.sort();            // soon..
    yazi.takeout("%&?*$");  // void: take out value
    yazi.title();           // strinx: make title
    yazi.to_double();       // double: convert double
    yazi.to_float();        // float: convert float
    yazi.to_int();          // int: convert int
    yazi.up();              // bool: upper case current char
    yazi.upper();           // strinx: upper case all elements
    yazi.wrap();            // soon..
    
    return 0;
}
