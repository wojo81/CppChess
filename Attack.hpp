#pragma once

#include "Army.hpp"

namespace chess {
    class Attack : public Move {
    public:
        Attack(Piece const& attackedPiece) :
            Move{attackedPiece.GetPosition()}, attackedPiece_{attackedPiece} {}

        auto DoAction(Army &, Army & enemies) -> void override {
            enemies.Kill(attackedPiece_);
        }
    private:
        Piece const& attackedPiece_;
    };
}