#include "Player.hpp"

#include "Resources.hpp"
Player::Player(tank::Vectorf pos, Level& l, GameState& gs)
    : GameboyEntity(pos)
    , moving_(false)
    , level_(l)
    , gameState_(gs)
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
                                     std::bind(&Player::move, this,
                                               std::placeholders::_1));
    evtHandler.registerKey(sf::Keyboard::W, "playerMove");
    evtHandler.registerKey(sf::Keyboard::D, "playerMove");
    evtHandler.registerKey(sf::Keyboard::S, "playerMove");
    evtHandler.registerKey(sf::Keyboard::A, "playerMove");
}

bool Player::move(tank::EventArgs const& args)
{
    if(moving_)
    {
        return true;
    }

    switch (args.key)
    {
    case sf::Keyboard::W:
        anim_->select("up");
        break;
    case sf::Keyboard::D:
        anim_->select("right");
        break;
    case sf::Keyboard::S:
        anim_->select("down");
        break;
    case sf::Keyboard::A:
        anim_->select("left");
        break;
    default:
        break;
    }

    //moving_ = true;
    return true;
}
