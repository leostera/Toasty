/***********************************************************************************

	\class			TyClock
	\brief			The almighty clock. returns time in ms from loop to loop and
					is capable of frame rate capping.

	\date			07/13/2011
	\version		1.5
	\notes			now a singleton with cool Marmalade like Init,Terminate,Get functions!

	\author			Leandro 'The Phantom Lord' / 'Grün' Ostera
					leostera at gmail dot com

************************************************************************************/
#pragma once

#include <s3eTimer.h>

class TyClock
{
private:
	/*
	 *	\brief	Standard constructor
	 *	Initializes the class properties to s3eTimerGetMs();
	 */
	TyClock() : m_TotalTicks(s3eTimerGetMs()),m_ThisTicks(s3eTimerGetMs()),m_LastTicks(s3eTimerGetMs()),m_Cap(0)
	{ ; }

	/*
	 *	m_Instance		static self-pointer used for the singleton pattern.
	 */
	static TyClock*	m_Instance;

	/*
	 *	m_TotalTicks	the total amount of ticks
	 */
	int64			m_TotalTicks;

	/*
	 *	m_LastTicks		the amount of ticks from the last iteration
	 */	
	int64			m_LastTicks;

	/*
	 *	m_ThisTicks		current amount of ticks
	 */
	int64			m_ThisTicks;

	/*
	 *  m_Cap			amount of frames per second
	 */
	int32			m_Cap;
	
	/*
	 *	FRIEND FUNCTIONS DECLARATIONS
	 */

	/*
	 *	\brief		Gets you a clock.
	 *
	 *	\returns	TyClock*	pointer to the singleton class.
	 *
	 *	Serves as a public method for getting a pointer to the singleton.
	 */
	friend TyClock*	TyGetClock();

	/*
	 *	\brief		Starts the clock.
	 *
	 *	\returns	void
	 *
	 *	Initializes the class by creating the singleton. Note: not strictly necessary since IwGetClock also calls it just in case!
	 */
	friend void		TyClockInit();

	/*
	 *	\brief		Terminates the clock.
	 *
	 *	\returns	void
	 *
	 *	Kills the singleton. This one IS necessary, otherwise leaks will be reported.
	 */
	friend void		TyClockTerminate();


public:
	/*
	 *	\brief	Gets you ticks.
	 *
	 *	\returns	int64	The amount of ticks since last call to Step()
	 *
	 *	Returns the amount of ticks since the last call to Step().
	 */
	inline int64 GetTicks(){
		return (m_ThisTicks - m_LastTicks);
	}
	
	/*
	 *	\brief	Updates the clock. 
	 *
	 *	\returns	int64	Also the amount of ticks since last call to Step()
	 *
	 *	Accumulates ticks in m_TotalTicks and a lil' algebra to get each tick into it's place.
	 *	Should be called just once at the end of the program loop.
	 */
	inline int64 Step(){
		m_LastTicks = m_ThisTicks;
		m_ThisTicks = s3eTimerGetMs();
		m_TotalTicks += m_ThisTicks;
		return (m_ThisTicks - m_LastTicks);
	}

	/*
	 *	\brief	Sets the cap rate.
	 *
	 *	\param	pCap	The amount of frames per second, or a non positive value if frame capping is to be disabled.
	 *
	 *	\returns	void
	 *
	 *	Sets current frames per second cap to pCap if it is positive, otherwise to ZERO.
	 */
	inline void	SetCap(int32 pCap){
		if(pCap > 0)
			m_Cap = pCap;
		else
			m_Cap = 0;
	}

	/*
	 *	\brief	Caps.
	 *
	 *	\returns	int32	current amount of frames per second or ZERO if frame capping is disabled.
	 *
	 *	If frame capping is enabled (m_Cap > 0) we will wait long enough to let only m_Cap frames be displayed every second.
	 */
	inline int32	Cap() {
		if(m_Cap > 0)
		{
			while (s3eTimerGetMs()- getTicks() < ( 1000/m_Cap ) )
			{
				int32 yield = (int32) ( ( 1000/m_Cap ) - (s3eTimerGetMs()-getTicks() ) );
				if (yield<0)
					break;
				s3eDeviceYield(yield);
			}
		}
		return m_Cap;
	}
};

TyClock* TyClock::m_Instance = 0;

/*
 *	FRIEND FUNCTIONS IMPLEMENTATIONS
 */

void TyClockInit()
{
	if(!TyClock::m_Instance)
		TyClock::m_Instance = new TyClock();
}

void TyClockTerminate()
{
	if(TyClock::m_Instance)
		delete TyClock::m_Instance;
}

TyClock* TyGetClock() 
{
	TyClockInit();
	return TyClock::m_Instance;
}