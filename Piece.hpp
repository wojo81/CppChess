#pragma once

#include <memory>
#include "Move.hpp"

namespace chess {
    class Piece {
    public:
        Piece(Position const position) : 
            position_{position} {}

        auto GetPosition() const -> Position {
            return position_;
        }

        auto MoveTo(Position const newPosition, class Army & allies, class Army & enemies) -> bool {
            for (auto & move : moves_) {
                if (newPosition == move->position) {
                    hasMoved_ = true;
                    move->DoAction(allies, enemies);
                    position_ = move->position;
                    return true;
                }
            }
            return false;
        }

        auto ClearMoves() {
            moves_.clear();
        }

        virtual auto SetMoves() -> void = 0;
        virtual ~Piece() = default;
    protected:
        template <typename MoveType>
        auto AddMove(MoveType move) {
            moves_.push_back(std::make_unique<MoveType>(move));
        }
    private:
        Position position_;
        std::vector<std::unique_ptr<Move>> moves_;
        bool hasMoved_ = false;
    };
}