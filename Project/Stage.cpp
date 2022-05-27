#include "Stage.h"


Stage::Stage() :
	m_BG(),
	m_Scroll(0.0f),
	m_pEnemytStart(NULL),
	m_EnemyMesh(),
	m_EnemyNo(0){

}


Stage::~Stage() {

}


bool Stage::Load() {
	if (!m_BG.CreateSprite("road.png"))
	{
		return false;
	}
	if (!m_EnemyMesh.Load("enemy.mom"))
	{
		return false;
	}

	return true;
}



void Stage::Initialize(ENEMYSTART* pst) {
	m_BG.m_Angle.x = MOF_MATH_HALFPI;
	m_BG.m_Angle.y = MOF_MATH_HALFPI;
	m_BG.m_Scale = Vector3(200, 200, 200);
	m_BG.m_Position.y = -15;
	m_BG.SetImageRect(0, 0, m_BG.GetTexture()->GetWidth() * 4, m_BG.GetTexture()->GetHeight() * 4);
	m_Scroll = 0;
	m_EnemyNo = 0;
	m_pEnemytStart = pst;
}

 
void Stage::Update(CEnemy* ene, int ecnt) {
	m_Scroll += SCROLL_SPEED;

	if (m_EnemyNo<m_pEnemytStart->Count&&m_Scroll>=m_pEnemytStart->Scroll[m_EnemyNo])
	{
		for (int i = 0; i < ecnt; i++) {
			if (ene[i].GetShow())
			{
				continue;
			}
			ene[i].SetMesh(&m_EnemyMesh);
			ene[i].Start(Vector3(m_pEnemytStart->PosX[m_EnemyNo], 0, 0));
			break;
		}
		m_EnemyNo++;
	}

	if (m_Scroll>1000 )
	{
		m_Scroll = 0.0f;
		m_EnemyNo = 0;
	}
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
	m_EnemyMesh.Release();
}