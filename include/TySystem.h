/*!**********************************************************************************

	\class			TySystem
	\brief			System singleton.
	\date			15/08/2011
	\version		0.1					
	\author			Leandro Ostera

************************************************************************************/

#pragma once

#ifndef TOASTY_SYSTEM_H
#define TOASTY_SYSTEM_H

#include <Iw2D.h>
#include <IwResManager.h>
#include <TySingleton.h>

enum TOASTY_SYSTEMS {
	TOASTY_INIT_ALL = 0,
	TOASTY_INIT_2D,	
	TOASTY_INIT_2D_LITE,	
	TOASTY_INIT_GX,
	TOASTY_INIT_GL,	
	TOASTY_INIT_CLOCK,
	TOASTY_INIT_INPUT,
	TOASTY_INIT_SCENEMGR
}

class TySystem
{
private:
	static TySystem*	m_Instance;
	
	CIwManagedList	m_ResourceGroups;
	
	TySystem();
	~TySystem();

	friend bool	TySystemInit(TOASTY_SYSTEMS pFlags, bool pExitOnFail);
	friend bool TySystemTerminate(TOASTY_SYSTEMS pFlags);

public:
	bool Init(TOASTY_SYSTEMS pFlags, bool pExitOnFail = true);
	bool Terminate();

	bool GetSubSystemState(TOASTY_SYSTEMS pSubsystem);

	bool LoadGroup(std::string pGroup);
	bool DestroyGroup(std::string pGroup);
};

bool TySystemInit(TOASTY_SYSTEMS pFlags, bool pExitOnFail = true)
{
	return TySystem::m_Instance->Init(pFlags,pExitOnFail);
}

bool TySystemTerminate(TOASTY_SYSTEMS pFlags)
{
	return TySystem::m_Instance->Terminate(pFlags);
}

#endif