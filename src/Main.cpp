#include "Tank/System/Game.hpp"
#include "GameboyEntity.hpp"
#include "MenuState.hpp"

int main()
{
    const unsigned int scale = GameboyEntity::getScale();
    if (tank::Game::initialize({160 * scale, 144 * scale}))
    {
        tank::Game::makeState<MenuState>();
        tank::Game::run();
    }

    return 0;
}
