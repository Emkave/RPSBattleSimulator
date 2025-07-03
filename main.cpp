#include "SFML/Graphics.hpp"
#include "vld.h"
#include "object.h"
#include <vector>
#include "settings.h"



using namespace sf;

std::vector<object> spawn_objects() {
    std::vector<object> objects;
    objects.reserve(ROCK_AMOUNT + PAPER_AMOUNT + SCISSOR_AMOUNT);

    for (size_t i=0; i<ROCK_AMOUNT; i++) {
        objects.emplace_back(0);
    }

    for (size_t i=0; i<PAPER_AMOUNT; i++) {
        objects.emplace_back(1);
    }

    for (size_t i=0; i<SCISSOR_AMOUNT; i++) {
        objects.emplace_back(2);
    }

    return objects;
}



int main(void) {
    ContextSettings settings;
    settings.antiAliasingLevel = 4;
    RenderWindow window (VideoMode({WIN_LENGTH, WIN_HEIGHT}), "RPS", Style::Default, settings);
    window.setFramerateLimit(120);

    std::vector<object> objects = spawn_objects();



    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }
        window.clear(Color::Black);
        window.draw(objects[0].get_shape());
        window.display();
    }

    return 0;
}