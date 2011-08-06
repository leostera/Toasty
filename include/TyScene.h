#pragma once

class CTyScene{

	private:
		static int64	m_ID;

	protected:
		CIwResGroup*			m_ResourceGroup;

		std::string				m_Name;
		std::string				m_Caption;

		std::vector<CTyActor*>	m_Actors;
		bool					m_ZOrdered;
		CIw2DImage*				m_Background;
		//back-track music, 
		//possible methods: BeginScene, renders background, calls actors StepStart, if not ordered by Z, order them all, calls actors Step
		//					EndScene, renders actors, calls actors StepEnd
		//also Load and Unload 		
		
	public:
		CTyScene();
		~CTyScene();
		CTyScene(CTyScene const& pScene);
		CTyScene& operator = (CTyScene const& pScene);

		/*
		 * RESOURCE RELATED FUNCTIONS
		 *
		 *	Each scene looks up for its own 'm_Name.group' file for resources
		 */
		void	Load(); //load resources into memory
		void	Unload(); //free resources

		/*
		 * SCENE LOGIC RELATED FUNCTIONS
		 */
		void	Start(); //setup scene logic
		void	Finish(); //cleanup scene logic

		void	BeginScene();
		void	EndScene();
};
