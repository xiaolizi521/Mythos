#include "Tile.hpp"

Tile::Tile(tank::Vectorf pos, tank::Image const& image)
    : GameboyEntity(pos)
{
    makeGraphic<tank::Image>(image);
}
