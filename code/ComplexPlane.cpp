#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixel_size.x = pixelWidth;
    m_pixel_size.y = pixelHeight;
    m_aspectRatio = static_cast<double>(m_pixel_size.x) / static_cast<double>(m_pixel_size.y);
    m_plane_center = {0, 0};
    m_state = State::CALCULATING;
    m_vArray.setPrimitiveType(sf::Points);
    m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_vArray);
}

void ComplexPlane::updateRender()
{
    if (m_state == State::CALCULATING) 
    {
        for (int j = 0; j < m_pixel_size.x; j++) 
        {
            for (int i = 0; i < m_pixel_size.y; i++) 
            {
                m_vArray[j + i * m_pixel_size.x].position = sf::Vector2f(j, i);
                sf::Vector2f coord = mapPixelToCoords(sf::Vector2i(j, i));
                int count = countIterations(coord);

                sf::Uint8 r, g, b;
                iterationsToRGB(count, r, g, b);
                m_vArray[j + i * m_pixel_size.x].color = sf::Color(r, g, b);
            }
        }
        m_state = State::DISPLAYING;
    }
}

void ComplexPlane::zoomIn()
{
    m_zoomCount++;
    float zoomed_x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float zoomed_y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size.x = zoomed_x;
    m_plane_size.y = zoomed_y;
    m_state = State::CALCULATING;
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    float zoomed_x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float zoomed_y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size.x = zoomed_x;
    m_plane_size.y = zoomed_y;
    m_state = State::CALCULATING;
}

void ComplexPlane::setCenter(sf::Vector2i mousePixel)
{
    sf::Vector2f coords = mapPixelToCoords(mousePixel);
    m_plane_center.x = coords.x;
    m_plane_center.y = coords.y;
}

void ComplexPlane::setMouseLocation(sf::Vector2i mousePixel)
{
    sf::Vector2f coords = mapPixelToCoords(mousePixel);
    m_mouseLocation = coords;
}

void ComplexPlane::loadText(sf::Text& text)
{
    stringstream mandelInfo;
    mandelInfo << "Mandelbrot Set\n";
    mandelInfo << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")\n";
    mandelInfo << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n";
    mandelInfo << "Left-click to Zoom in\n";
    mandelInfo << "Right-click to Zoom out\n";
    text.setString(mandelInfo.str());
}

int ComplexPlane::countIterations(sf::Vector2f coord)
{
    complex<double> z = 0;
    complex<double> c(coord.x, coord.y);
    int iterations = 0;

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