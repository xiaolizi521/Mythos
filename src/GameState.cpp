#include "GameState.hpp"

#include "Tank/System/Game.hpp"
#include "Tank/System/Entity.hpp"
#include "Tank/Utility/Vector.hpp"
#include "StartText.hpp"
#include "Resources.hpp"

GameState::GameState()
{
    makeEntity<StartText>(tank::Vectorf{80.f, 100.f});
    tank::Entity* e = makeEntity<tank::Entity>(tank::Vectorf{});
    e->makeGraphic<tank::Image>(res::debugGrid);

    getEventHandler().registerEvent("quit");
    getEventHandler().registerEventListener("quit",
                                            std::bind(&GameState::quit,
                                                      this,
                                                      std::placeholders::_1));
    getEventHandler().registerKey(sf::Keyboard::Escape, "quit", false);
}

bool GameState::quit(tank::EventArgs const& evtArgs)
{
    tank::Game::popState();
    return true;
}
