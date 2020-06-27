#pragma once

#include "Army.hpp"
#include "Cloner.hpp"

namespace chess {
    class Attack : public Cloner<Move, Attack> {
    public:
        Attack(Piece const& attackedPiece) :
            Cloner{attackedPiece.GetPosition()}, attackedPiece_{attackedPiece} {}

        auto DoAction(Army &, Army & enemies) -> void override {
            enemies.Kill(attackedPiece_);
        }
    private:
        Piece const& attackedPiece_;
    };
}