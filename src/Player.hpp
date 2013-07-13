#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Tank/Utility/Vector.hpp"
#include "Tank/Graphics/Animation.hpp"
#include "Tank/System/EventHandler.hpp"
#include "TileObject.hpp"

class Player : public TileObject
{
public:
    Player(tank::Vectorf pos, Level& level, GameState& gameState);

    virtual void update() override;
private:
    tank::Animation* anim_;

    bool handleInput(tank::EventArgs const& e);
};

#endif /* PLAYER_HPP */
