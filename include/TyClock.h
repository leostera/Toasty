/*!**********************************************************************************

	\class			TyClock
	\brief			The almighty clock. Returns time in ms from loop to loop and
					is capable of frame rate capping.

	\date			07/13/2011
	\version		1.5
	\notes			Now a singleton with cool Marmalade like Init,Terminate,Get functions!

	\author			Leandro 'The Phantom Lord' / 'Grün' Ostera
					leostera at gmail dot com

************************************************************************************/
#pragma once

#ifndef TOASTY_CLOCK_H
#define TOASTY_CLOCK_H

#include <s3eTimer.h>

void TyClockInit();
void TyClockTerminate();

class TyClock;
TyClock* TyGetClock();

class TyClock
{
private:
	/*!
	 *	\brief	Standard constructor
	 *	Initializes the class properties to 0;
	 */
	TyClock() : m_TotalTicks(0),m_ThisTicks(0),m_LastTicks(0),m_Cap(0)
	{ ; }

	/*!
	 *	m_Instance		static self-pointer used for the singleton pattern.
	 */
	static TyClock*	m_Instance;

	/*!
	 *	m_TotalTicks	the total amount of ticks
	 */
	uint64			m_TotalTicks;

	/*!
	 *	m_LastTicks		the amount of ticks from the last iteration
	 */	
	uint64			m_LastTicks;

	/*!
	 *	m_ThisTicks		current amount of ticks
	 */
	uint64			m_ThisTicks;

	/*!
	 *  m_Cap			amount of frames per second
	 */
	int32			m_Cap;
	
	/*!
	 *	FRIEND FUNCTIONS DECLARATIONS
	 */

	/*!
	 *	\brief		Gets you a clock.
	 *
	 *	\returns	TyClock*	pointer to the singleton class.
	 *
	 *	Serves as a public method for getting a pointer to the singleton.
	 */
	friend TyClock*	TyGetClock();

	/*!
	 *	\brief		Starts the clock.
	 *
	 *	\returns	void
	 *
	 *	Initializes the class by creating the singleton. Note: not strictly necessary since IwGetClock also calls it just in case!
	 */
	friend void		TyClockInit();

	/*!
	 *	\brief		Terminates the clock.
	 *
	 *	\returns	void
	 *
	 *	Kills the singleton. This one IS necessary, otherwise leaks will be reported.
	 */
	friend void		TyClockTerminate();


public:
	/*!
	 *	\brief	Gets you ticks.
	 *
	 *	\returns	uint64	The amount of ticks since last call to Step()
	 *
	 *	Returns the amount of ticks since the last call to Step().
	 */
	uint64 GetTicks();
	
	/*!
	 *	\brief	Updates the clock. 
	 *
	 *	\returns	uint64	Also the amount of ticks since last call to Step()
	 *
	 *	Accumulates ticks in m_TotalTicks and a lil' algebra to get each tick into it's place.
	 *	Should be called just once at the end of the program loop.
	 */
	uint64 Update();

	/*!
	 *	\brief	Sets the cap rate.
	 *
	 *	\param	pCap	The amount of frames per second, or a non positive value if frame capping is to be disabled.
	 *
	 *	\returns	void
	 *
	 *	Sets current frames per second cap to pCap if it is positive, otherwise to ZERO.
	 */
	void	SetCap(int32 pCap);

	/*!
	 *	\brief	Caps.
	 *
	 *	\returns	uint64	current amount of frames per second or ZERO if frame capping is disabled.
	 *
	 *	If frame capping is enabled (m_Cap > 0) we will wait long enough to let only m_Cap frames be displayed every second.
	 */
	int32	Cap();
};

#endif