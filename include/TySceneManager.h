/*!**********************************************************************************

	\class			TySceneManager
	\brief			Scene management singleton.
	\date			15/08/2011
	\version		0.1					
	\author			Leandro Ostera

************************************************************************************/

#pragma once

#ifndef TOASTY_SCENEMGR_H
#define TOASTY_SCENEMGR_H

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
	CIwManagedList			m_Scenes;

	
public:
	TyScene*	AddScene();
	bool		DeleteScene(TyScene* pScene);	

	bool		HasScene(TyScene* pScene);
	bool		IsCurrentScene(TyScene* pScene);

	bool		SetCurrentScene(TyScene* pScene);

	bool		Play();
};

#endif