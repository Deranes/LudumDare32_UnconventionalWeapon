#pragma once

#include <SFML/Window/Keyboard.hpp>

typedef std::pair< sf::Keyboard::Key, sf::Keyboard::Key > Keybinding;

struct ControllableComponent
{
	Keybinding	KeyMoveLeft		= Keybinding( sf::Keyboard::KeyCount,	sf::Keyboard::KeyCount );
	Keybinding	KeyMoveRight	= Keybinding( sf::Keyboard::KeyCount,	sf::Keyboard::KeyCount );
	Keybinding	KeyJump			= Keybinding( sf::Keyboard::KeyCount,	sf::Keyboard::KeyCount );
	Keybinding	KeyJumpSecond	= Keybinding( sf::Keyboard::KeyCount,	sf::Keyboard::KeyCount );
};