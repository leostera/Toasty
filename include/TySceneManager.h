#pragma once

#include <TyScene.h>
#include <TySingleton.h>

#include <vector>

class TySceneManager : public ITySingleton<TySceneManager>
{
private:
	TyScene*				m_CurrentScene;
	TyScene*				m_PreviousScene;
	std::vector<TyScene*>	m_Scenes;

public:
	TySceneManager();	
	~TySceneManager();
	

	TyScene*	AddScene();
	bool		DeleteScene(TyScene* pScene);	

	bool		HasScene(TyScene* pScene);
	bool		IsCurrentScene(TyScene* pScene);

	bool		SetCurrentScene(TyScene* pScene);

	bool		Play();
};