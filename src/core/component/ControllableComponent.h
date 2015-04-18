#pragma once

#include <SFML/Window/Keyboard.hpp>

typedef std::pair< sf::Keyboard::Key, sf::Keyboard::Key > Keybinding;

struct ControllableComponent
{
	Keybinding	KeyMoveUp		= Keybinding( sf::Keyboard::Up,		sf::Keyboard::W );
	Keybinding	KeyMoveDown		= Keybinding( sf::Keyboard::Down,	sf::Keyboard::S );	
	Keybinding	KeyMoveLeft		= Keybinding( sf::Keyboard::Left,	sf::Keyboard::A );
	Keybinding	KeyMoveRight	= Keybinding( sf::Keyboard::Right,	sf::Keyboard::D );
};