#pragma once

namespace chess {
    struct Position {
        int x, y;
    };

    auto operator==(Position const left, Position const right) -> bool {
        return left.x == right.x && left.y == right.y;
    }
};