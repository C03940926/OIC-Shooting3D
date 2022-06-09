/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"Player.h"
#include	"Stage.h"
#include	"Stage1.h"

CPlayer		Player;

Stage		gStage;

#define		ENEMY_COUNT		(20)
CEnemy		gEnemyArray[ENEMY_COUNT];

#define		ENEMYSHOT_COUNT	(200)
CEnemyShot	gShotArray[ENEMYSHOT_COUNT];
CMeshContainer	gEnemyShotMesh;

CCamera		Camera;
CDirectionalLight	Light;

bool		gdDebug;

CVector3		gCameraPos;
CVector3		gTarPos;
CVector3		gCameraUp;


/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");
	gCameraPos = Vector3(0, 6.0f, -17.0f);
	gTarPos = Vector3(0, 0, -10);
	gCameraUp = Vector3(0, 1, 0);

	Camera.SetViewPort();
	Camera.LookAt(Vector3(0, 6.0f, -17.0f), Vector3(0, 0, -10), Vector3(0, 1, 0));
	Camera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 1000.0f);
	CGraphicsUtilities::SetCamera(&Camera);

	Light.SetDirection(Vector3(-1, -2, 1.5f));
	Light.SetDiffuse(MOF_COLOR_WHITE);
	Light.SetAmbient(MOF_COLOR_HWHITE);
	Light.SetSpeculer(MOF_COLOR_WHITE);
	CGraphicsUtilities::SetDirectionalLight(&Light);

	Player.Load();
	Player.Initialize();

	gStage.Load();
	gStage.Initialize(&gStg1EnemyStart);
	
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		gEnemyArray[i].Initialize();
	}

	if (!gEnemyShotMesh.Load("eshot.mom"))
	{
		return false;
	}

	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		gShotArray[i].Initialize();
		gShotArray[i].SetMesh(&gEnemyShotMesh);
	}


	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//キーの更新
	g_pInput->RefreshKey();



	Player.Update();

	gStage.Update(gEnemyArray, ENEMY_COUNT);
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		gEnemyArray[i].SetTargetPos(Player.GetPosition());
		gEnemyArray[i].Update(gShotArray,ENEMYSHOT_COUNT);
	}

	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		gShotArray[i].Update();
	}

	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		Player.ColisionEnemyShot(gShotArray[i]);
	}


	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		Player.CollisionEnemy(gEnemyArray[i]);
	}



	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		gdDebug = ((gdDebug) ? false : true);
	}


	if (g_pInput->IsKeyPush(MOFKEY_RETURN)&&Player.IsDead())
	{
		Player.Initialize();
		gStage.Initialize(&gStg1EnemyStart);
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			gEnemyArray[i].Initialize();
		}
		for (int i = 0; i < ENEMYSHOT_COUNT; i++)
		{
			gShotArray[i].Initialize();
		}
	}



	float posX = Player.GetPosition().x * 0.4f;
	
	gCameraPos.x = posX;
	gTarPos.x = posX;

	gCameraUp.RotationZ(Player.GetPosition().x / FIELD_HALF_X * MOF_ToRadian(0.01f));

	Camera.LookAt(gCameraPos, gTarPos, gCameraUp);

	Camera.Update();

	return TRUE;
}

/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//描画処理
	g_pGraphics->RenderStart();
	// 画面のクリア
	g_pGraphics->ClearTarget(0.65f,0.65f,0.67f,0.0f,1.0f,0);

	g_pGraphics->SetDepthEnable(true);

	Player.Render();

	gStage.Render();

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		gEnemyArray[i].Render();
	}

	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		gShotArray[i].RenderDebug();
	}




	g_pGraphics->SetDepthEnable(false);

	if (gdDebug)
	{
		Player.RenderDebugText();
	}

	if (Player.IsDead())
	{
		CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "ゲームオーバー：Enterキーでもう一度最初から");
	}
	

	// 描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void){

	Player.Release();

	gStage.Relese();
	gEnemyShotMesh.Release();

	return TRUE;
}