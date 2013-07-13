#include "TileObject.hpp"

const float TileObject::speed_ = 1.f;

TileObject::TileObject(tank::Vectorf pos, Level* l, GameState& gs)
    : GameboyEntity(pos)
    , level_(l)
    , gameState_(gs)
    , moving_(false)
    , toMove_()
{
    // Set initial tilePos
    tilePos_.x = getPos().x / level_->getTileSize();
    tilePos_.y = getPos().y / level_->getTileSize();
}

bool TileObject::attemptMove(tank::Vectori direction)
{
    if(not isMoving())
    {
        direction_ = direction;

        if(level_->canMoveTo(tilePos_ + direction_))
        {
            toMove_ = getLevel()->getTileSize();
            tilePos_ += direction_;
            moving_ = true;

            return true;
        }
    }

    return false;
}

void TileObject::updateMove()
{
    if (moving_)
    {
        tank::Vectorf pos = getPos();

        if (std::abs(toMove_) <= speed_)
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
    }
}
