#include <TySceneManager.h>

TySceneManager* TySceneManager::m_Instance = 0;

void TySceneMgrInit()
{
	if(TySceneManager::m_Instance == 0)
		TySceneManager::m_Instance = new TySceneManager();
}

void TySceneMgrTerminate()
{
	if(TySceneManager::m_Instance)
	{
		delete TySceneManager::m_Instance;
		TySceneManager::m_Instance = 0;
	}
}

TySceneManager*	TyGetSceneMgr()
{
	return TySceneManager::m_Instance;
}

TySceneManager::TySceneManager() : m_CurrentScene(0), m_PreviousScene(0)
{

}

TySceneManager::~TySceneManager()
{
	std::vector<TyScene*>::iterator it = m_Scenes.begin();
	while(it != m_Scenes.end())
	{
			delete (*it);
			it = m_Scenes.erase(it);
	}
	m_Scenes.clear();
}

TyScene*	TySceneManager::AddScene() 
{
	m_Scenes.push_back(new TyScene());
	return m_Scenes.back();
}

bool		TySceneManager::DeleteScene(TyScene* pScene)
{
	bool deleted = false;
	std::vector<TyScene*>::iterator it;
	for(it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
	{
		if( (*it) == pScene )
		{
			delete (*it);
			m_Scenes.erase(it);
			deleted = true;
			break;
		}
	}
	return deleted;
}

bool		TySceneManager::HasScene(TyScene* pScene)
{
	bool has = false;
	std::vector<TyScene*>::iterator it;
	for(it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
	{
		if( (*it) == pScene )
		{
			has = true;
			break;
		}
	}
	return has;
}

bool		TySceneManager::IsCurrentScene(TyScene * pScene)
{
	bool current = false;
	if( HasScene(pScene) )
	{
		if ( m_CurrentScene == pScene )
			current = true;
	}
	return current;
}

bool		TySceneManager::SetCurrentScene(TyScene *	pScene)
{	
	bool current = false;
	std::vector<TyScene*>::iterator it;
	for(it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
	{
		if( (*it) == pScene )
		{
			current = true;
			m_PreviousScene = m_CurrentScene;
			m_CurrentScene = (*it);
			break;
		}
	}
	return current;
}

bool		TySceneManager::Play()
{
	bool howdiditgo = false;
	if ( m_CurrentScene != 0 )
	{
		if(m_CurrentScene->Create())
		{
			howdiditgo = m_CurrentScene->Play();
			m_CurrentScene->Destroy();
		}
	}
	return howdiditgo;
}