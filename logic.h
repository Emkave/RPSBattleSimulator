#ifndef LOGIC_H
#define LOGIC_H

inline uint8_t determine_winner(const uint8_t p1, const uint8_t p2) noexcept {
    return (3 + p1 - p2) % 3;
}


#endif //LOGIC_H
