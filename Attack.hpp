#pragma once

#include "Army.hpp"
#include "Cloner.hpp"

namespace chess {
    class Attack : public Cloner<Move, Attack> {
    public:
        Attack(Position const position, int const attackedPieceIndex) :
            Cloner{position}, attackedPieceIndex_{attackedPieceIndex} {}

        auto DoAction(Army &, Army & enemies) -> void override {
            enemies.Take(attackedPieceIndex_);
        }
    private:
        int const attackedPieceIndex_;
    };
}