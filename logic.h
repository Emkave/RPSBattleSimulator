#ifndef LOGIC_H
#define LOGIC_H
#include "object.h"

const enum choice {ROCK=0, PAPER=1, SCISSORS=2};
const enum result {TIE, P1W, P2W};
inline const char * choice_str[] = {"rock", "paper", "scissors"};

inline result determine_winner(const choice p1, const choice p2) noexcept {
    switch ((3 + p1 - p2) % 3) {
        case 0:
            return TIE;

        case 1:
            return P1W;

        default:
            return P2W;
    }
}


inline void swap_winner(const result winner) {

}

#endif //LOGIC_H
