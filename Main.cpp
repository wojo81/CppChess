#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

namespace chess {
	class Chess : public olc::PixelGameEngine {
	public:
		Chess() {
			sAppName = "Chess";
		}

		auto OnUserCreate() -> bool override {
			
			return true;
		}

		auto OnUserUpdate(float elapsedTime) -> bool override {
			return true;
		}
	};
}

auto main() -> int {
	chess::Chess game;
	if (game.Construct(256, 256, 4, 4));
		game.Start();
}