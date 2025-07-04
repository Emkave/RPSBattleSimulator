#include "SFML/Graphics.hpp"
#include "vld.h"
#include "object.h"
#include <vector>

#include "logic.h"
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
    RenderWindow window (VideoMode({WIN_LENGTH, WIN_HEIGHT}), "RPS", Style::Default, State::Windowed, settings);
    window.setFramerateLimit(60);

    //object::init();

    const Font font ("../assets/arial.ttf");
    Text r_text (font, "");
    Text p_text (font, "");
    Text s_text (font, "");

    r_text.setFillColor(Color::Cyan);
    p_text.setFillColor(Color::Cyan);
    s_text.setFillColor(Color::Cyan);

    r_text.setPosition({0, 0});
    p_text.setPosition({0, 30});
    s_text.setPosition({0, 60});

    std::vector<object> objects = spawn_objects();

    Clock clock;

    while (window.isOpen()) {
        r_text.setString("Rock amount: " + std::to_string(object::get_type_amount(0)));
        p_text.setString("Paper amount: " + std::to_string(object::get_type_amount(1)));
        s_text.setString("Scissor amount: " + std::to_string(object::get_type_amount(2)));

        while (const std::optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }
        window.clear(Color::Black);

        const float dt = clock.restart().asSeconds();

        for (size_t i=0; i<objects.size(); i++) {
            objects[i].update(dt);

            for (size_t j=i+1; j<objects.size(); j++) {
                if (i != j && objects[i].get_type() != objects[j].get_type()) {
                    auto & obj1 = objects[i];
                    auto & obj2 = objects[j];

                    const Vector2f delta = obj1.get_shape().getPosition() - obj2.get_shape().getPosition();
                    const float dist2 = delta.x * delta.x + delta.y * delta.y;
                    const float min_dist = obj1.get_shape().getRadius() * 2.f;

                    if (dist2 < min_dist * min_dist) {
                        const uint8_t winner = determine_winner(obj1.get_type(), obj2.get_type());

                        if (winner == 1) {
                            obj2.convert_to(obj1.get_type());
                        } else if (winner == 2) {
                            obj1.convert_to(obj2.get_type());
                        }
                    }
                }
            }

            window.draw(objects[i].get_shape());
        }

        window.draw(r_text);
        window.draw(p_text);
        window.draw(s_text);

        window.display();
    }

    return 0;
}