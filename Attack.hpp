#pragma once

#include "Piece.hpp"

namespace chess {
    class Attack : public Move {
    public:
        explicit Attack(Piece const& attackedPiece) :
            Move{attackedPiece.GetPosition()}, attackedPiece_{attackedPiece} {}

        auto DoAction() -> void override {
            
        }
    private:
        Piece const& attackedPiece_;
    };
}