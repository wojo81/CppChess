#pragma once

#include <memory>
#include "Position.hpp"

namespace chess {
	struct Move {
		Position const position;

		explicit Move(Position const newPosition) :
			position{newPosition} {}

		virtual auto DoAction(class Army &, class Army &) -> void {}
		virtual auto Clone() const -> std::unique_ptr<Move> {
			return std::make_unique<Move>(position);    
		}
		virtual ~Move() = default;
	};
}