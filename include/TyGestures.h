#pragma once

#ifndef TOASTY_GESTURES_H
#define TOASTY_GESTURES_H

#include <s3ePointer.h>
#include <IwGxTypes.h>

enum	TOASTY_GESTURES {
	TOASTY_GESTURES_SLIDE
}

class TyGesture : public CIwManaged
{
	TOASTY_GESTURES		Type;
	CIwManagedList		Touches;
	bool				Active;

public:
	TyGesture() : Active(false)
	{;}

	TyGesture&	operator= (TyGesture const& pTyGesture)
	{
		this->Type = pTyGesture.Type;
		this->Touches.CopyList(pTyGesture); 
		this->Active = pTyGesture.Active;
		return (*this);
	}
};

class TyGestures
{
private:
	CIwManagedList			m_Gestures;
	TyTouch*				m_LastGesture;
	TyTouch*				m_CurrentGesture;

public:	
	TyGestures();
	~TyGestures();

	bool		Update();
	TyGesture	GetLastGesture();
};

#endif