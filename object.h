#ifndef OBJECT_H
#define OBJECT_H
#include <stdexcept>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include "settings.h"
#include <random>


using namespace sf;

class object {
private:
    CircleShape shape;
    uint8_t type = 0;
    float dx = 0;
    float dy = 0;

    static size_t rock_amount;
    static size_t scissor_amount;
    static size_t paper_amount;

    static Texture rock_texture;
    static Texture scissor_texture;
    static Texture paper_texture;

public:
    explicit object(const uint8_t && type) {
        this->shape.setRadius(10.f);
        this->shape.setOrigin({20.f, 20.f});
        this->shape.setOutlineColor(Color::Green);


        static std::random_device rd;
        static std::mt19937 gen(rd());

        switch (type) {
            case 0:
                object::rock_amount++;
                this->shape.setFillColor(Color::Red);
                {
                    const std::uniform_real_distribution<float> dist_x(0.f, WIN_LENGTH - 1);
                    const std::uniform_real_distribution<float> dist_y(110.f, WIN_HEIGHT - 1);
                    this->shape.setPosition({dist_x(gen), dist_y(gen)});
                }
                this->type = 0;
                break;

            case 2:
                object::scissor_amount++;
                this->shape.setFillColor(Color::White);
                {
                    const std::uniform_real_distribution<float> dist_x(WIN_LENGTH / 4.f, 3.f * WIN_LENGTH / 4.f);
                    const std::uniform_real_distribution<float> dist_y(110.f, WIN_HEIGHT / 4.f);
                    shape.setPosition({dist_x(gen), dist_y(gen)});
                }
                this->type = 2;
                break;

            case 1:
                object::paper_amount++;
                {
                    const std::uniform_real_distribution<float> dist_x(WIN_LENGTH / 2.f, WIN_LENGTH);
                    const std::uniform_real_distribution<float> dist_y(110.f, WIN_HEIGHT);
                    shape.setPosition({dist_x(gen), dist_y(gen)});
                }
                this->shape.setFillColor(Color::Yellow);
                this->type = 1;
                break;

            default:
                throw std::runtime_error("object::object() -> Invalid type given.\n");
        }

        constexpr float speed = 150.f;
        const std::uniform_real_distribution<float> dist_angle(0.f, 2.f * 3.1415926f);
        const float angle = dist_angle(gen);

        this->dx = std::cos(angle) * speed;
        this->dy = std::sin(angle) * speed;
    }

    inline CircleShape & get_shape() noexcept;
    inline void update(const float dt);
    inline uint8_t get_type() const noexcept { return type; }
    inline void convert_to(uint8_t new_type);
    static void init();
    inline static size_t get_type_amount(const uint8_t && type) noexcept;

};

size_t object::paper_amount = 0;
size_t object::scissor_amount = 0;
size_t object::rock_amount = 0;

Texture object::rock_texture;
Texture object::paper_texture;
Texture object::scissor_texture;


inline CircleShape & object::get_shape() noexcept {
    return this->shape;
}


inline void object::update(const float dt) {
    auto pos = shape.getPosition();
    pos.x += dx * dt;
    pos.y += dy * dt;

    if (pos.x - shape.getRadius() <= 0.f || pos.x + shape.getRadius() >= WIN_LENGTH) {
        dx = -dx;
    }

    if (pos.y - shape.getRadius() <= 90.f || pos.y + shape.getRadius() >= WIN_HEIGHT) {
        dy = -dy;
    }

    shape.setPosition(pos);
}


inline void object::convert_to(const uint8_t new_type) {
    switch (this->type) {
        case 0:
            object::rock_amount--;
            break;

        case 1:
            object::paper_amount--;
            break;

        case 2:
            object::scissor_amount--;
            break;
        default: break;
    }

    this->type = new_type;

    switch (this->type) {
        case 0:
            //shape.setTexture(&rock_texture);
            this->shape.setFillColor(Color::Red);
            object::rock_amount++;
            break;
        case 2:
            //shape.setTexture(&scissor_texture);
            this->shape.setFillColor(Color::White);
            object::scissor_amount++;
            break;
        case 1:
            //shape.setTexture(&paper_texture);
            this->shape.setFillColor(Color::Yellow);
            object::paper_amount++;
            break;
        default:
            throw std::runtime_error("convert_to() -> Invalid type assigned!");
    }
}


inline void object::init() {
    if (rock_texture.getSize().x == 0) {
        if (!rock_texture.loadFromFile(ROCK_PNG_PATH)) {
            throw std::runtime_error("Failed to load rock texture");
        }
    }

    if (scissor_texture.getSize().x == 0) {
        if (!scissor_texture.loadFromFile(SCISSOR_PNG_PATH)) {
            throw std::runtime_error("Failed to load scissor texture");
        }
    }

    if (paper_texture.getSize().x == 0) {
        if (!paper_texture.loadFromFile(PAPER_PNG_PATH)) {
            throw std::runtime_error("Failed to load paper texture");
        }
    }
}


inline size_t object::get_type_amount(const uint8_t && type) noexcept {
    switch (type) {
        case 0:
            return object::rock_amount;

        case 1:
            return object::paper_amount;

        case 2:
            return object::scissor_amount;

        default:
            return -1;
    }
}



#endif //OBJECT_H
