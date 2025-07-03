#ifndef OBJECT_H
#define OBJECT_H
#include <stdexcept>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "settings.h"




using namespace sf;

class object {
private:
    CircleShape shape;
    int8_t type = 0;
    float dx;
    float dy;

    static size_t rock_amount;
    static size_t scissor_amount;
    static size_t paper_amount;

    Texture texture;

public:
    explicit object(const int8_t && type) {
        this->shape.setRadius(10.f);
        this->shape.setOutlineColor(Color::Green);
        this->shape.setFillColor(Color::White);

        switch (type) {
            case 0:
                object::rock_amount++;
                if (!texture.loadFromFile(ROCK_PNG_PATH)) {
                    throw std::runtime_error("Failed to load rock texture");
                }
                shape.setTexture(&texture);
                break;

            case 1:
                object::scissor_amount++;
                if (!texture.loadFromFile(SCISSOR_PNG_PATH)) {
                    throw std::runtime_error("Failed to load scissor texture");
                }
                shape.setTexture(&texture);
                break;

            case 2:
                object::paper_amount++;
                if (!texture.loadFromFile(PAPER_PNG_PATH)) {
                    throw std::runtime_error("Failed to load paper texture");
                }
                shape.setTexture(&texture);
                break;

            default:
                throw std::runtime_error("object::object() -> Invalid type given.\n");
        }


    }


    inline CircleShape & get_shape() noexcept;


};


size_t object::paper_amount = 0;
size_t object::scissor_amount = 0;
size_t object::rock_amount = 0;


inline CircleShape & object::get_shape() noexcept {
    return this->shape;
}


#endif //OBJECT_H
