#include "Level.hpp"

#include <sstream>
#include <iostream>
#include <algorithm>
#include <boost/property_tree/json_parser.hpp>
#include "StartText.hpp"
#include "Resources.hpp"

Level::Level(std::string name, GameState& parent)
    : parent_(parent)
{
    std::stringstream filePath;
    filePath << "res/maps/" << name << ".json";

    boost::property_tree::ptree levelTree;
    boost::property_tree::read_json(filePath.str(), levelTree);

    dimensions_.x = levelTree.get<unsigned int>("width");
    dimensions_.y = levelTree.get<unsigned int>("height");
    tileSize_ = levelTree.get<unsigned int>("tileheight");

    tilesets_ = levelTree.get_child("tilesets");
    layers_ = levelTree.get_child("layers");

    loadImages();
    loadTerrain(levelTree);
    loadInteractables(levelTree);

    //Testing code
    makeEntity<StartText>(tank::Vectorf{80.f, 100.f});
    tank::Entity* e = makeEntity<tank::Entity>(tank::Vectorf{});
    e->makeGraphic<tank::Image>(res::debugGrid);

}

void Level::loadImages()
{
    std::string rootPath = "res/maps/";
    for (auto& tileset : tilesets_)
    {
        unsigned int firstID = tileset.second.get<unsigned int>("firstgid");
        std::string filePath = tileset.second.get<std::string>("image");

        filePath = rootPath + filePath;

        images_.insert({firstID, tank::Image(filePath)});
    }
}

void Level::loadTerrain(boost::property_tree::ptree& levelTree)
{
    boost::property_tree::ptree terrainLayer;

    terrainLayer = std::find_if(layers_.begin(), layers_.end(),
       [](std::pair<std::string, boost::property_tree::ptree> const& layer)
    {
        return layer.second.get<std::string>("name") == "Terrain";
    })->second;

    int nonNull = 0;
    for (auto& tile : terrainLayer.get_child("data"))
    {
        unsigned int id = tile.second.get_value<unsigned int>();
        if (id) ++nonNull;
    }

    std::cout << nonNull << std::endl;
    /*
    for (auto&  layer: levelTree.get_child("layers"))
    {
        if(tileset.second.get<std::string>("name") == "Terrain")
        {
            terrainTree = tileset.second;
            break;
        }
    }
    */
}

void Level::loadInteractables(boost::property_tree::ptree& levelTree)
{
}
