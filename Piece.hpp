#pragma once

#include <memory>
#include <vector>
#include "Move.hpp"

namespace chess {
    class Piece {
    public:
        Piece(Position const position)
            : position_{position} {}

        Position GetPosition() const {
            return position_;
        }

        bool MoveTo(Position const newPosition) {
            for (auto & move : moves_) {
                if (newPosition == move->GetPosition()) {
                    hasMoved_ = true;
                    move->DoAction();
                    position_ = move->GetPosition();
                    return true;
                }
            }
            return false;
        }

        void ClearMoves() {
            moves_.clear();
        }

        virtual void SetMoves() = 0;
        virtual ~Piece() = default;
    protected:
        template<typename MoveType>
        void AddMove(MoveType && move) {
            moves_.push_back(std::make_unique<MoveType>(std::move(move)))
        }
    private:
        Position position_;
        std::vector<std::unique_ptr<Move>> moves_;
        bool hasMoved_ = false;
    };
};