#include "GameboyEntity.hpp"

unsigned int GameboyEntity::scale_ = 4;

GameboyEntity::GameboyEntity(tank::Vectorf pos)
    : Entity(pos)
{}
void GameboyEntity::draw(tank::Vectorf camera)
{
    for (auto& g : getGraphicList())
    {
        g->setPos(getPos() * scale_);
        g->setScale(scale_);
    }

    Entity::draw(camera);
}
