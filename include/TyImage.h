#pragma once

#include <Iw2D.h>
#include <IwResManager.h>
#include <IwGxTypes.h>
#include <string>

class TyImage
{
private:
	/*!
	 *	is the pointer to CIwImage that actually holds the sprite sheet image.
	 *	It uses the Marmalade SDK resource manager to load it
	 */
	CIw2DImage*		m_Image;

	/*!
	 *	name of the resource loaded into m_Image;
	 */
	std::string		m_ResourceName;

	/*!
	 *	name of the group where the resource named m_ResourceName is located
	 */
	CIwResGroup*	m_ResourceGroup;

	bool m_Built;
	int m_H,m_W;

public:
	/*!
	 *	\brief	Parameterized constructor
	 *
	 *	\param	pGroup	the resource group inwhere to look for the resource
	 *	\param	pName	the name of the resource to look up in the group
	 *
	 *	This is the main constructor. It initializes the following properties:
	 *					\arg	\c m_Built, false
	 */
	TyImage(CIwResGroup* pGroup, std::string pName);
	~TyImage();

	/*!
	 *	\brief	Render the animation.
	 *
	 *	\returns		void
	 *
	 *	\param	pPosition	(x,y) 2D integer vector
	 *
	 *	Draws a region of the image starting at m_DrawRect and finishing at m_DrawRect+m_FrameSize,
	 *	at the coordinates passed by pPosition.
	 */
	void		Render(CIwSVec2 pPosition = CIwSVec2::g_Zero);

	CIwSVec2	GetSize() const { return CIwSVec2(m_W,m_H); }
};