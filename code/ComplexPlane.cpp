#include "ComplexPlane.h"

// Constructor: Initializes values for rendering the complex plane
ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixel_size.x = pixelWidth;
    m_pixel_size.y = pixelHeight;
    m_aspectRatio = static_cast<double>(pixelWidth) / static_cast<double>(pixelHeight);
    m_plane_center = {0, 0}; // Starting center of the plane
    m_state = State::CALCULATING; // Initial state
    m_vArray.setPrimitiveType(sf::Points); // Set the primitive type to points
    m_vArray.resize(pixelWidth * pixelHeight); // Resize vertex array to fit the window
    updateRender(); // Perform initial render
}

// Draw function: Draws the Mandelbrot set onto the target
void ComplexPlane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_vArray); // Draw the vertex array to the render target
}

// UpdateRender function: Updates the rendering of the Mandelbrot set
void ComplexPlane::updateRender()
{
    if (m_state == State::CALCULATING) 
    {
        // Iterating over each pixel to calculate Mandelbrot set color
        for (int j = 0; j < m_pixel_size.x; j++) 
        {
            for (int i = 0; i < m_pixel_size.y; i++) 
            {
                // Set the position for each point
                m_vArray[j + i * m_pixel_size.x].position = sf::Vector2f(j, i);

                // Map the pixel to complex plane coordinates
                sf::Vector2f coord = mapPixelToCoords(sf::Vector2i(j, i));

                // Count the number of iterations for the current coordinate
                int count = countIterations(coord);

                // Map the iteration count to RGB values
                sf::Uint8 r, g, b;
                iterationsToRGB(count, r, g, b);

                // Set the color for the current point
                m_vArray[j + i * m_pixel_size.x].color = sf::Color(r, g, b);
            }
        }
        m_state = State::DISPLAYING; // Change state to displaying after calculating
    }
}

// ZoomIn function: Increases the zoom level of the Mandelbrot set
void ComplexPlane::zoomIn()
{
    m_zoomCount++;
    float zoomed_x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float zoomed_y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size.x = zoomed_x;
    m_plane_size.y = zoomed_y;
    m_state = State::CALCULATING; // Set state to recalculating after zoom
}

// ZoomOut function: Decreases the zoom level of the Mandelbrot set
void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    float zoomed_x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float zoomed_y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size.x = zoomed_x;
    m_plane_size.y = zoomed_y;
    m_state = State::CALCULATING; // Set state to recalculating after zoom
}

// SetCenter function: Sets the center of the Mandelbrot view to the given pixel
void ComplexPlane::setCenter(sf::Vector2i mousePixel)
{
    sf::Vector2f coords = mapPixelToCoords(mousePixel);
    m_plane_center.x = coords.x;
    m_plane_center.y = coords.y;
}

// SetMouseLocation function: Updates the mouse location in the complex plane
void ComplexPlane::setMouseLocation(sf::Vector2i mousePixel)
{
    sf::Vector2f coords = mapPixelToCoords(mousePixel);
    m_mouseLocation = coords;
}

// LoadText function: Loads the information text to be displayed on screen
void ComplexPlane::loadText(sf::Text& text)
{
    stringstream mandelInfo;
    mandelInfo << "Mandelbrot Set\n";
    mandelInfo << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")\n";
    mandelInfo << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n";
    mandelInfo << "Left-click to Zoom in\n";
    mandelInfo << "Right-click to Zoom out\n";
    text.setString(mandelInfo.str()); // Set the text to display
}

// CountIterations function: Counts the iterations before escaping the set
int ComplexPlane::countIterations(sf::Vector2f coord)
{
    complex<double> z = 0;
    complex<double> c(coord.x, coord.y);
    int iterations = 0;

    // Iteration loop to check if the point escapes the set boundary; from https://en.wikipedia.org/wiki/Mandelbrot_set
    while (abs(z) < 2.0 && iterations < MAX_ITER) 
    {
        z = z*z + c;
        iterations++;
    }
    return iterations;
}


void ComplexPlane::iterationsToRGB(int count, sf::Uint8& r, sf::Uint8& g, sf::Uint8& b)
{
    if (count == MAX_ITER) 
    {
        r = g = b = 0; // Black for points inside the Mandelbrot set
    } 
    else 
    {
        const int regionSize = MAX_ITER / 5;
        int region = count / regionSize;

        switch(region)
        {
            case 0: // Purple / Blue
                r = 128 - (count % regionSize); // Decrease red to transition from purple to blue
                g = 0;
                b = 255;
                break;
            case 1: // Turquoise
                r = 0;
                g = 255;
                b = 255 - (count % regionSize); // Decrease blue to transition to green
                break;
            case 2: // Green
                r = 0;
                g = 255;
                b = 0;
                break;
            case 3: // Yellow
                r = 255;
                g = 255 - (count % regionSize); // Decrease green to transition to red
                b = 0;
                break;
            case 4: // Red
                r = 255;
                g = 0;
                b = 0;
                break;
            default: // Fallback color
                r = g = b = 255; // White
                break;
        }
    }
}


sf::Vector2f ComplexPlane::mapPixelToCoords(sf::Vector2i mousePixel)
{
    float x = (static_cast<float>(mousePixel.x) / m_pixel_size.x) * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0f);
    float y = (static_cast<float>(mousePixel.y) / m_pixel_size.y) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0f);
    return sf::Vector2f(x, y);
}