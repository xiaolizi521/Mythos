#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Tank/Utility/Vector.hpp"
#include "Tank/Graphics/Animation.hpp"
#include "GameboyEntity.hpp"
#include "GameState.hpp"
#include "Level.hpp"

class Player : public GameboyEntity
{
public:
    Player(tank::Vectorf pos, Level& level, GameState& gameState);
private:
    tank::Animation* anim_;
    Level& level_;
    GameState& gameState_;

    void changeLevel(std::string name)
    {
        gameState_.changeLevel(name);
    }
};

#endif /* PLAYER_HPP */
