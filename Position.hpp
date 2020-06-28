#pragma once

#include <vector>

namespace chess {
	class Position {
	public:
		enum Direction {
			Up, UpRight, Right, DownRight, Down, DownLeft, Left, UpLeft
		};

		static auto GetNextDirection(Direction direction, int const spaces = 1) -> Direction {
			return static_cast<Direction>((direction + spaces) % (UpLeft + 1));
		}

		Position(int x, int y) :
			x_{x}, y_{y} {}

		friend auto operator==(Position const left, Position const right) -> bool {
			return left.x_ == right.x_ && left.y_ == right.y_;
		}

		auto GetX() -> int {
			return x_;
		}

		auto GetY() -> int {
			return y_;
		}

		auto InBounds() const -> bool {
			return  x_ >= 0 && x_ < 8 && y_ >= 0 && y_ < 8;
		}

		auto GetAdjacent(Direction const direction, int const spaces = 1) const -> Position {
			return *this + Displace(direction) * spaces;
		}

		auto GetLine(Direction const direction) const -> std::vector<Position> {
			std::vector<Position> positions;
			auto displacement = Displace(direction);
			for (auto position = *this + displacement; position.InBounds(); position = position + displacement)
				positions.push_back(position);
			return positions;
		}
	private:
		int x_, y_;

		auto operator+(Position const other) const -> Position {
			return {x_ + other.x_, y_ + other.y_};
		}

		auto operator*(int const value) const -> Position {
			return {x_ * value, y_ * value};
		}

		auto Displace(Direction const direction) const -> Position {
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