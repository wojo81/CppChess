#pragma once

#include "Position.hpp"

namespace chess {
    struct Move {
        Position const position;

        virtual void DoAction() {}
        virtual ~Move() = default;
    };
}