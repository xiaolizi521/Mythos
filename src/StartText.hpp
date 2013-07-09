#ifndef STARTTEXT_HPP
#define STARTTEXT_HPP

//#include "Tank/System/Entity.hpp"
#include "GameboyEntity.hpp"
#include "Tank/Utility/Vector.hpp"

class StartText : public GameboyEntity
{
public:
    StartText(tank::Vectorf pos);
};
#endif /* STARTTEXT_HPP */
