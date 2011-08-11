/*!**********************************************************************************

	\class			ITyActor
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

/*!
 * \enum	TOASTY_ACTOR_STATE
 * \brief	Actor State enumeration
 *	You might provide your own set of states but these (so far) are useful enough.
 */
enum TOASTY_ACTOR_STATE {
		TOASTY_ACTOR_WALKING=0,	/*! Actor is moving */
		TOASTY_ACTOR_ATTACKING, /*! Actor is attacking */
		TOASTY_ACTOR_DEFENDING, /*! Actor is defending */
		TOASTY_ACTOR_STANDING,  /*! Actor is holding position */
		TOASTY_ACTOR_APPEARING, /*! Actor is appearing */
		TOASTY_ACTOR_DYING,		/*! Actor is dying */
		TOASTY_ACTOR_DEAD,		/*! Actor is dead */
		TOASTY_ACTOR_IDLE		/*! Actor is idle */
	};

class ITyActor {
	
	private:
		/*!
		 * \property	m_ID	Long int used as Actor constant identifier.
		 */
		const int64				m_ID;

		/*!
		 * \property	m_Built	Bool flag telling whether the Actor has been built or not.
		 */
		bool					m_Built;

	protected:
		/*!
		 * \property	m_Name	std::string for the name of the actor.
		 */
		std::string				m_Name;

		/*!
		 * \property	m_Role	std::string for the role of the actor in the scene.
		 */
		std::string				m_Role;
		
		/*!
		 * \property	m_Depth	Depth of the actor (if ZOrdered is active in an scene, actors will be sorted by depth) as integer (can be negative).
		 */
		int						m_Depth;

		/*!
		 * \property	m_Active	Bool flag that determines whether it should be processed or skipped.
		 */
		bool					m_Active;

		/*!
		 * \property	m_Visible	Bool flag that determines whether the actor should be drawn or not.
		 */
		bool					m_Visible;

		/*!
		 * \property	m_Solid		Bool flag used for collision checking.
		 */
		bool					m_Solid;

		/*!
		 *	\class	CTyState
		 *	\brief	Inner class used to relate a Actor State with a Sprite.
		 */
		class CTyState {
		public:
			/*!
			 * \property	sprite	TySprite representing the actors state.
			 */
			CTySprite*			sprite;

			/*!
			* \property		state	TOASTY_ACTOR_STATE value.
			*/
			TOASTY_ACTOR_STATE	state;

			/*!
			 *	\brief	Constructor
			 *	\param	pSprite	TySprite to associate with pState
			 *	\param	pState	TOASTY_ACTOR_STATE to associate with pSprite
			 *
			 *	Simply inits internal values.
			 */
			CTyState( CTySprite* pSprite = 0, TOASTY_ACTOR_STATE pState = TOASTY_ACTOR_IDLE): sprite(pSprite), state(pState)
			{
				;
			}
		};

		/*!
		 * \property	m_States	std::vector of TyStates used to contain all the states of the actor
		 */
		std::vector<CTyState>	m_States;

		/*!
		 * \property	m_CurrentState	Pointer to the current state.
		 */
		CTyState*				m_CurrentState;

		/*!
		 * \property	m_LastState	Pointer to the last state.
		 */
		CTyState*				m_LastState;

		/*!
		 * \property	m_Mask	IwRect representing actors collision mask
		 */
		CIwRect					m_Mask;

		/*!
		 * \property	m_Position	IwSVec2 vector representing the (x,y) position of the actor from the scene (0,0). This is, it is a relative value and depends on the scene position on screen.
		 */
		CIwSVec2				m_Position;

		friend class CTyScene;

	public:
		/*!
		 *	\brief	Constructor
		 *	\param	pID			Integer value for the Actor ID.
		 *	\param	pActive		Boolean value. True if active, false otherwise.
		 *	\param	pVisible	Boolean value. True if visible, false otherwise.
		 *	\param	pSolid		Boolean value. True if solid, false otherwise.
		 *	\param	pMask		CIwRect(x,y,w,h). Actors collision mask, relative to Actors position.
		 *	\param	pPosition	CIwSVec2(x,y).	Actors position. Relative to Scene position.
		 *
		 *	This is the main constructor. It initializes the following m_rom_erties:
		 *					\arg	\c m_ID			, pID. Remember this is a constant!
		 *					\arg	\c m_Built		, true
		 *					\arg	\c m_Depth		, 0
		 *					\arg	\c m_Active		, true
		 *					\arg	\c m_Visible	, true
		 *					\arg	\c m_Solid		, true
		 *					\arg	\c m_Mask		, CIwRect(0,0,0,0)
		 *					\arg	\c m_Position	, CIwSVec2(0,0)
		 */
		ITyActor(int64 pID, bool pActive = true, bool pVisible = true, bool pSolid = true, CIwRect pMask = CIwRect(0,0,0,0), CIwSVec2 pPosition = CIwSVec2::g_Zero)
			: m_ID(pID), m_Built(true), m_Depth(0), m_Active(pActive), m_Visible(pVisible), m_Solid(pSolid), m_Mask(pMask), m_Position(pPosition)
		{ 
			;
		}

		/*!
		 *	\brief	Destructor
		 *	It actually does nothing.
		 */
		virtual ~ITyActor()
		{
			;
		}
	
		/*!
		 *	\brief	Is the actor built?
		 *	\returns bool	True if built, false otherwise.
		 */
		bool	IsBuilt()	const	{	return m_Built;		}

		/*!
		 *	\brief	Is the actor active?
		 *	\returns bool	True if active, false otherwise.
		 */
		bool	IsActive()	const	{	return m_Active;	}
		
		/*!
		 *	\brief	Is the actor visible?
		 *	\returns bool	True if visible, false otherwise.
		 */
		bool	IsVisible() const	{	return m_Visible;	}
		
		/*!
		 *	\brief	Is the actor solid?
		 *	\returns bool	True if solid, false otherwise.
		 */
		bool	IsSolid()	const	{	return m_Solid;		}

		/*!
		 *	\brief	Adds a new state to the State Vector.
		 *
		 *	\param	pSprite	TySprite sprite to associate with pState.
		 *	\param	pState	TOASTY_ACTOR_STATE state to associate with pSprite.
		 *
		 *	\returns bool	True if added succesfully, false if pState is already associated to a Sprite.
		 *
		 *	It instantiates a new CTyState object and pushes it back in the m_State vector if pState is not yet associated to a pSprite in the vector.
		 */
		bool	AddState(CTySprite* pSprite, TOASTY_ACTOR_STATE pState);

		/*!
		 *	\brief	Deletes a state from the State Vector.
		 *
		 *	\param	pState	TOASTY_ACTOR_STATE state to delete.
		 *
		 *	\returns bool	True if deleted succesfully, false if pState is not in the vector.
		 *
		 *	Deletes the state pState from m_State if it is there and if it is not the current state.
		 */
		bool	DeleteState(TOASTY_ACTOR_STATE pState);

		/*!
		 *	\brief	Sets a state from the State Vector as current state.
		 *
		 *	\param	pState	TOASTY_ACTOR_STATE state to set as current.
		 *
		 *	\returns bool	True if set succesfully, false such state is not in the State Vector.
		 */
		bool	SetCurrentState(TOASTY_ACTOR_STATE pState);
		
/*!
		 *	\brief	Will be called once the actor is added to a scene.
		 *	\returns bool
		 */
		virtual bool	OnCreate()											{ return true; }

		/*!
		 *	\brief	Will be called once the actor is removed from a scene.
		 *	\returns bool
		 */
		virtual bool	OnDestroy()											{ return true; }

		/*!
		 *	\brief	Will be called on Keyboard Press event.
		 *	\returns void
		 */
		virtual void	OnKeyPress(s3eKey pKey)								{ ; }

		/*!
		 *	\brief	Will be called on Keyboard Release event.
		 *	\returns void
		 */
		virtual void	OnKeyRelease(s3eKey pKey)							{ ; }

		/*!
		 *	\brief	Will be called if a Key is hold.
		 *	\returns void
		 */
		virtual void	OnKeySustain(s3eKey pKey, int64 pMS)				{ ; }

		/*!
		 *	\brief	Will be called if the Screen is touched.
		 *	\returns void
		 */
		virtual void	OnTouchPress(int pX, int pY )						{ ; }

		/*!
		 *	\brief	Will be called if the Screen is hold.
		 *	\returns void
		 */
		virtual void	OnTouchSustain(int pX, int pY, int64 pMS)			{ ; }

		/*!
		 *	\brief	Will be called if a Screentouch is released.
		 *	\returns void
		 */
		virtual void	OnTouchRelease(int pX, int pY)						{ ; }

		/*!
		 *	\brief	Will be called if the screen is touch and then dragged.
		 *	\returns void
		 */
		virtual void	OnTouchDrag(int pX, int pY, int pRelX, int pRelY)	{ ; }

		/*!
		 *	\brief	Will be called if Actor is about to collide with Scene boundaries.
		 *	\returns void
		 */
		virtual void	OnIntersectBoundaries(CIwRect pBoundaries)			{ ; }

		/*!
		 *	\brief	Will be called First in each step,  if Active.
		 *	\returns void
		 */
		virtual void	OnStepStart()										{ ; }	//first		called method

		/*!
		 *	\brief	Will be called Second in each step,  if Active.
		 *	\returns void
		 */
		virtual void	OnStep()											{ ; }	//second	

		/*!
		 *	\brief	Will be called after Rendering in each step, if Active.
		 *	\returns void
		 */
		virtual void	OnStepEnd()											{ ; }	//this one is called after OnRender so if you need to update anything between rendering and OnStepStart, do it here

		/*!
		 *	\brief	Will be called before StepEnd, but at the end of each step, if Visible.
		 *	\returns void
		 */
		virtual void	OnRender()											{ ; }	//this is called before OnStepEnd and after OnStep

		/*!
		 *	\brief	Will be called when two actors collide, if Solid.
		 *	\returns void
		 */
		virtual void	OnCollision(ITyActor const& pActor)					{ ; }

		/*!
		 *	\brief	Accessor for the Actors ID.
		 *	\returns int64	The actors ID.
		 */
		int64				GetID()				const		{	return m_ID;					}

		/*!
		 *	\brief	Accessor for the Actors Name.
		 *	\returns std::string	The actors Name.
		 */
		std::string			GetName()			const		{	return m_Name;					}

		/*!
		 *	\brief	Accessor for the Actors Role.
		 *	\returns std::string	The actors Role.
		 */
		std::string			GetRole()			const		{	return m_Role;					}

		/*!
		 *	\brief	Accessor for the Actors Depth.
		 *	\returns int	The actors Depth.
		 */
		int					GetDepth()			const		{	return m_Depth;					}

		/*!
		 *	\brief	Accessor for the Actors Current State.
		 *	\returns TOASTY_ACTOR_STATE	The actors Current State as TOASTY_ACTOR_STATE.
		 */
		TOASTY_ACTOR_STATE	GetCurrentState()	const		{	return m_CurrentState->state;	}

		/*!
		 *	\brief	Accessor for the Actor Last State.
		 *	\returns TOASTY_ACTOR_STATE	The actors Last State as TOASTY_ACTOR_STATE.
		 */
		TOASTY_ACTOR_STATE	GetLastState()		const		{	return m_LastState->state;		}

		/*!
		 *	\brief	Accessor for the Actors Mask.
		 *	\returns CIwRect	The actors mask as CIwRect.
		 */
		CIwRect				GetMask()			const		{	return m_Mask;					}

		/*!
		 *	\brief	Accessor for the Actors Position.
		 *	\returns CIwSVec2	The actors position as CIwSVec2.
		 */
		CIwSVec2			GetPosition()		const		{	return m_Position;				}

		/*!
		 *	\brief Mutator for the Actors Name
		 *	\param	pName	std::string of the name.
		 */
		void	SetName(std::string pName)					{	m_Name     = pName;			}

		/*!
		 *	\brief Mutator for the Actors Role
		 *	\param	pRole	std::string of the Role.
		 */
		void	SetRole(std::string pRole)					{	m_Role     = pRole;			}
		
		/*!
		 *	\brief Mutator for the Actors Depth
		 *	\param	pDepth	int for the Depth.
		 */
		void	SetDepth(int pDepth)						{	m_Depth    = pDepth;		}
		
		/*!
		 *	\brief Mutator for the Actors Active flag.
		 *	\param	pActive	boolean for Active;
		 */
		void	SetActive(bool pActive)						{	m_Active   = pActive;		}
		
		/*!
		 *	\brief Mutator for the Actors Visible flag.
		 *	\param	pVisible	boolean for Visible;
		 */
		void	SetVisible(bool pVisible)					{	m_Visible  = pVisible;		}
		
		/*!
		 *	\brief Mutator for the Actors Solid flag.
		 *	\param	pSolid	boolean for Solid;
		 */
		void	SetSolid(bool pSolid)						{	m_Solid    = pSolid;		}		
		
		/*!
		 *	\brief Mutator for the Actors Collision Mask.
		 *	\param	pMask	CIwRect rect for the Collision Mask.
		 */
		void	SetMask(CIwRect pMask)						{	m_Mask	   = pMask;			}
		
		/*!
		 *	\brief Mutator for the Actors Position.
		 *	\param	pPosition	CIwSVec2 vector for Position.
		 */
		void	SetPosition(CIwSVec2 pPosition)				{	m_Position = pPosition;		}
};