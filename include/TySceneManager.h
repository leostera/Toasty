#pragma once

#include <vector>

class CTyScene
{
	public: 
		CTyScene() { ; }
		bool yeah() const { return true; }
}; //dummy, to remove!

class CTySceneManager //: public TySingleton
{
private:
	CTyScene*				m_CurrentScene;
	CTyScene*				m_PreviousScene;
	std::vector<CTyScene*>	m_Scenes;

protected:

public:
	CTySceneManager();
	CTySceneManager(CTySceneManager const& pSceneManager);
	~CTySceneManager();

	CTyScene*	AddScene();
	bool		DeleteScene(CTyScene* pScene);	

	bool		HasScene(CTyScene* pScene);
	bool		IsCurrentScene(CTyScene* pScene);

	bool		SetCurrentScene(CTyScene* pScene);
};