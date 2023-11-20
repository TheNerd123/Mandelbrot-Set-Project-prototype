#include "ComplexPlane.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(W, H), "Mandelbrot");
    sf::CircleShape shape(100.f);
    ComplexPlane complexPlane(W, H);
    sf::Font font;
    if (!font.loadFromFile("./fonts/champagne_limousines/Champagne Limousines.ttf"))
    {
        cout << "ERROR";
        return -1;
    }
    sf::Text text;
    text.setFont(font);

    sf::Image image;
    image.create(W, H);
    sf::Texture texture;

      while (window.isOpen())
    {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    complexPlane.zoomOut();
                    complexPlane.setCenter(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    complexPlane.zoomIn();
                    complexPlane.setCenter(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                complexPlane.setMouseLocation(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        // Update Scene
        complexPlane.updateRender();

        // Load Text
        complexPlane.loadText(text);

        // Draw Scene
        window.clear();
        window.draw(complexPlane);
        window.draw(text);
        window.display();
    }

    return 0;
}