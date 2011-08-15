#pragma once

#include <TyScene.h>

#include <vector>

void TySceneMgrInit();
void TySceneMgrTerminate();

class TySceneManager;
TySceneManager*	TyGetSceneMgr();

class TySceneManager
{
private:
	static	TySceneManager*	m_Instance;
	friend void TySceneMgrInit();
	friend void TySceneMgrTerminate();
	friend TySceneManager* TyGetSceneMgr();
	TySceneManager();	
	~TySceneManager();

	TyScene*				m_CurrentScene;
	TyScene*				m_PreviousScene;
	std::vector<TyScene*>	m_Scenes;

public:
	TyScene*	AddScene();
	bool		DeleteScene(TyScene* pScene);	

	bool		HasScene(TyScene* pScene);
	bool		IsCurrentScene(TyScene* pScene);

	bool		SetCurrentScene(TyScene* pScene);

	bool		Play();
};