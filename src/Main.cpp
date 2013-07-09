#include "Tank/System/Game.hpp"
#include "MenuState.hpp"

int main()
{
    if (tank::Game::initialize({640, 576}))
    {
        tank::Game::makeState<MenuState>();
        tank::Game::run();
    }

    return 0;
}
