#ifndef OBJECT_H
#define OBJECT_H
#include <stdexcept>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "settings.h"
#include <random>


using namespace sf;

class object {
protected:
    CircleShape shape;

private:

public:
    virtual ~object() = default;
    virtual CircleShape get_shape(void) const noexcept;
    virtual const uint8_t get_type(void) const noexcept;
};


class rock final : public object {
private:
    static Texture texture;
    static uint8_t type;

public:
    inline CircleShape get_shape(void) const noexcept override {return this->shape;}
    inline const uint8_t get_type(void) const noexcept override {return rock::type;}

    static void init(void) {
        if (!rock::texture.loadFromFile(ROCK_PNG_PATH)) {
            throw std::runtime_error("rock::init() -> Invalid path.");
        }

        rock::type = 0;
    }
};


class paper final : public object {
private:
    static Texture texture;
    static uint8_t type;

public:
    inline CircleShape get_shape(void) const noexcept override {return this->shape;}
    inline const uint8_t get_type(void) const noexcept override {return paper::type;}

    static void init(void) {
        if (!paper::texture.loadFromFile(PAPER_PNG_PATH)) {
            throw std::runtime_error("paper::init() -> Invalid path.");
        }

        paper::type = 1;
    }
};


class scissors final : public object {
private:
    static Texture texture;
    static uint8_t type;

public:
    inline CircleShape get_shape(void) const noexcept override {return this->shape;}
    inline const uint8_t get_type(void) const noexcept override {return scissors::type;}

    static void init(void) {
        if (!scissors::texture.loadFromFile(SCISSOR_PNG_PATH)) {
            throw std::runtime_error("scissors::init() -> Invalid path.");
        }

        scissors::type = 2;
    }
};




#endif //OBJECT_H
