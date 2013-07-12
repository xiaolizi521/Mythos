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

    virtual void update() override;
private:
    tank::Animation* anim_;
    Level& level_;
    GameState& gameState_;

    bool moving_;
    tank::Vectori direction_;
    float toMove_;
    tank::Vectoru tilePos_;

    static const float speed_;
    bool handleInput(tank::EventArgs const& e);
};

#endif /* PLAYER_HPP */
