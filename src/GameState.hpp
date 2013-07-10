#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <memory>
#include "Tank/System/State.hpp"
#include "Tank/System/EventHandler.hpp"

class Level;

class GameState : public tank::State
{
public:
    GameState();

    void changeLevel(std::string name);

    virtual void update() override;
    virtual void draw() override;
private:
    std::unique_ptr<Level> currentLevel_;
    bool quit(tank::EventArgs const&);
};

#endif /* GAMESTATE_HPP */
