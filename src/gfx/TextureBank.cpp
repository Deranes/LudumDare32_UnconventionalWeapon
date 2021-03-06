#include "TextureBank.h"

TextureBank& TextureBank::GetInstance()
{
	static TextureBank instance;
	return instance;
}

void TextureBank::Initialize()
{
	m_Textures[ TEXTURE_HANDLE_PLAYER		].loadFromFile( "asset/circle.jpg" );
	m_Textures[ TEXTURE_HANDLE_CREATURE		].loadFromFile( "asset/creature.png" );
	m_Textures[ TEXTURE_HANDLE_PROJECTILE	].loadFromFile( "asset/projectile.png" );
	m_Textures[ TEXTURE_HANDLE_WALL			].loadFromFile( "asset/wall.png" );
	m_Textures[ TEXTURE_HANDLE_CROSSHAIR	].loadFromFile( "asset/crosshair.png" );

	for ( auto& texture : m_Textures )
	{
		texture.setSmooth( TEXTURE_BANK_SET_SMOOTH );
	}
}

const sf::Texture& TextureBank::GetTexture( TEXTURE_HANDLE textureHandle )
{
	return m_Textures[textureHandle];
}