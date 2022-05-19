#pragma once
#include "GameDefine.h"
#define SCROLL_SPEED (1.0f)

class Stage
{
private:
	CSprite3D		m_BG;
	float			m_Scroll;
public:
	Stage();
	~Stage();
	bool	Load();
	void	Initialize();
	void	Update();
	void	Render();
	void	Relese();
};

