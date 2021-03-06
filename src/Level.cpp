#include "Level.hpp"

#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <boost/property_tree/json_parser.hpp>
#include "Tank/System/Game.hpp"
#include "StartText.hpp"
#include "Resources.hpp"
#include "Tile.hpp"
#include "Character.hpp"

Level::Level(std::string name, GameState& parent)
    : parent_(parent)
{
    std::stringstream filePath;
    filePath << "res/maps/" << name << ".json";

    // Load mapfile
    boost::property_tree::read_json(filePath.str(), mainTree_);

    // Set level properties
    dimensions_.x = mainTree_.get<unsigned int>("width");
    dimensions_.y = mainTree_.get<unsigned int>("height");
    tileSize_ = mainTree_.get<unsigned int>("tileheight");

    // Organize ptrees
    tilesets_ = mainTree_.get_child("tilesets");
    layers_ = mainTree_.get_child("layers");

    // Allocate map space
    map_.resize(dimensions_.x);
    for(auto& column : map_)
    {
        column.resize(dimensions_.y);
    }

    loadImages();
    loadTiles();
    loadObjects();
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

void Level::loadTiles()
{
    int z = -100;
    for (auto& layer : layers_)
    {
        tank::Vectoru mapPos {};

        if (layer.second.get<std::string>("type") == "tilelayer")
        {
            for (auto& tile : layer.second.get_child("data"))
            {
                if (mapPos.x >= dimensions_.x or
                    mapPos.y >= dimensions_.y)
                {
                    throw std::out_of_range("Exceeded map dimensions");
                }

                const unsigned int tileID = tile.second.get_value<unsigned int>();

                if (tileID)
                {
                    tank::Vectorf entPos {
                        static_cast<float>(mapPos.x * tileSize_),
                        static_cast<float>(mapPos.y * tileSize_)
                    };

                    bool solid = false;

                    auto tileset = getTileset(tileID);

                    std::stringstream propertyID;
                    propertyID << "tileproperties." << tileID - 1;
                    auto properties = tileset.get_child_optional(propertyID.str());
                    if(properties)
                    {
                        solid = properties->get("solid", false);
                    }

                    map_[mapPos.x][mapPos.y].push_back(
                        makeEntity<Tile>(entPos, getImage(tileID), solid));

                    map_[mapPos.x][mapPos.y].back()->setLayer(z);
                }

                //Next map position
                if(mapPos.x + 1 >= dimensions_.x)
                {
                    mapPos.x = 0;
                    ++mapPos.y;
                }
                else
                {
                    ++mapPos.x;
                }
            }
        }

        ++z;
    }
}

void Level::loadObjects()
{
    for (auto& layer : layers_)
    {
        if (layer.second.get<std::string>("type") == "objectgroup")
        {
            for (auto& object : layer.second.get_child("objects"))
            {
                const tank::Vectorf entPos {
                    object.second.get<float>("x"),
                    object.second.get<float>("y")
                };

                const tank::Vectoru mapPos = {
                    static_cast<unsigned int>(entPos.x / tileSize_),
                    static_cast<unsigned int>(entPos.y / tileSize_)
                };

                std::string type = object.second.get<std::string>("type");

                if(type == "civilian" or type == "companion" or type == "")
                {
                    const unsigned int tileID = object.second.get<unsigned int>("gid");

                    map_[mapPos.x][mapPos.y].push_back(
                        makeEntity<Character>(entPos, this, parent_,
                                              getImage(tileID), object.second));
                }
            }
        }
    }
}

tank::Image Level::getImage(unsigned int index) const
{
    tank::Image image;

    unsigned int key;
    for(auto& keyVal : images_)
    {
        unsigned int currentKey = keyVal.first;
        if(currentKey <= index)
        {
            key = currentKey;
        }
        else
        {
            break;
        }
    }

    image = images_.at(key);

    image.setClip({ tileSize_, tileSize_ }, index - key);

    return image;
}

boost::property_tree::ptree Level::getTileset(unsigned int index)
{
    using boost::property_tree::ptree;

    ptree::iterator lastIt = tilesets_.begin();
    for (ptree::iterator it = tilesets_.begin(); it != tilesets_.end(); ++it)
    {
        if(it->second.get<unsigned int>("firstgid") > index)
        {
            return lastIt->second;
        }
        lastIt = it;
    }

    throw std::runtime_error("Could not find tileset from tileid");
}

void Level::setCamera(tank::Vectorf camera)
{
    tank::Vectoru midPoint = tank::Game::window()->getSize() / 2;

    camera *= GameboyEntity::getScale();
    camera.x -= midPoint.x;
    camera.y -= midPoint.y;

    State::setCamera(camera);
}

bool Level::canMoveTo(tank::Vectoru coord) const
{
    if (coord.x > dimensions_.x or coord.y > dimensions_.y)
    {
        return false;
    }

    std::vector<tank::Entity*> const& tile = map_[coord.x][coord.y];
    if (tile.empty())
    {
        return false;
    }

    return find_if(tile.begin(), tile.end(),
                   [](tank::Entity* ent)
    {
        return ent->isSolid();
    }) == tile.end();
}
