#include "Character.hpp"

#include <iostream>

const std::vector<unsigned int> Character::moveDelays = {
    200, 300, 500, 700, 1100, 1300, 1700, 1900, 2300, 2900, 3100, 3700, 4100,
    4300, 4700, 5300, 5900, 6100, 6700, 7100, 7300, 7900, 8300, 8900, 9700,
    11000
};

Character::Character(tank::Vectorf pos, Level* l, GameState& gs,
                     tank::Image const& image, boost::property_tree::ptree& properties)
    : TileObject(pos, l, gs)
{
    makeGraphic<tank::Image>(image);

    mobile_ = properties.get("properties.mobile", false);
    fixedText_ = properties.get("properties.fixedText", true);
    name_ = properties.get("properties.name", "Lofty Itinerant");

    std::string out = "Created " + name_ + ": ";
    out += mobile_ ? "mobile, " : "immobile, ";
    out += fixedText_ ? "fixed text " : "variable text ";
    std::cout << out << std::endl;
}
