#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <vector>
#include <boost/property_tree/ptree.hpp>
#include "Tank/Utility/Vector.hpp"
#include "Tank/Utility/Timer.hpp"
#include "Tank/Graphics/Image.hpp"
#include "Level.hpp"
#include "TileObject.hpp"

class Character : public TileObject
{
public:
    Character(tank::Vectorf pos, Level* l, GameState& gs, tank::Image const&,
              boost::property_tree::ptree& properties);
protected:
    static const std::vector<unsigned int> moveDelays;
private:
    tank::Timer moveTimer_;
    bool mobile_;
    bool fixedText_;
    std::string name_;
};

#endif /* CHARACTER_HPP */
