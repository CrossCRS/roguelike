#include "Game.h"
#include <spdlog/spdlog.h>

int main() {
    spdlog::set_pattern("[%T.%e] [%^%L%$] %v");
#ifdef BREAD_DEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    Game game;
    game.run();
}