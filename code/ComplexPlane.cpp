#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) {
    m_pixel_size.x = pixelWidth;
    m_pixel_size.y = pixelHeight;
    
    float temp1 = pixelWidth;
    float temp2 = pixelHeight;
    m_aspectRatio = temp2/temp1;

    m_plane_center = {0, 0};
    m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
    m_zoomCount = 0;
    m_state = CALCULATING;
    m_vArray.setPrimitiveType(Points);
    m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const {
    target.draw(m_vArray);
}

void ComplexPlane::updateRender() {
    if(m_state == CALCULATING) {
        for(int j = 0.0; j < VideoMode::getDesktopMode().width; j++) {
            for(int i = 0.0; i < VideoMode::getDesktopMode().height; i++) {
                m_vArray[j + i * m_pixel_size.x].position = {j, i};
                int count = countIterations(mapPixelToCoords(Vector2i(j, i)));
                Uint8 r, g, b;
                //iterationsToRGB(count, r, g, b);
            }
        }
    }
}

void ComplexPlane::zoomIn() {
    m_zoomCount++;
    float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_plane_size = {x, y};
    m_state = CALCULATING;
}

void ComplexPlane::zoomOut() {
    m_zoomCount--;
    float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_plane_size = {x, y};
    m_state = CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel) {
    m_plane_center = mapPixelToCoords(mousePixel);
    m_state = CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel){
    m_mouseLocation = mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text& text) {

}

int ComplexPlane::countIterations(Vector2f coord) {
    return (coord.y * coord.x) + coord.x;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {

}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {
    float x = ((mousePixel.x - 0)/(VideoMode::getDesktopMode().width - 0)) * (m_plane_size.x) + (m_plane_center.x - m_plane_size.x / 2.0);
    float y = ((mousePixel.y - VideoMode::getDesktopMode().height )/(0 - VideoMode::getDesktopMode().height)) * (m_plane_size.y) + (m_plane_center.y - m_plane_size.y / 2.0);
    return {x, y};
}

