#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace std;

// Constants for Mandelbrot set calculations and rendering
const unsigned int MAX_ITER = 128;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;
const int W = sf::VideoMode::getDesktopMode().width;
const int H = sf::VideoMode::getDesktopMode().height;

// State enumeration to manage rendering states
namespace State
{
    enum State
    {
        CALCULATING,
        DISPLAYING,
    };
}

// Class representing the complex plane for Mandelbrot set
class ComplexPlane : public sf::Drawable
{
public:
    // Constructor
    ComplexPlane(int pixelWidth, int pixelheight);

    // Draw function overridden from sf::Drawable
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Functions to manage zoom and centering
    void zoomIn();
    void zoomOut();
    void setCenter(sf::Vector2i mousePixel);
    void setMouseLocation(sf::Vector2i mousePixel);

    // Load and update text information
    void loadText(sf::Text& text);

    // Update the Mandelbrot set rendering
    void updateRender();

private:
    // Private member variables and functions
    sf::VertexArray m_vArray;
    State::State m_state;
    sf::Vector2f m_mouseLocation;
    sf::Vector2i m_pixel_size;
    sf::Vector2f m_plane_center;
    sf::Vector2f m_plane_size;
    int m_zoomCount;
    float m_aspectRatio;

    // Calculate the number of iterations for each point
    int countIterations(sf::Vector2f coord);

    // Map iteration count to RGB color
    void iterationsToRGB(int count, sf::Uint8& r, sf::Uint8& g, sf::Uint8& b);

    // Map a pixel position to complex plane coordinates
    sf::Vector2f mapPixelToCoords(sf::Vector2i mousePixel);
};

#endif // COMPLEXPLANE_H
