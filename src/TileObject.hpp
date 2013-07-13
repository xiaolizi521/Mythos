#ifndef TILEOBJECT_HPP
#define TILEOBJECT_HPP

#include "GameboyEntity.hpp"
#include "GameState.hpp"
#include "Level.hpp"

class TileObject : public GameboyEntity
{
    Level* level_;
    GameState& gameState_;

    bool moving_;
    tank::Vectori direction_;
    float toMove_;
    tank::Vectoru tilePos_;
public:
    static const float speed_;

    TileObject(tank::Vectorf pos, Level* level, GameState& gameState);

    virtual bool attemptMove(tank::Vectori direction);
    virtual void updateMove();

    bool isMoving() const { return moving_; }
    virtual void setTilePos(tank::Vectoru tilePos) { tilePos_ = tilePos; }
    virtual tank::Vectoru getTilePos() const { return tilePos_; }
    virtual void setLevel(Level* level) { level_ = level; }
    virtual Level* getLevel() { return level_; }
    virtual GameState& getGameState() { return gameState_; }
private:
};
#endif /* TILEOBJECT_HPP */
