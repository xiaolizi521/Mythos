#include  "StartText.hpp"

#include "Tank/Graphics/Image.hpp"
#include  "Resources.hpp"

StartText::StartText(tank::Vectorf pos)
    : GameboyEntity(pos)
{
    makeGraphic<tank::Image>(res::menuStart);

    const float width = getGraphic()->getTextureSize().x;
    getGraphic()->setOrigin({ width / 2.f, 0.f });
}
