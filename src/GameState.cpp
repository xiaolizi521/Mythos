#include "GameState.hpp"

#include "Tank/System/Game.hpp"
#include "Tank/System/Entity.hpp"
#include "Tank/Utility/Vector.hpp"
#include "Level.hpp"

GameState::GameState()
{
    getEventHandler().registerEvent("quit");
    getEventHandler().registerEventListener("quit",
                                            std::bind(&GameState::quit,
                                                      this,
                                                      std::placeholders::_1));
    getEventHandler().registerKey(sf::Keyboard::Escape, "quit", false);

    changeLevel("testmap");
}

bool GameState::quit(tank::EventArgs const& evtArgs)
{
    tank::Game::popState();
    return true;
}

void GameState::changeLevel(std::string name)
{
    currentLevel_.reset(new Level(name, *this));
}

void GameState::update()
{
    currentLevel_->update();
}

void GameState::draw()
{
    currentLevel_->draw();
}

