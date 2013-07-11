#include "Tile.hpp"

Tile::Tile(tank::Vectorf pos, tank::Image const& image, bool solid)
    : GameboyEntity(pos)
{
    makeGraphic<tank::Image>(image);
    setSolid(solid);
}
