#include "Player.hpp"

#include <cmath>
#include "Resources.hpp"

Player::Player(tank::Vectorf pos, Level& l, GameState& gs)
    : TileObject(pos, l, gs)
{
    // Set up animation
    anim_ = makeGraphic<tank::Animation>(res::player,
                                         tank::Vectoru{ getLevel()->getTileSize(),
                                                        getLevel()->getTileSize()});

    tank::addWalkingAnimation(*anim_, 100);
    anim_->setClip({0, 0, getLevel()->getTileSize(), getLevel()->getTileSize()});

    // Set up events
    auto& evtHandler = getGameState().getEventHandler();
    evtHandler.registerEvent("playerMove", tank::EventType::button_held);
    evtHandler.registerEventListener("playerMove",
                                     std::bind(&Player::handleInput, this,
                                               std::placeholders::_1));
    evtHandler.registerKey(sf::Keyboard::W, "playerMove");
    evtHandler.registerKey(sf::Keyboard::D, "playerMove");
    evtHandler.registerKey(sf::Keyboard::S, "playerMove");
    evtHandler.registerKey(sf::Keyboard::A, "playerMove");

    // Set initial camera position
    getLevel()->setCamera(getPos() + getLevel()->getTileSize() / 2);
}

void Player::update()
{
    if (isMoving())
    {
        updateMove();
        getLevel()->setCamera(getPos() + getLevel()->getTileSize() / 2);
    }
    else
    {
        anim_->stop();
    }
}
bool Player::handleInput(tank::EventArgs const& args)
{
    if(isMoving())
    {
        return true;
    }

    tank::Vectori direction = {};

    switch (args.key)
    {
    case sf::Keyboard::W:
        anim_->select("walk_up");
        direction.y = -1;
        break;
    case sf::Keyboard::D:
        anim_->select("walk_right");
        direction.x = 1;
        break;
    case sf::Keyboard::S:
        anim_->select("walk_down");
        direction.y = 1;
        break;
    case sf::Keyboard::A:
        anim_->select("walk_left");
        direction.x = -1;
        break;
    default:
        break;
    }

    if (attemptMove(direction))
    {
        anim_->start();
    }

    return true;
}
