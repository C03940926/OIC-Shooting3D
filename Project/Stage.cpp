#include "Stage.h"


Stage::Stage() :
	m_BG(),
	m_Scroll(0.0f) {

}


Stage::~Stage() {

}


bool Stage::Load() {
	if (!m_BG.CreateSprite("road.png"))
	{
		return false;
	}

	return true;
}



void Stage::Initialize() {
	m_BG.m_Angle.x = MOF_MATH_PI;
	m_BG.m_Angle.y = MOF_MATH_PI;
	m_BG.m_Scale = Vector3(200, 200, 200);
	m_BG.m_Position.y = -15;
	m_BG.SetImageRect(0, 0, m_BG.GetTexture()->GetWidth() * 4, m_BG.GetTexture()->GetHeight() * 4);
	m_Scroll = 0;
}

 
void Stage::Update() {
	m_Scroll += SCROLL_SPEED;
}


void Stage::Render() {
	for (int i = 0; i < 2; i++)
	{
		m_BG.m_Position.z = 50.0f + fmodf(-m_Scroll, m_BG.m_Scale.z) + i * m_BG.m_Scale.z;
		m_BG.Update();
		m_BG.Render();
	}
}




void Stage::Relese() {
	m_BG.Release();
}