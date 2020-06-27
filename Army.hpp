#pragma once

#include <algorithm>
#include "Cloner.hpp"
#include "Piece.hpp"

namespace chess {
    class Army {
    public:
        Army() {}

        Army(Army const& other) :
            pieces_{CloneAll(other.pieces_)} {}

        auto GetPieceAt(Position const position) -> Piece * const {
            for (auto & piece : pieces_)
                if (piece->GetPosition() == position)
                    return piece.get();
            return nullptr;
        }

        auto HasPieceAt(Position const position) -> bool {
            return GetPieceAt(position) != nullptr;
        }

        auto Kill(Piece const& key) {
            std::erase_if(pieces_, [&key](auto const& piece) {
                return piece->GetPosition() == key.GetPosition();
            });
        }
    private:
        std::vector<std::unique_ptr<Piece>> pieces_;
    };
}