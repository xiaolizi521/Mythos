#include "MenuState.hpp"

#include "Tank/Utility/Vector.hpp"
#include "StartText.hpp"

MenuState::MenuState()
{
    makeEntity<StartText>(tank::Vectorf{80, 20});
}
