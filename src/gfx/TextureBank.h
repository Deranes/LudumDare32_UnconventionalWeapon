#pragma once

#include <SFML/Graphics.hpp>

#define TEXTURE_BANK_SET_SMOOTH	false

#define g_TextureBank	TextureBank::GetInstance()

enum TEXTURE_HANDLE
{
	TEXTURE_HANDLE_PLAYER_1,
	TEXTURE_HANDLE_PLAYER_2,
	TEXTURE_HANDLE_GUARD,
	TEXTURE_HANDLE_WALL,
	TEXTURE_HANDLE_SIZE
};

class TextureBank
{
public:
	static TextureBank&	GetInstance();

	void				Initialize();

	const sf::Texture&	GetTexture( TEXTURE_HANDLE textureHandle );

private:
	sf::Texture			m_Textures[TEXTURE_HANDLE_SIZE];
};