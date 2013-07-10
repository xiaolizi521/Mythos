#include "GameboyEntity.hpp"

unsigned int GameboyEntity::scale_ = 4;

GameboyEntity::GameboyEntity(tank::Vectorf pos)
    : Entity(pos)
{}
void GameboyEntity::draw(tank::Vectorf camera)
{
    for (auto& g : getGraphicList())
    {
        g->setScale(scale_);

        g->draw(getPos() * scale_, getRotation(), camera);
    }
}
