#pragma once

class CTySceneManager //: public TySingleton
{
private:
	CTyScene*				m_ActiveScene;
	CTyScene*				m_PreviousScene;
	CTyScene*				m_NextScene;
	std::queue<CTyScene*>	m_Scenes;

protected:

public:
	CTySceneManager();
	CTySceneManager(CTySceneManager const& pSceneManager);
	~CTySceneManager();

	AddScene(CTyScene*);
	DeleteScene(CTyScene*);

	SetCurrentScene(CTyScene*);

	Push(CTyScene*);

	Pop(CTyScene*);

	
}