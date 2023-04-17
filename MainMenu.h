#pragma once

#include <SFML/Graphics.hpp>

class MainMenu : public sf::Drawable, public sf::Transformable
{
public:
	// Menu Options
	enum class Option
	{
		Jugar,
		Instrucciones,
		Creditos,
		Salir,
		Default
	};

	MainMenu(sf::Font& font, sf::Texture& backgroundTexture);

	void handleEvent(sf::Event event);
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	Option getSelectedOption() const;


private:
	sf::Font& m_font;
	sf::Texture& m_menuBackground;
	std::vector<sf::Text> m_menuItems;
	Option m_selectedOption = Option::Default; // Default option
};