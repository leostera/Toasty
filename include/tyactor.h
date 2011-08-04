/*!**********************************************************************************

	\class			CTyActor
	\brief			Actor class to be used within a scene.
	\date			2/08/2011
	\version		0.1					
	\author			Leandro Ostera

	Actor class to be used within a Scene class that works with states (CTyState)
	and is meant to be an interface with some virtual methods to be overloaded.

************************************************************************************/

#pragma once // might be more suitable to use define checks, but pragma once seems to work fine on almost every compiler

/*
 * Marmalade SDK Header file includes
 */
#include <TySprite.h>
#include <Iw2D.h>
#include <IwGxTypes.h>

/*
 * Standard C++ Header file includes
 */
#include <string>
#include <vector>

enum TOASTY_ACTOR_STATES {
		WALKING=0,
		ATTACKING,
		DEFENDING,
		STANDING,
		APPEARING,
		DYING,
		DEAD,		
		IDLE
	};

class CTyActor {
	
	private:
		static int64			m_ID;
		bool					m_Built;
/*
	protected:
		std::string				m_Name;
		std::string				m_Role;
		
		int						m_Depth;
		bool					m_Active;
		bool					m_Visible;
		bool					m_Solid;

		struct CTyState {
			CTySprite*			sprite;
			TOASTY_ACTOR_STATE	state;
		};

		std::vector<CTyState*>	m_States;
		CTyState*				m_CurrentState;
		CTyState*				m_LastState;

		CIwRect					m_Mask;
		CIwSVec2				m_Position;

		std::vector<CTyActor*>	m_Children;

		friend class CTyScene;
*/
	public:
		
		CTyActor(bool pActive = true, bool pVisible = true, bool pSolid = true, CIwRect pMask = CIwRect(0,0,0,0), CIwSVec2 pPosition = CIwSVec2::g_Zero)
			: m_Built(true)//, m_Depth(0), m_ID(++m_ID), m_Active(pActive), m_Visible(pVisible), m_Solid(pSolid), m_Mask(pMask), m_Position(pPosition)
		{ 
			;
		}
		virtual ~CTyActor();
		CTyActor(CTyActor const& pActor);
		CTyActor& operator = (CTyActor const& pActor);

		bool	IsBuilt() const { return m_Built; }
		/*

		int			AttachChild(CTyActor const& pChild);
		void		DettachChild(CTyActor const& pChild);

		bool		PushState(CTySprite* pSprite, TOASTY_ACTOR_STATE pState);
		bool		PopState(TOASTY_ACTOR_STATE pState);

		virtual void	OnLoad();
		virtual void	OnUnload();
		virtual void	OnKeyPress(s3eKey pKey);
		virtual void	OnKeyRelease(s3eKey pKey);
		virtual void	OnKeySustain(s3eKey pKey, int64 pMS);
		virtual void	OnTouchPress(int pX, int pY );
		virtual void	OnTouchSustain(int pX, int pY, int64 pMS);
		virtual void	OnTouchRelease(int pX, int pY);
		virtual void	OnTouchDrag(int pX, int pY, int pRelX, int pRelY);
		virtual void	OnIntersectBoundaries(CIwRect pBoundaries);
		virtual void	OnStepStart();	//first		called method
		virtual void	OnStep();		//second	
		virtual void	OnStepEnd();	//this one is called after OnRender so if you need to update anything between rendering and OnStepStart, do it here
		virtual void	OnRender();		//this is called before OnStepEnd and after OnStep
		virtual void	OnCollision(CTyActor const& pActor);
		virtual void	OnAnimationStart();
		virtual void	OnAnimationEnd();

		std::string			GetName() const;
		std::string			GetRole() const;
		int					GetDepth() const;
		bool				GetActive() const;
		bool				GetVisible() const;
		bool				GetSolid() const;
		TOASTY_ACTOR_STATE	GetCurrentState() const;
		TOASTY_ACTOR_STATE	GetLastState() const;
		CIwRect				GetMask() const;
		CIwSVec2			GetPosition() const;
		CTyActor*			GetChild()	const;

		void	SetName(std::string pName);
		void	SetRole(std::string pRole);
		void	SetDepth(int pDepth);
		void	SetActive(bool pActive);
		void	SetVisible(bool pVisible);
		void	SetSolid(bool pSolid);
		void	SetCurrentState(TOASTY_ACTOR_STATE pState);
		void	SetMask(CIwRect pMask);
		void	SetPosition(CIwSVec2 pPosition);
*/
};