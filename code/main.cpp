#include "ComplexPlane.h"

int main()
{
    // Create an SFML window with dimensions W x H, titled "Mandelbrot"
    sf::RenderWindow window(sf::VideoMode(W, H), "Mandelbrot");

    // Initialize ComplexPlane for rendering the Mandelbrot set
    ComplexPlane complexPlane(W, H);

    // Load a font for displaying text
    sf::Font font;
    if (!font.loadFromFile("./fonts/champagne_limousines/Champagne Limousines.ttf"))
    {
        cout << "ERROR: Font unable to load\n";
        return -1;
    }

    // Set up the text to be used for displaying information
    sf::Text text;
    text.setFont(font);

    // Event loop: Keep running as long as the window is open
    while (window.isOpen())
    {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close the window if the close event is triggered
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Handle mouse button presses for zooming in and out
            if (event.type == sf::Event::MouseButtonPressed) 
            {
                if (event.mouseButton.button == sf::Mouse::Right) 
                {
                    complexPlane.zoomOut();
                    complexPlane.setCenter(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                }
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    complexPlane.zoomIn();
                    complexPlane.setCenter(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                }
            }

            // Update the mouse location in the complex plane on mouse move
            if (event.type == sf::Event::MouseMoved) 
            {
                complexPlane.setMouseLocation(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            }
        }

        // Close the window if the Escape key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        // Update the Mandelbrot rendering
        complexPlane.updateRender();

        // Load the text information onto the screen
        complexPlane.loadText(text);

        // Drawing sequence: clear, draw, and display
        window.clear();
        window.draw(complexPlane);
        window.draw(text);
        window.display();
    }

    return 0;
}
