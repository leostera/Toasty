/*!**********************************************************************************

	\class			TyDebug
	\brief			Debug output singleton.
	\date			15/08/2011
	\version		0.1					
	\author			Leandro Ostera

************************************************************************************/


#pragma once

#ifndef TOASTY_DEBUG_H
#define TOASTY_DEBUG_H

/*
	exit on error
	pause on warning

	possible structure would be inner exception derived class TyException(msg,code)
	to be thrown. that would be nice if well implemented! KEEP IN MIND
*/

class TyDebug 
{
public:
	static void	ReportError( std::string const & pErrorString, int pErrorCode );
	static void	ReportWarning( std::string const & pWarningString, int pWarningCode );
	static void	ReportMessage( std::string const & pMessageString);

	static void Dump();

	static void	ScreenReportError( std::string const & pErrorString, int pErrorCode );
	static void	ScreenReportWarning( std::string const & pWarningString, int pWarningCode );
	static void	ScreenMessage( std::string const & pMessageString);

	static void ScreenDump();
};

#endif