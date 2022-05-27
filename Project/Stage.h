#pragma once
#include "GameDefine.h"
#include "Enemy.h"
#define SCROLL_SPEED (1.0f)

typedef struct tag_ENEMYSTART {
	int		Count;
	float*	PosX;
	float* Scroll;
}ENEMYSTART;

class Stage
{
private:
	CSprite3D		m_BG;
	float			m_Scroll;
	ENEMYSTART* m_pEnemytStart;
	CMeshContainer	m_EnemyMesh;
	int				m_EnemyNo;
public:
	Stage();
	~Stage();
	bool	Load();
	void	Initialize(ENEMYSTART* pst);
	void	Update(CEnemy* ene,int ecnt);
	void	Render();
	void	Relese();
};

