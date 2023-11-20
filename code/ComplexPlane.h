#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H

// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <complex>
#include <cmath>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

//Constants
const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;
enum State {CALCULATING, DISPLAYING}; 

class ComplexPlane {
public: 
    //public functions:
    ComplexPlane(int pixelWidth, int pixelHeight);
    void draw(RenderTarget& target, RenderStates states) const;
    void zoomIn();
    void zoomOut();
    void setCenter(Vector2i mousePixel);
    void setMouseLocation(Vector2i mousePixel);
    void loadText(Text& text);
    void updateRender();

private:
    //private members:
    State m_state;
    VertexArray m_vArray;
    Vector2f m_mouseLocation;
    Vector2f m_plane_center;
    Vector2f m_plane_size;
    Vector2i m_pixel_size;
    int m_zoomCount;
    float m_aspectRatio;

    //private functions:
    int countIterations(Vector2f coord);
    void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
    Vector2f mapPixelToCoords(Vector2i mousePixel);
};

#endif