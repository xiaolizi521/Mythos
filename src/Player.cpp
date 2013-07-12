#include "Player.hpp"

#include <cmath>
#include "Resources.hpp"

const float Player::speed_ = 1.f;

Player::Player(tank::Vectorf pos, Level& l, GameState& gs)
    : GameboyEntity(pos)
    , level_(l)
    , gameState_(gs)
    , moving_(false)
{
    anim_ = makeGraphic<tank::Animation>(res::player,
                                         tank::Vectoru{ level_.getTileSize(),
                                                        level_.getTileSize()});
    anim_->add("up",    { 0, 1, 2, 3 },     100);
    anim_->add("right", { 4, 5, 6, 7 },     100);
    anim_->add("down",  { 8, 9, 10, 11 },   100);
    anim_->add("left",  { 12, 13, 14, 15 }, 100);
    anim_->setClip({0, 0, 16, 16});

    auto& evtHandler = gameState_.getEventHandler();
    evtHandler.registerEvent("playerMove", tank::EventType::button_held);
    evtHandler.registerEventListener("playerMove",
                                     std::bind(&Player::handleInput, this,
                                               std::placeholders::_1));
    evtHandler.registerKey(sf::Keyboard::W, "playerMove");
    evtHandler.registerKey(sf::Keyboard::D, "playerMove");
    evtHandler.registerKey(sf::Keyboard::S, "playerMove");
    evtHandler.registerKey(sf::Keyboard::A, "playerMove");

    level_.setCamera(getPos() + 8);
}

void Player::update()
{
    if (moving_)
    {
        tank::Vectorf pos = getPos();

        if (std::abs(toMove_) < speed_)
        {
            pos += direction_ * toMove_;
            toMove_ = 0;
            moving_ = false;
        }
        else
        {
            pos += direction_ * speed_;
            toMove_ -= speed_;
        }

        setPos(pos);
        level_.setCamera(pos + 8);
    }
}
bool Player::handleInput(tank::EventArgs const& args)
{
    if(moving_)
    {
        return true;
    }

    direction_ = {};
    toMove_ = level_.getTileSize();

    switch (args.key)
    {
    case sf::Keyboard::W:
        anim_->select("up");
        direction_.y = - 1;
        break;
    case sf::Keyboard::D:
        anim_->select("right");
        direction_.x = 1;
        break;
    case sf::Keyboard::S:
        anim_->select("down");
        direction_.y = 1;
        break;
    case sf::Keyboard::A:
        anim_->select("left");
        direction_.x = -1;
        break;
    default:
        break;
    }

    moving_ = true;
    return true;
}
