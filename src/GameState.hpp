#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Tank/System/State.hpp"
#include "Tank/System/EventHandler.hpp"

class GameState : public tank::State
{
public:
    GameState();
private:
    bool quit(tank::EventArgs const&);
};

#endif /* GAMESTATE_HPP */
