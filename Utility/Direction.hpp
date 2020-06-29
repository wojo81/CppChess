namespace chess::dir {
	enum Direction {
		Up, UpRight, Right, DownRight, Down, DownLeft, Left, UpLeft
	};

	auto GetNextDirection(Direction direction, int const spaces = 1) -> Direction {
		return static_cast<Direction>((direction + spaces) % (UpLeft + 1));
	}
}