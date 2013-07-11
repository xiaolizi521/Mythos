#include "Level.hpp"

#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <boost/property_tree/json_parser.hpp>
#include "StartText.hpp"
#include "Resources.hpp"
#include "Tile.hpp"

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

    boost::property_tree::ptree layers_ = mainTree_.get_child("layers");

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

                unsigned int tileID = tile.second.get_value<unsigned int>();
                std::string tileIDAsString = tile.second.get_value<std::string>();

                if (tileID)
                {
                    tank::Vectorf tilePos {static_cast<float>(mapPos.x * tileSize_),
                                           static_cast<float>(mapPos.y * tileSize_)};

                    bool solid;

                    auto tileset = getTileset(tileID);
                    auto properties = tileset.get_child_optional(tileIDAsString);
                    if(properties)
                    {
                        solid = properties->get("solid", false);
                    }

                    map_[mapPos.x][mapPos.y].push_back(
                        makeEntity<Tile>(tilePos, getImage(tileID), solid));

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
    }
}

void Level::loadObjects()
{
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

    // TODO: Maybe move this into tank::Image?
    // TODO: Check for invalid y coord
    tank::Rectu clip { 0, 0, tileSize_, tileSize_ };

    unsigned int clipOffset = index - key;
    unsigned int usefulSize = image.getTextureSize().x -
                              ( image.getTextureSize().x % tileSize_ );
    clip.x = (tileSize_ * clipOffset) % usefulSize;
    clip.y = (tileSize_ * clipOffset) / usefulSize;
    image.setClip(clip);

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

