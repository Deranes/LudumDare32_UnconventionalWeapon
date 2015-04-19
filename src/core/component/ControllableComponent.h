#pragma once

#include <SFML/Window/Keyboard.hpp>

typedef std::pair< sf::Keyboard::Key, sf::Keyboard::Key > Keybinding;

struct ControllableComponent
{
	Keybinding	KeyMoveLeft		= Keybinding( sf::Keyboard::Left,	sf::Keyboard::A );
	Keybinding	KeyMoveRight	= Keybinding( sf::Keyboard::Right,	sf::Keyboard::D );
	Keybinding	KeyJump			= Keybinding( sf::Keyboard::Up,		sf::Keyboard::W );
	Keybinding	KeyJumpSecond	= Keybinding( sf::Keyboard::Space,	sf::Keyboard::X );
};