#pragma once

#include <vector>
#include "Direction.hpp"

namespace chess {
	struct Position {
		int x, y;

		friend auto operator==(Position const left, Position const right) -> bool {
			return left.x == right.x && left.y == right.y;
		}

		auto InBounds() const -> bool {
			return  x >= 0 && x < 8 && y >= 0 && y < 8;
		}

		auto GetAdjacent(dir::Direction const direction, int const spaces = 1) const -> Position {
			return *this + Displace(direction) * spaces;
		}

		auto GetLine(dir::Direction const direction) const -> std::vector<Position> {
			std::vector<Position> positions;
			auto displacement = Displace(direction);
			for (auto position = *this + displacement; position.InBounds(); position = position + displacement)
				positions.push_back(position);
			return positions;
		}
	private:
		auto operator+(Position const other) const -> Position {
			return {x + other.x, y + other.y};
		}

		auto operator*(int const value) const -> Position {
			return {x * value, y * value};
		}

		auto Displace(dir::Direction const direction) const -> Position {
			using namespace dir;
			switch (direction) {
			case Up:
				return {0, -1};
			case UpRight:
				return {1, -1};
			case Right:
				return {1, 0};
			case DownRight:
				return {1, 1};
			case Down:
				return {0, 1};
			case DownLeft:
				return {-1, 1};
			case Left:
				return {-1, 0};
			case UpLeft:
				return {-1, -1};
			}
		}
	};
}