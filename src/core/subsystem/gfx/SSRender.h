#pragma once
#include "../Subsystem.h"
#include "SFML/Graphics.hpp"
#define g_SSRender SSRender::GetInstance()
class SSRender : public Subsystem{
public:
	static SSRender&		GetInstance();
	virtual void 			Startup();
	virtual void 			Shutdown();
	virtual void 			Update(const float deltaTime);

	void					SetWindow(sf::RenderWindow* window);
private:
	SSRender() : Subsystem("SSRender") {}
	SSRender(const SSRender & rhs);
	~SSRender() {};
	SSRender& operator=(const SSRender & rhs);

	sf::RenderWindow*				m_Window;
};