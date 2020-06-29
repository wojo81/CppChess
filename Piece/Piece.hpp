#pragma once

#include <memory>
#include "../Move/Move.hpp"

namespace chess {
	class Piece {
	public:
		Piece(Position const position) : 
			position_{position} {}

		Piece(Piece const& other) :
			position_{other.position_}, moves_{CloneAll(other.moves_)}, hasMoved_{other.hasMoved_} {}

		auto GetPosition() const -> Position {
			return position_;
		}

		auto HasMoved() const -> bool {
			return hasMoved_;
		}

		auto MoveTo(Position const newPosition, class Army & allies, class Army & enemies) -> bool {
			for (auto & move : moves_) {
				if (newPosition == move->position) {
					hasMoved_ = true;
					move->DoAction(allies, enemies);
					position_ = move->position;
					return true;
				}
			}
			return false;
		}

		auto ClearMoves() {
			moves_.clear();
		}

		template <typename PieceType>
		auto Cast() -> PieceType * {
			return dynamic_cast<PieceType *>(this);
		}

		template <typename PieceType>
		auto Cast() const -> PieceType const* {
			return dynamic_cast<PieceType const*>(this);
		}

		virtual auto SetMoves(class Army const&, class Army const&) -> void = 0;
		virtual auto Clone() const -> std::unique_ptr<Piece> = 0;
		virtual ~Piece() = default;
	protected:
		template <typename MoveType>
		auto AddMove(MoveType move) {
			moves_.push_back(std::make_unique<MoveType>(move));
		}
	private:
		Position position_;
		std::vector<std::unique_ptr<Move>> moves_;
		bool hasMoved_ = false;
	};
}