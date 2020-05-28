#pragma once

#include "Position.hpp"

namespace chess {
    class Move {
    public:
        Move(Position position)
            : position_{position} {}

        Position GetPosition() const {
            return position_;
        }

        virtual void DoAction() {}
        virtual ~Move() = default;
    private:
        Position position_;
    };
};