/*!**********************************************************************************

	\class			TyImage
	\brief			Static image class.
	\date			14/08/2011
	\version		0.1					
	\author			Leandro Ostera

************************************************************************************/

#pragma once

#ifndef TOASTY_IMAGE_H
#define TOASTY_IMAGE_H

/*
 * Marmalade SDK Header file includes
 */
#include <IwResManagerClass.h>
#include <IwResGroup.h>
#include <IwGeomCore.h>
#include <Iw2D.h>

/*
 * Standard C++ Header file includes
 */
#include <string>


class TyImage
{
protected:
	/*!
	 * \property m_Built bool flag to determine whether the object is already built or not
	 */
	bool		m_Built; 

	/*!
	 * \property m_Flip CIwSVec2 vector determines if image is or not flipped in each axis.
	 */
	CIwSVec2	m_Flip;

	/*!
	 * \property m_Angle rotation angle in radians (32-bits integer)
	 */
	iwangle		m_Angle;

	/*!
	 * \property m_Center rotation Center.
	 */
	CIwSVec2	m_Center;

	/*!
	 *	is the pointer to CIwImage that actually holds the image sheet image.
	 *	It uses the Marmalade SDK resource manager to load it
	 */
	CIw2DImage*		m_Image;

	/*!
	 *	name of the resource loaded into m_SpriteSheet;
	 */
	std::string		m_ResourceName;

	/*!
	 *	name of the group where the resource named m_ResourceName is located
	 */
	CIwResGroup*	m_ResourceGroup;
	
	/*!
	 *	the actual size of the image x for width, y for height
	 */
	CIwSVec2	m_Size;

	//Private class methods: do not attempt to use in your own code!

	/*!
	 *	\brief	Loads a resource from a resource group.
	 *
	 *	\param	pGroup	the resource group inwhere to look for the resource
	 *	\param	pName	the name of the resource to look up in the group
	 *
	 *	\returns	bool	true if image was succesfully rebuilt, false otherwise.
	 *
	 *	Loads a resource named name from the resource group that group points to if the current
	 *	group is different from the one specified, the new group is set to be the current.
	 *  If the resource name and group equals the current resource name and group then nothing is done.
	 *  If current resource name differs from pName, current resource group is not pGroup,
	 *	the object has not yet been built or both the resource name and resource group has
	 *	not been set previously, set pGroup as current resource group, pName as current
	 *	resource name and try to load the resource.
	 *	If anything but error, the image should have been succesfully loaded into memory, and all
	 *	image-dependant properties of the class properly initialized.
	 */
	bool LoadFromResource(CIwResGroup* pGroup, std::string pName);
	
public:
	/*!
	 *	\brief	Null constructor. Does nothing: useful when inheriting.
	 */
	TyImage() : m_Built(false) { ; }

	/*!
	 *	\brief	Parameterized constructor
	 *
	 *	\param	pGroup	the resource group inwhere to look for the resource
	 *	\param	pName	the name of the resource to look up in the group
	 *	\param	pLoop	whether the image sohuld loop (true) or not (false
	 *
	 *	This is the main constructor. It initializes the following properties:
	 *					\arg	\c m_Built, false
	 */
	TyImage(CIwResGroup* pGroup, std::string pName);

	/*!
	 *	\brief	Cleans up the object.
	 *
	 *	Performs clean up of the asigned memory blocks. 
	 *  If the class has been succesfully built before, delete the image pointer as it is no longer needed.
	 */
	~TyImage();

	/*!
	 *	\brief	Copy constructor
	 *
	 *	\param	pImage	The image object to be copied
	 *
	 *	Copies the propierties of the parameter object into the object that is being constructed.
	 *	It uses the overloaded operator = to such ends. Current object flag m_Built will be set along
	 *	with flag m_Copy.
	 */
	TyImage(TyImage const& pImage);

	/*!
	 *	\brief	Assignment operator
	 *
	 *	\param	pImage	The image object to be assigned (copied)
	 *
	 *	Copies all data from the image parameter object, incluiding the pointer to the imagesheet.
	 */
	TyImage&	operator= (TyImage const& pImage);

	/*!
	 *	\brief	Comparison operator
	 *
	 *	\param	pImage1	A image object to compare against pImage2
	 *	\param	pImage2	A image object to compare against pImage1
	 *
	 *	\returns	bool
	 *
	 *	Compares both images and returns true if are equal, or false if not.
	 */
	bool		operator== (TyImage const& pImage) const;

	/*!
	 *	\brief Is the object built?
	 *
	 *	\returns		bool	
	 *
	 *	True if the image has been built, false otherwise.
	 */
	inline bool		IsBuilt()			const { return m_Built; }

	/*!
	 *	\brief Is the object flipped?
	 *
	 *	\returns		CIwSVec2
	 *
	 *	CIwSVec2 boolean vector with (1,0) for flipped on X, (0,1) for flipped on Y, (1,1) for flipped on both, and (0,0) for not flipped at all.
	 */
	inline CIwSVec2	IsFlipped()			const { return m_Flip; }

	/*!
	 *	\brief	Image width as CIwSVec2 integer vector.
	 *	\returns	CIwSVec2
	 */
	CIwSVec2	GetSize()			const { return m_Size; }

	/*!
	 *	\brief	Spritesheet width.
	 *
	 *	\returns		int16	
	 *
	 *	Returns current imagesheet width as integer.
	 */
	int16		GetWidth()			const { return m_Image->GetWidth(); }
	
	/*!
	 *	\brief	Spritesheet height.
	 *
	 *	\returns		int16
	 *
	 *	Returns current imagesheet height as integer.
	 */
	int16		GetHeigth()			const { return m_Image->GetHeight(); }

	/*!
	 *	\brief	Get the resource name string.
	 *
	 *	\returns		std::string
	 *
	 *	Returns a copy of the resource name as a std::string.
	 */
	std::string			GetResourceName()	const { return m_ResourceName; }

	/*!
	 *	\brief	Get the resources group pointer.	 
	 *
	 *	\returns		CIwResGroup*
	 *
	 *	Returns a pointer to the current resource group.
	 */
	CIwResGroup*		GetResourceGroup()	const { return m_ResourceGroup; }

	/*!
	 *	\brief	Pointer to const this.	 
	 *
	 *	\returns		const TyImage*
	 *
	 *	Returns a pointer to a const TyImage (which is this).
	 */
	const TyImage*	GetCopy()		const { return this; }

	/*!
	 *	\brief	Image rotation.
	 *
	 *	\returns	Returns the current angle in radians.
	 *
	 */
	iwangle		GetAngle()	const { return m_Angle; }

	/*!
	 *	\brief	Image rotation Center.
	 *
	 *	\returns	Returns the current Center as a vector.
	 *
	 */
	CIwSVec2	GetCenter()	const { return m_Center; }

	/*!
	 *	\brief	Rotates the image.
	 *	\returns	void
	 *	\param	pRads	Angle in radians (32-bits integer)
	 *
	 *	Rotates the image by pRads radians counterclockwise.
	 */
	void		Rotate(iwangle	pRads);

	/*!
	 *	\brief	Center the image for rotation
	 *	\returns	void
	 *	\param	pCenter	integer vector for image center.
	 *
	 *	Centers the image at the given coordinates for rotation.
	 */
	void		Center(CIwSVec2 pCenter = CIwSVec2::g_Zero);

	/*!
	 *	\brief	Flips the image
	 *	\returns	void
	 *	\param	pFlip	CIwSVec2 vector for flipping on X and/or Y axis.
	 *
	 *	Flips the image according the the pFlip vector. If the current Flip vector equals the passed Flip vector, image is unflipped.
	 */
	void		Flip(CIwSVec2 pFlip = CIwSVec2::g_Zero);

	/*!
	 *	\brief	Render the image.
	 *
	 *	\returns		void
	 *
	 *	\param	pPosition	(x,y) 2D integer vector
	 *
	 *	Draws the image at the given position.
	 */
	void		Render(CIwSVec2 pPosition = CIwSVec2::g_Zero);
};

#endif