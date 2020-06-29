#pragma once

#include "../Utility/Cloner.hpp"
#include "../Utility/Army.hpp"
#include "../Move/Attack.hpp"

namespace chess {
	class Pawn : public Cloner<Piece, Pawn> {
		struct Jump : Cloner<Move, Jump> {
			int const jumpedPawnIndex;

			Jump(Position const position, Army const& allies) :
				Cloner{position}, jumpedPawnIndex{allies.GetPieceIndexAt(position.GetAdjacent(dir::Down, 2))} {}

			auto DoAction(Army & allies, Army &) -> void override {
				allies[jumpedPawnIndex].Cast<Pawn>()->justJumped_ = true;
			}
		};

		struct EnPassant : Cloner<Move, EnPassant> {
			int const attackedPawnIndex;

			EnPassant(Position const position, Army const& enemies) :
				Cloner{position}, attackedPawnIndex{enemies.GetPieceIndexAt(position.GetAdjacent(dir::Down))} {}

			auto DoAction(Army &, Army & enemies) -> void override {
				enemies.Take(attackedPawnIndex);
			}
		};
	public:
		Pawn(Position const position)  :
			Cloner{position} {}
		
		auto SetMoves(Army const& allies, Army const& enemies) -> void override {
			justJumped_ = false;

			if (auto const up = GetPosition().GetAdjacent(dir::Up); 
			  !allies.HasPieceAt(up) && !enemies.HasPieceAt(up))
			{
				AddMove(Move{up});

				if (auto const jump = up.GetAdjacent(dir::Up);
				  !HasMoved() && !allies.HasPieceAt(jump) && !enemies.HasPieceAt(jump)) 
					AddMove(Jump{jump, allies});
			}
			
			auto direction = dir::UpLeft;
			for (int i = 0; i != 2; ++i) {
				if (auto const diagonal = GetPosition().GetAdjacent(direction);
				  enemies.HasPieceAt(diagonal))
					AddMove(Attack{diagonal, enemies});
				else if (auto const horizontal = GetPosition().GetAdjacent(dir::Down);
				  enemies.HasPieceAt(horizontal))
					if (auto const pawn = enemies.GetPieceAt(horizontal)->Cast<Pawn>();
					  pawn != nullptr && pawn->justJumped_)
						AddMove(EnPassant{diagonal, enemies});
				direction = dir::GetNextDirection(direction, 2);
			}
		}
	private:
		bool justJumped_ = false;
	};
}