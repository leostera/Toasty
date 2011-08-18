#pragma once

#ifndef TOASTY_INPUT_H
#define TOASTY_INPUT_H

#include <s3ePointer.h>
#include <IwManaged.h>
#include <IwManagedList.h>
#include <IwGxTypes.h>

void TyInputInit();
void TyInputTerminate();

class TyInput;
TyInput* TyGetInput();

class TyTouch : public CIwManaged
{
public:
	const int				TOASTY_TOUCH_MULTI_MAX;

	uint32					TouchID;

	CIwSVec2				FirstPosition;
	CIwSVec2				Position;
	CIwSVec2				LastPosition;
	CIwSVec2				DeltaPosition;
	CIwSVec2				Velocity;
	CIwSVec2				DistanceToLast;

	uint64					TimeSinceLastPress;
	uint64					TimeHold;
	uint16					DoubleTapCounter;
	bool					DoubleTap;

	bool					Active;
	bool					Drag;	
	s3ePointerState			State;

	TyTouch(uint32 pTouchID) : TouchID(pTouchID), DistanceToLast(CIwSVec2::g_Zero),Velocity(CIwSVec2::g_Zero),
								DoubleTap(false), DoubleTapCounter(0),TOASTY_TOUCH_MULTI_MAX(S3E_POINTER_TOUCH_MAX),
								TimeSinceLastPress(0), Position(CIwSVec2::g_Zero),LastPosition(CIwSVec2::g_Zero),
								DeltaPosition(CIwSVec2::g_Zero),Active(false),Drag(false),State(S3E_POINTER_STATE_UP)
	{;}

	/*!
	 *	\brief	Assignment operator
	 *
	 *	\param	pTouch	The touch object to be assigned (copied)
	 *
	 *	Copies all data from the touch parameter object.
	 */
	TyTouch&	operator= (TyTouch const& pTouch)
	{
		this->TouchID = pTouch.TouchID;
		this->FirstPosition = pTouch.FirstPosition;
		this->Position = pTouch.Position;
		this->LastPosition = pTouch.LastPosition;
		this->DeltaPosition = pTouch.DeltaPosition;
		this->Velocity = pTouch.Velocity;
		this->DistanceToLast = pTouch.DistanceToLast;
		this->TimeSinceLastPress = pTouch.TimeSinceLastPress;
		this->TimeHold = pTouch.TimeHold;
		this->DoubleTapCounter = pTouch.DoubleTapCounter;
		this->DoubleTap = pTouch.DoubleTap;
		this->Active = pTouch.Active;
		this->Drag = pTouch.Drag;
		this->State = pTouch.State;
		return (*this);
	}
};

class TyInput
{
private:
	static TyInput*	m_Instance;
	friend void		TyInputInit();
	friend void		TyInputTerminate();
	friend TyInput* TyGetInput();

	CIwManagedList			m_Touches;
	TyTouch*				m_LastTouchPressed;
	TyTouch*				m_LastTouchReleased;
	TyTouch*				m_LastTouchDragged;
	bool					m_MultiTouchSupport;

	TyInput();
	~TyInput();
	void CheckForMultitouchSupport();

public:	
	bool		RefreshTouchpad();

	TyTouch		GetTouchInRect(CIwRect pArea, s3ePointerState pState);

	TyTouch		GetLastTouchPressed();
	TyTouch		GetLastTouchReleased();
	TyTouch		GetLastTouchDragged();
};

#endif