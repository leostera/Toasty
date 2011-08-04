/***********************************************************************************

	class			IwClock
	description		The almighty clock. returns time in ms from loop to loop and
					is capable of frame rate capping.

	date			07/13/2011
	version			1.5
	notes			now a singleton with cool Marmalade like functions!

	author			Leandro 'The Phantom Lord' / 'Grün' Ostera
					leostera at gmail dot com

************************************************************************************/
#pragma once

#include <s3eTimer.h>

class IwClock
{
private:
	/*
	 *	method		Standard constructor
	 *
	 *	description			initializes the class properties to s3eTimerGetMs();
	 */
	IwClock() : m_TotalTicks(s3eTimerGetMs()),m_ThisTicks(s3eTimerGetMs()),m_LastTicks(s3eTimerGetMs()),m_Cap(0)
	{ ; }

	/*
	 *	m_Clock		static self-pointer used for the singleton pattern.
	 */
	static IwClock*	m_Clock;

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
	 *	method		IwGetClock
	 *
	 *	returns		IwClock*	pointer to the singleton class.
	 *
	 *	description		Serves as a public method for getting a pointer to the singleton.
	 */
	friend IwClock*	IwGetClock();

	/*
	 *	method		IwClockInit
	 *
	 *	returns		void
	 *
	 *	description			Initializes the class by creating the singleton. 
	 *						Note: not strictly necessary since IwGetClock also calls it just in case!
	 */
	friend void		IwClockInit();

	/*
	 *	method		IwClockTerminate
	 *
	 *	returns		void
	 *
	 *	description			Kills the singleton. This one IS necessary, otherwise leaks will be reported.
	 */
	friend void		IwClockTerminate();


public:
	/*
	 *	method		getTicks
	 *
	 *	returns		int64	The amount of ticks since last call to Step()
	 *
	 *	description			Returns the amount of ticks since the last call to Step()
	 */
	inline int64 getTicks(){
		return (m_ThisTicks - m_LastTicks);
	}
	
	/*
	 *	method		Step
	 *
	 *	returns		int64	Also the amount of ticks since last call to Step()
	 *
	 *	description			Accumulates ticks in m_TotalTicks and a lil' algebra to get each tick into it's place.
	 */
	inline int64 Step(){
		m_LastTicks = m_ThisTicks;
		m_ThisTicks = s3eTimerGetMs();
		m_TotalTicks += m_ThisTicks;
		return (m_ThisTicks - m_LastTicks);
	}

	/*
	 *	method		setCap
	 *
	 *	parameters	pCap	The amount of frames per second, or a non positive value if frame capping is to be disabled.
	 *
	 *	returns		void
	 *
	 *	description			Sets current frames per second cap to pCap if it is positive, otherwise to ZERO.
	 */
	inline void	SetCap(int32 pCap){
		if(pCap > 0)
			m_Cap = pCap;
		else
			m_Cap = 0;
	}

	/*
	 *	method		Cap
	 *
	 *	returns		int32	current amount of frames per second or ZERO if frame capping is disabled.
	 *
	 *	description			If frame capping is enabled (m_Cap > 0) we will wait long enough to let only m_Cap frames be displayed every second.
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


/*
 *	FRIEND CLASSES IMPLEMENTATIONS
 */

void IwClockInit()
{
	if(!IwClock::m_Clock)
		IwClock::m_Clock = new IwClock();
}

void IwClockTerminate()
{
	if(IwClock::m_Clock)
		delete IwClock::m_Clock;
}

IwClock* IwGetClock() 
{
	IwClockInit();
	return IwClock::m_Clock;
}