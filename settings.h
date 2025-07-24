#ifndef SETTINGS_H
#define SETTINGS_H

#define SCISSOR_PNG_PATH "../assets/scissors.png"
#define ROCK_PNG_PATH "../assets/rock.png"
#define PAPER_PNG_PATH "../assets/paper.png"
#define ROCK_AMOUNT 1
#define PAPER_AMOUNT 1
#define SCISSOR_AMOUNT 1
#define WIN_HEIGHT 720
#define WIN_LENGTH 1280

constexpr unsigned field_x_up_limit = WIN_LENGTH-20;
constexpr unsigned field_x_low_limit = 20;
constexpr unsigned field_y_up_limit = WIN_HEIGHT-20;
constexpr unsigned field_y_low_limit = 100;

#endif //SETTINGS_H
