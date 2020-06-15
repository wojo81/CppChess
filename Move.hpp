#pragma once

#include "Position.hpp"

namespace chess {
    struct Move {
        Position const position;

        Move(Position const newPosition) :
            position{newPosition} {}

        virtual auto DoAction() -> void {}
        virtual ~Move() = default;
    };
}