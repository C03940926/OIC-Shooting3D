#pragma once

#include "GameDefine.h"

#include "PlayerShot.h"

#include "Enemy.h"

// ˆÚ“®‘¬“x
#define PLAYER_SPEED		(0.1f)

#define SHOT_COUNT			(40)
#define SHOT_WAIT			(5)

class CPlayer{
private:
	CMeshContainer	m_Mesh;
	CVector3		m_Pos;
	float			m_RotZ;
	float			m_Speed;
	float			RotSpeed ;
	bool			m_bDead;

	CMeshContainer	m_ShotMesh;
	CPlayerShot		m_ShotArray[SHOT_COUNT];
	int				m_ShotWait;
	int				m_Select;

public:
	CPlayer();
	~CPlayer();
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void RenderDebugText();
	const CVector3 GetPosition(){ return m_Pos; }
	void Release();
	void CollisionEnemy(CEnemy& ene);
	bool IsDead() { return m_bDead; }
	CSphere GetSphere() { return CSphere(m_Pos, 0.4f); }
	void ColisionEnemyShot(CEnemyShot& shot);

	
	void UpdateSingle();
	void UpdateDouble();
	void UpdateTripple();
};