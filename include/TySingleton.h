#pragma once

#ifndef TOASTY_SINGLETON_H
#define TOASTY_SINGLETON_H

template <class T>

class TySingleton
{
private:
	static T*	m_Instance;

	bool		m_Built;

public:
	TySingleton()
	{
		m_Built = false;
	}

	~TySingleton()
	{
		this->Erase();
	}
	
	static T* GetPtr()
	{
		return (this->m_Built) ? this->m_Instance : 0 ;
	}

	static void Erase()
	{
		if ( this->m_Built )
		{
			delete this->m_Instance;
			this->m_Built = false;
		}
	}
};

#endif