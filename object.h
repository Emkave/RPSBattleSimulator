#ifndef OBJECT_H
#define OBJECT_H
#include <stdexcept>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "settings.h"
#include <random>


using namespace sf;

class object {
private:
    CircleShape shape;

    static Texture rock_texture;
    static Texture paper_texture;
    static Texture scissor_texture;

    const uint8_t type = 0;

    float x;
    float y;
    float dx;
    float dy;


public:
    explicit object(const uint8_t && type) : type(type) {
        this->shape.setRadius(20);
        this->shape.setFillColor(Color::White);

        switch (this->type) {
            case 0:
                break;

            case 1:
                this->shape.setFillColor(Color::Yellow);
                break;

            case 2:
                this->shape.setFillColor(Color::Red);
                break;

            default:
                throw std::runtime_error("object::object() -> Invalid type given.");
        }

        const float fxll = field_x_low_limit + this->shape.getRadius() + 5;
        const float fxul = field_x_up_limit - this->shape.getRadius() - 5;
        const float fyll = field_y_low_limit + this->shape.getRadius() + 5;
        const float fyul = field_y_up_limit - this->shape.getRadius() - 5;

        std::random_device rd;
        std::mt19937 gen(rd());
        const std::uniform_real_distribution<float> x_pos (fxll, fxul);
        const std::uniform_real_distribution<float> y_pos (fyll, fyul);
        const std::uniform_real_distribution<float> ddx (-30, 30);
        const std::uniform_real_distribution<float> ddy (-30, 30);

        this->x = x_pos(gen);
        this->y = y_pos(gen);
        this->dx = ddx(gen);
        this->dy = ddy(gen);

        this->shape.setPosition(Vector2f{this->x, this->y});
    }

    inline CircleShape get_shape(void) const noexcept {return this->shape;}
    inline float * get_x(void) noexcept {return &this->x;}
    inline float * get_y(void) noexcept {return &this->y;}
    inline float * get_dx(void) noexcept {return &this->dx;}
    inline float * get_dy(void) noexcept {return &this->dy;}
    inline uint8_t get_type(void) const noexcept {return this->type;}
    inline Vector2f get_delta(void) const noexcept {return Vector2f(this->dx, this->dy);}

    void update(const size_t dt) {
        const float fxll = field_x_low_limit + this->shape.getRadius() + 5;
        const float fxul = field_x_up_limit - this->shape.getRadius() - 5;
        const float fyll = field_y_low_limit + this->shape.getRadius() + 5;
        const float fyul = field_y_up_limit - this->shape.getRadius() - 5;

        if ((this->x > fxul) ^ (this->x < fxll)) {
            this->dx = -this->dy;
        }

        if ((this->y > fyul) ^ (this->y < fyll)) {
            this->dy = -this->dy;
        }

        this->x += (this->dx * dt / 1000);
        this->y += (this->dy * dt / 1000);

        this->shape.setPosition(Vector2f{this->x, this->y});
    }

};

Texture object::rock_texture = Texture(ROCK_PNG_PATH);
Texture object::paper_texture = Texture(PAPER_PNG_PATH);
Texture object::scissor_texture = Texture(SCISSOR_PNG_PATH);





#endif //OBJECT_H
