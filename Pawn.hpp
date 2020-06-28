#pragma once

#include "Cloner.hpp"
#include "Army.hpp"
#include "Attack.hpp"

namespace chess {
	class Pawn : public Cloner<Piece, Pawn> {
		struct Jump : Cloner<Move, Jump> {
			int const jumpedPawnIndex;

			Jump(Position const position, Army const& allies) :
				Cloner{position}, jumpedPawnIndex{allies.GetPieceIndexAt(position.GetAdjacent(Position::Down, 2))} {}

			auto DoAction(Army & allies, Army &) -> void override {
				allies[jumpedPawnIndex].Cast<Pawn>()->justJumped_ = true;
			}
		};

		struct EnPassant : Cloner<Move, EnPassant> {
			int const attackedPawnIndex;

			EnPassant(Position const position, Army const& enemies) :
				Cloner{position}, attackedPawnIndex{enemies.GetPieceIndexAt(position.GetAdjacent(Position::Down))} {}

			auto DoAction(Army &, Army & enemies) -> void override {
				enemies.Take(attackedPawnIndex);
			}
		};
	public:
		Pawn(Position const position)  :
			Cloner{position} {}
		
		void SetMoves(Army const& allies, Army const& enemies) override {
			justJumped_ = false;

			if (auto const up = GetPosition().GetAdjacent(Position::Up); 
			  !allies.HasPieceAt(up) && !enemies.HasPieceAt(up))
			{
				AddMove(Move{up});

				if (auto const jump = up.GetAdjacent(Position::Up);
				  !HasMoved() && !allies.HasPieceAt(jump) && !enemies.HasPieceAt(jump)) 
					AddMove(Jump{jump, allies});
			}
			
			auto direction = Position::UpLeft;
			for (int i = 0; i != 2; ++i) {
				if (auto const diagonal = GetPosition().GetAdjacent(direction);
				  enemies.HasPieceAt(diagonal))
					AddMove(Attack{diagonal, enemies});
				else if (auto const horizontal = GetPosition().GetAdjacent(Position::Down);
				  enemies.HasPieceAt(horizontal))
					if (auto const pawn = enemies.GetPieceAt(horizontal)->Cast<Pawn>();
					  pawn != nullptr && pawn->justJumped_)
						AddMove(EnPassant{diagonal, enemies});
				direction = Position::GetNextDirection(direction, 2);
			}
		}
	private:
		bool justJumped_ = false;
	};
}