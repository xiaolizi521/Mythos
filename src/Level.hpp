#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include "Tank/Utility/Vector.hpp"
#include "Tank/Graphics/Image.hpp"
#include "Tank/System/State.hpp"
#include "GameState.hpp"

class Level : public tank::State
{
    GameState& parent_;
    tank::Vectoru dimensions_;
    unsigned int tileSize_;

    boost::property_tree::ptree tilesets_;
    boost::property_tree::ptree layers_;
public:
    std::map<unsigned int, tank::Image> images_;
    Level(std::string name, GameState& parent);

    void changeLevel(std::string name)
    {
        parent_.changeLevel(name);
    }
private:
    void loadImages();
    void loadTerrain(boost::property_tree::ptree&);
    void loadInteractables(boost::property_tree::ptree&);
};

#endif /* LEVEL_HPP */
