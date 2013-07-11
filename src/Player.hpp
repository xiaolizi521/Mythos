#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Tank/Utility/Vector.hpp"
#include "Tank/Graphics/Animation.hpp"
#include "Tank/System/EventHandler.hpp"
#include "GameboyEntity.hpp"
#include "GameState.hpp"
#include "Level.hpp"

class Player : public GameboyEntity
{
public:
    Player(tank::Vectorf pos, Level& level, GameState& gameState);
private:
    tank::Animation* anim_;
    bool moving_;
    Level& level_;
    GameState& gameState_;

    bool move(tank::EventArgs const& e);
};

#endif /* PLAYER_HPP */
