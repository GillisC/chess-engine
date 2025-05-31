#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <stdexcept>
#include <unordered_map>
#include <iostream>

class TextureManager
{
    std::unordered_map<std::string, sf::Texture> _textureMap;


public:
    void load(const std::string& name, const std::string& path)
    {
        sf::Texture texture;
        if (!texture.loadFromFile(path))
        {
            throw std::invalid_argument("Failed to load texture: " + path);
        }
        _textureMap[name] = std::move(texture);
    }

    const sf::Texture& get(const std::string& name) const
    {
        auto it = _textureMap.find(name);
        if (it == _textureMap.end())
        {
            throw std::runtime_error("Texture not found: " + name);
        }
        return it->second;
    }
};
