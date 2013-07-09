#ifndef GAMEBOYENTITY_HPP
#define GAMEBOYENTITY_HPP

#include "Tank/System/Entity.hpp"
#include "Tank/Utility/Vector.hpp"

class GameboyEntity : public tank::Entity
{
public:
    GameboyEntity(tank::Vectorf pos);
    virtual void draw(tank::Vectorf camera) override;

    static unsigned int getScale()
    {
        return scale_;
    }

    static void setScale(unsigned int scale)
    {
        scale_ = scale;
    }
private:
    static unsigned int scale_;
};

#endif /* GAMEBOYENTITY_HPP */
