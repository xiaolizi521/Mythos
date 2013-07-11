#include "GameState.hpp"

#include "Tank/System/Game.hpp"
#include "Tank/System/Entity.hpp"
#include "Tank/Utility/Vector.hpp"
#include "Level.hpp"
#include "Player.hpp"

GameState::GameState()
    : currentLevel_(nullptr)
    , player_(nullptr)
{
    getEventHandler().registerEvent("quit");
    getEventHandler().registerEventListener("quit",
                                            std::bind(&GameState::quit,
                                                      this,
                                                      std::placeholders::_1));
    getEventHandler().registerKey(sf::Keyboard::Escape, "quit", false);

    currentLevel_.reset(new Level("testmap", *this));
    player_ = currentLevel_->makeEntity<Player>(tank::Vectorf{0.f,0.f}, *currentLevel_, *this);
}

bool GameState::quit(tank::EventArgs const& evtArgs)
{
    tank::Game::popState();
    return true;
}

void GameState::changeLevel(std::string name)
{
    std::unique_ptr<Level> oldLevel;
    oldLevel.reset(currentLevel_.release());
    currentLevel_.reset(new Level(name, *this));

    oldLevel->moveEntity(currentLevel_.get(), player_);
}

void GameState::update()
{
    currentLevel_->update();
}

void GameState::draw()
{
    currentLevel_->draw();
}
