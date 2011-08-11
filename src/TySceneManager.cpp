#include <TySceneManager.h>

CTySceneManager::CTySceneManager()
{

}

CTySceneManager::~CTySceneManager()
{
	std::vector<CTyScene*>::iterator it = m_Scenes.begin();
	while(it != m_Scenes.end())
	{
			delete (*it);
			it = m_Scenes.erase(it);
	}
	m_Scenes.clear();
}

CTyScene*	CTySceneManager::AddScene() 
{
	m_Scenes.push_back(new CTyScene());
	return m_Scenes.back();
}

bool		CTySceneManager::DeleteScene(CTyScene* pScene)
{
	bool deleted = false;
	std::vector<CTyScene*>::iterator it;
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

bool		CTySceneManager::HasScene(CTyScene* pScene)
{
	bool has = false;
	std::vector<CTyScene*>::iterator it;
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

bool		CTySceneManager::IsCurrentScene(CTyScene * pScene)
{
	bool current = false;
	if( HasScene(pScene) )
	{
		if ( m_CurrentScene == pScene )
			current = true;
	}
	return current;
}

bool		CTySceneManager::SetCurrentScene(CTyScene *	pScene)
{	
	bool current = false;
	std::vector<CTyScene*>::iterator it;
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