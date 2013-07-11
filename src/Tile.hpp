#ifndef TILE_HPP
#define TILE_HPP

#include "Tank/Utility/Vector.hpp"
#include "Tank/Graphics/Image.hpp"
#include "GameboyEntity.hpp"

class Tile : public GameboyEntity
{
public:
    Tile(tank::Vectorf pos, tank::Image const&);
};

#endif /* TILE_HPP */
