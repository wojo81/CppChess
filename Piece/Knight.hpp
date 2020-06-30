#pragma once

#include "../Move/Attack.hpp"
#include "../Utility/Army.hpp"
#include "../Utility/Cloner.hpp"

namespace chess {
	class Knight : Cloner<Piece, Knight> {
	public:
		Knight(Position const position) :
			Cloner{position} {}

		auto SetMoves(Army const& allies, Army const& enemies) -> void override {
			auto direction = dir::Up;
			for (int i = 0; i != 4; ++i) {
				auto perpendicularDirection = dir::GetNextDirection(direction, 2);
				for (int j = 0; j != 2; ++j) {
					if (auto position = GetPosition().GetAdjacent(direction, 2).GetAdjacent(perpendicularDirection);
					  enemies.HasPieceAt(position))
					  	AddMove(Attack{position, enemies});
					else if (!allies.HasPieceAt(position) && position.InBounds())
						AddMove(Move{position});
					perpendicularDirection = dir::GetNextDirection(perpendicularDirection, 4);
				}
				direction = dir::GetNextDirection(direction, 2);
			}
		}
	};
}