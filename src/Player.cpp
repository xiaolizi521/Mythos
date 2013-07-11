#include "Player.hpp"

#include "Resources.hpp"
Player::Player(tank::Vectorf pos, Level& l, GameState& gs)
    : GameboyEntity(pos)
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
}
