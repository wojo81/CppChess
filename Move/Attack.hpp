#pragma once

#include "../Utility/Army.hpp"
#include "../Utility/Cloner.hpp"

namespace chess {
	struct Attack : public Cloner<Move, Attack> {
		int const attackedPieceIndex;

		Attack(Position const position, Army const& enemies) :
			Cloner{position}, attackedPieceIndex{enemies.GetPieceIndexAt(position)} {}

		auto DoAction(Army &, Army & enemies) -> void override {
			enemies.Take(attackedPieceIndex);
		}
	};
}