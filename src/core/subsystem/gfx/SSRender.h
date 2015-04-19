#pragma once
#include <glm/vec2.hpp>
#include "../Subsystem.h"
#include "SFML/Graphics.hpp"
#include "../../datadriven/ComponentTypes.h"

#define g_SSRender SSRender::GetInstance()

class SSRender : public Subsystem{
public:
	static SSRender&		GetInstance();
	virtual void 			Startup();
	virtual void 			Shutdown();
	virtual void 			Update(const float deltaTime);

	void					SetWindow(sf::RenderWindow* window);
	void					SetTargetEntity( Entity newTargetEntity );
	void					SetBounds( const glm::vec2& min, const glm::vec2& max );

private:
	SSRender() : Subsystem("SSRender") {}
	SSRender(const SSRender & rhs);
	~SSRender() {};
	SSRender& operator=(const SSRender & rhs);

	sf::RenderWindow*				m_Window;
	Entity							m_TargetEntity;
	glm::vec2						m_ScreenSize;
	glm::vec2						m_BoundsMin;
	glm::vec2						m_BoundsMax;
	glm::vec2						m_Position;
	glm::vec2						m_PrevTargetPosition;
};