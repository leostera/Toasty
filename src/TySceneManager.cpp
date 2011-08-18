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
	m_Scenes.Delete();
	m_Scenes.Clear();
}

TyScene*	TySceneManager::AddScene() 
{
	m_Scenes.Add(new TyScene());
	return (TyScene*)(*m_Scenes.GetEnd());
}

bool		TySceneManager::DeleteScene(TyScene* pScene)
{
	bool deleted = false;
	if( m_Scenes.EraseFast(m_Scenes.Find(pScene)) )
		deleted = true;
	return deleted;
}

bool		TySceneManager::HasScene(TyScene* pScene)
{
	return m_Scenes.Contains(pScene);
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
	uint32 it = m_Scenes.Find(pScene);
	if( it > 0 && m_Scenes[it] == pScene )
	{
		current = true;
		m_PreviousScene = m_CurrentScene;
		m_CurrentScene = (TyScene*) m_Scenes[it];
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