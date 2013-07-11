#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <map>
#include <vector>
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

    boost::property_tree::ptree layers_;
    boost::property_tree::ptree tilesets_;
    boost::property_tree::ptree mainTree_;

    std::vector<std::vector<std::vector<tank::Entity*>>> map_;
    std::map<unsigned int, tank::Image> images_;
public:
    Level(std::string name, GameState& parent);

    tank::Image getImage(unsigned int id) const;
    //Temp to stop compiler complaining about parent_
    void changeLevel(std::string name)
    {
        parent_.changeLevel(name);
    }
private:
    void loadImages();
    void loadTerrain();
    void loadInteractables();

    boost::property_tree::ptree getTileset(unsigned int index);
};

#endif /* LEVEL_HPP */
