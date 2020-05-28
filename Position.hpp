#pragma once

namespace chess {
    struct Position {
        int x, y;
    };

    bool operator==(Position const left, Position const right) {
        return left.x == right.x && left.y == right.y;
    }
};