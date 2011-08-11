#pragma once

#include <IwResManager.h>
#include <TyActor.h>
#include <string>
#include <vector>

class CTyScene{

	private:
		const	int64	m_ID;

	protected:
		std::string				m_ResGroupName;
		CIwResGroup*			m_ResGroup;

		std::string				m_Name;
		std::string				m_Caption;

		std::vector<ITyActor*>	m_Actors;
		bool					m_ZOrdered;
		bool					m_Created;
		//CIw2DImage*				m_Background;
		CIwRect					m_Boundaries;

		//back-track music, 
		//possible methods: BeginScene, renders background, calls actors StepStart, if not ordered by Z, order them all, calls actors Step
		//					EndScene, renders actors, calls actors StepEnd
		//also Load and Unload 		
		
	public:
		CTyScene(std::string pName, std::string pCaption, std::string pResGroup = std::string(""), int64 pID = 0, bool pZOrdered = false);
		~CTyScene();

		bool	AddActor(ITyActor* pActor);
		bool	DeleteActor(ITyActor* pActor);

		/*
		 * RESOURCE RELATED FUNCTIONS
		 *
		 *	Each scene looks up for its own 'm_Name.group' file for resources
		 */
		bool	Create(); //load resources into memory
		bool	Destroy(); //free resources

		/*
		 * SCENE LOGIC RELATED FUNCTIONS
		 */
		bool	Play();

		int64		GetID()				const {	return	m_ID;			}
		std::string	GetResGroupName()	const { return	m_ResGroupName;	}
		std::string	GetName()			const { return	m_Name;			}
		std::string	GetCaption()		const { return	m_Caption;		}
		CIwRect		GetBoundaries()		const { return  m_Boundaries;	}
		bool		IsZOrdered()		const { return	m_ZOrdered;		}

		void		SetBoundaries(CIwRect pBoundaries = CIwRect(0,0,0,0))	{	m_Boundaries = pBoundaries; }
		
};
