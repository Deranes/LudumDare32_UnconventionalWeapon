#include "TextureBank.h"

TextureBank& TextureBank::GetInstance()
{
	static TextureBank instance;
	return instance;
}

void TextureBank::Initialize()
{
	m_Textures[ TEXTURE_HANDLE_PLAYER_1	].loadFromFile( "asset/circle.jpg" );
	m_Textures[ TEXTURE_HANDLE_PLAYER_2	].loadFromFile( "asset/circle.jpg" );
	m_Textures[ TEXTURE_HANDLE_GUARD	].loadFromFile( "asset/circle.jpg" );
	m_Textures[ TEXTURE_HANDLE_WALL		].loadFromFile( "asset/circle.jpg" );

	for ( auto& texture : m_Textures )
	{
		texture.setSmooth( TEXTURE_BANK_SET_SMOOTH );
	}
}

const sf::Texture& TextureBank::GetTexture( TEXTURE_HANDLE textureHandle )
{
	return m_Textures[textureHandle];
}