//Created by Richard Chao and Dominic Agoncillo
//Created for the CISP 400 Mandelbrot Set Project
//----------------------------------------------//
// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <complex>
#include "ComplexPlane.h"

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    ComplexPlane y;
    std::cout << y.test() << std::endl;
    return 0;
}