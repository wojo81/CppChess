#pragma once

#include "Cloner.hpp"
#include "Piece.hpp"

namespace chess {
    class Army {
    public:
        Army() {}

        Army(Army const& other) :
            pieces_{CloneAll(other.pieces_)} {}

        auto operator[](int pieceIndex) -> Piece & {
            return *pieces_[pieceIndex];
        }

        auto GetPieceAt(Position const position) -> Piece * const {
            for (auto const& piece : pieces_)
                if (piece->GetPosition() == position)
                    return piece.get();
            return nullptr;
        }

        auto GetPieceIndexAt(Position const position) -> int {
            for (int index = 0; auto const& piece : pieces_) {
                if(piece->GetPosition() == position)
                    return index;
                ++index;
            }
            return -1;
        }

        auto HasPieceAt(Position const position) -> bool {
            return GetPieceAt(position) != nullptr;
        }

        auto Take(int const pieceIndex) {
            pieces_.erase(begin(pieces_) + pieceIndex);
        }
    private:
        std::vector<std::unique_ptr<Piece>> pieces_;
    };
}