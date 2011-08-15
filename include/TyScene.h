#pragma once

#include <IwResManager.h>
#include <TyActor.h>

#include <string>
#include <list>

class TyScene{

	private:
		const	int64	m_ID;

	protected:
		std::string				m_ResGroupName;
		CIwResGroup*			m_ResGroup;

		std::string				m_Name;
		std::string				m_Caption;

		std::list<ITyActor*>	m_Actors;
		bool					m_ZOrdered;
		bool					m_Created;
		TyImage*				m_Background;
		CIwRect					m_Boundaries;
		//back-track music, 
		
	public:
		TyScene(std::string pName = std::string(""), std::string pCaption = std::string(""), std::string pResGroup = std::string(""), int64 pID = 0, bool pZOrdered = false);
		~TyScene();

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

		void		SetName(std::string pName)		 { m_Name = pName;			}
		void		SetCaption(std::string pCaption) { m_Caption = pCaption;	}


		void		SetBoundaries(CIwRect pBoundaries = CIwRect(0,0,0,0))	{	m_Boundaries = pBoundaries; }
		
};