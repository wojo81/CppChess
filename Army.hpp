#pragma once

#include <algorithm>
#include "Piece.hpp"

namespace chess {
    class Army {
    public:
        explicit Army(bool const white) {
            pieces_.reserve(16);


        }

        auto GetPieceAt(Position const position) -> Piece const* {
            for (auto & piece : pieces_)
                if (piece->GetPosition() == position)
                    return piece.get();
            return nullptr;
        }

        auto Contains(Position const position) -> bool {
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