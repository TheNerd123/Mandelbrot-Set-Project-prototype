//Created by Richard Chao and Dominic Agoncillo
//Created for the CISP 400 Mandelbrot Set Project
//----------------------------------------------//

//include our header file that has all of our important libraries
#include "ComplexPlane.h"

//start of our program
int main()
{
    //Getting the desktop resolution
    VideoMode vm(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
    RenderWindow window(vm, "Mandelbrot Set", Style::Default);

    ComplexPlane fractal(1, 1);
    Font font;
    Text text;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) { // Quits the game when the window is closed
				window.close();
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Right) {
                    fractal.zoomOut();
                    fractal.setCenter(Vector2i(event.mouseButton.x, event.mouseButton.y));
                }
                else if (event.mouseButton.button == Mouse::Left) {
                    fractal.zoomIn();
                    fractal.setCenter(Vector2i(event.mouseButton.x, event.mouseButton.y));
                }
            }
            if(event.type == sf::Event::MouseMoved) {
                fractal.setMouseLocation(Vector2i(event.mouseButton.x, event.mouseButton.y));
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) { //press escape key to exit program
                window.close();
            }
        }
    }

    return 0;
}