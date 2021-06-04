#include "Play_state.h"
#include <iostream>


Play_state::Play_state(std::string filePath) : Game_state()
{
    tmx::Map map;
    if (map.load(filePath))
    {
        std::cout<<"file loaded successfully\n";
        const auto& layers = map.getLayers();
        //visual_layer = layers[0];
        for (const auto& layer : layers)
        {
            //*visual_layer = layer->getLayerAs<tmx::TileLayer>();

            //Le layer est de type object, il s'agit donc ddu path layer
            if (layer->getType() == tmx::Layer::Type::Object)
            {   /*
                const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
                const auto& objects = objectLayer.getObjects();
                for (const auto& object : objects)
                {
                    //do stuff with object properties
                }*/
            }

            //Le layer est de type tile, il s'agit donc d'un visual layer
            else if (layer->getType() == tmx::Layer::Type::Tile)
            {
                const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();



                //*visual_layer = layer->getLayerAs<tmx::TileLayer>();





                //read out tile layer properties etc...
            }
        }

        const auto& tilesets = map.getTilesets();
        for (const auto& tileset : tilesets)
        {
            //read out tile set properties, load textures etc...
        }
    }
}


void Play_state::init()
{

}

void Play_state::update()
{

}

void Play_state::render()
{

}

