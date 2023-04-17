#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "Collidable.h"

// Houses, trees, ...

class SurfaceObjects : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const std::string& tileset, sf::Vector2u tileSize);
	std::vector<Collidable> collidables;


private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray o_vertices;
	sf::Texture o_tileset;
};





