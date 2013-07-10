#include "MenuState.hpp"

#include "Tank/System/Game.hpp"
#include "Tank/Utility/Vector.hpp"
#include "GameState.hpp"
#include "StartText.hpp"

MenuState::MenuState()
{
    makeEntity<StartText>(tank::Vectorf{80, 20});

    getEventHandler().registerEvent("play");
    getEventHandler().registerEventListener("play",
                                            std::bind(&MenuState::play,
                                                      this,
                                                      std::placeholders::_1));
    getEventHandler().registerKey(sf::Keyboard::Space, "play", false);
}

bool MenuState::play(tank::EventArgs const& evtArgs)
{
    tank::Game::makeState<GameState>();

    return true;
}
