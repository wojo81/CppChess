#pragma once

#include "../Move/Attack.hpp"
#include "../Utility/Army.hpp"
#include "../Utility/Cloner.hpp"

namespace chess {
	class Rook : Cloner<Piece, Rook> {
	public:
		Rook(Position const position) :
			Cloner{position} {}

		auto SetMoves(Army const& allies, Army const& enemies) -> void override {
			auto direction = dir::Up;
			for (int i = 0; i != 4; ++i) {
				for (auto const thisPosition = GetPosition(); 
				  auto const position : thisPosition.GetLine(direction)) {
					if (enemies.HasPieceAt(position))
						AddMove(Attack{position, enemies});
					else if (!allies.HasPieceAt(position))
						AddMove(Move{position});
				}
				direction = dir::GetNextDirection(direction, 2);
			}
		}
	};
}