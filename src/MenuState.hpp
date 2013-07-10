#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "Tank/System/State.hpp"
#include "Tank/System/EventHandler.hpp"

class MenuState : public tank::State
{
public:
    MenuState();

private:
    bool play(tank::EventArgs const&);
};
#endif /* MENUSTATE_HPP */
