#pragma once

#include "Cloner.hpp"
#include "../Piece/Piece.hpp"

namespace chess {
	class Army {
	public:
		Army() {}

		Army(Army const& other) :
			pieces_{CloneAll(other.pieces_)} {}

		auto operator[](int const pieceIndex) -> Piece & {
			return *pieces_[pieceIndex];
		}

		auto operator[](int const pieceIndex) const -> Piece const& {
			return *pieces_[pieceIndex];
		}

		auto GetPieceAt(Position const position) const -> Piece const* {
			for (auto const& piece : pieces_)
				if (piece->GetPosition() == position)
					return piece.get();
			return nullptr;
		}

		auto GetPieceIndexAt(Position const position) const -> int {
			for (int index = 0; auto const& piece : pieces_) {
				if (piece->GetPosition() == position)
					return index;
				++index;
			}
			return -1;
		}

		auto HasPieceAt(Position const position) const -> bool {
			return GetPieceAt(position) != nullptr;
		}

		auto Take(int const pieceIndex) {
			pieces_.erase(begin(pieces_) + pieceIndex);
		}
	private:
		std::vector<std::unique_ptr<Piece>> pieces_;
	};
}