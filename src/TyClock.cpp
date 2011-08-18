#include <TyClock.h>
#include <s3eDevice.h>

TyClock* TyClock::m_Instance = 0;

/*
 *	FRIEND FUNCTIONS IMPLEMENTATIONS
 */

void TyClockInit()
{
	if(TyClock::m_Instance == 0)
		TyClock::m_Instance = new TyClock();
}

void TyClockTerminate()
{
	if(TyClock::m_Instance != 0)
		delete TyClock::m_Instance;
	TyClock::m_Instance = 0;
}

TyClock* TyGetClock() 
{
	return TyClock::m_Instance;
}

/*
 *	CLASS METHODS IMPLEMENTATIONS
 */
uint64	TyClock::Update()
{
	m_LastTicks = m_ThisTicks;
	m_ThisTicks = s3eTimerGetMs();
	m_TotalTicks += m_ThisTicks;
	return (m_ThisTicks - m_LastTicks);
}

void		TyClock::SetCap(int32 pCap)
{
	if(pCap > 0)
		m_Cap = pCap;
	else
		m_Cap = 0;
}

int32	TyClock::Cap()
{
	if(m_Cap > 0)
		{
			while (s3eTimerGetMs()-m_ThisTicks < ( 1000/m_Cap ) )
			{
				int32 yield = (int32) ( ( 1000/m_Cap ) - (s3eTimerGetMs()-m_ThisTicks ) );
				if (yield<0)
					break;
				s3eDeviceYield(yield);
			} 
		}
	return m_Cap;
}

uint64	TyClock::GetTicks()
{
	return (m_ThisTicks - m_LastTicks);
}