#include "SFML/Graphics.hpp"
#include "vld.h"
#include "object.h"
#include <vector>
#include "logic.h"
#include "settings.h"

using namespace sf;



int main(void) {
    ContextSettings settings;
    settings.antiAliasingLevel = 4;
    RenderWindow window (VideoMode({WIN_LENGTH, WIN_HEIGHT}), "RPS", Style::Default, State::Windowed, settings);
    window.setFramerateLimit(60);

    VertexArray lines(PrimitiveType::LineStrip, 5);
    lines[0].position = Vector2f(20, 100);
    lines[1].position = Vector2f(WIN_LENGTH-20, 100);
    lines[2].position = Vector2f(WIN_LENGTH-20, WIN_HEIGHT-20);
    lines[3].position = Vector2f(20, WIN_HEIGHT-20);
    lines[4].position = Vector2f(20, 100);

    const Font font ("../assets/arial.ttf");

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }
        window.clear(Color::Black);

        window.draw(lines);

        window.display();
    }

    return 0;
}