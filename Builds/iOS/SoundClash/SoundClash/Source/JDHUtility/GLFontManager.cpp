/**
 * Class:	GLFontManager
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include "GLTextureFont.h"
#include "GLFontManager.h"
#include "Ndelete.h"

namespace JDHUtility
{
	const std::string GLFontManager::LARGE_FONT		= "../../../Data/Fonts/courier20.fnt";
	const std::string GLFontManager::MEDIUM_FONT	= "../../../Data/Fonts/courier18.fnt";
	const std::string GLFontManager::SMALL_FONT		= "../../../Data/Fonts/courier18.fnt";
	const std::string GLFontManager::LARGE_TEX		= "../../../Data/Fonts/courier20_0.tga";
	const std::string GLFontManager::MEDIUM_TEX		= "../../../Data/Fonts/courier18_0.tga";
	const std::string GLFontManager::SMALL_TEX		= "../../../Data/Fonts/courier18_0.tga";

	/* Private Constructors */
	GLFontManager::GLFontManager(void)
	{
		large	= new GLTextureFont(LARGE_FONT, LARGE_TEX);
		medium	= new GLTextureFont(MEDIUM_FONT, MEDIUM_TEX);
		sml	= new GLTextureFont(SMALL_FONT, SMALL_TEX);
	}
	
	GLFontManager::~GLFontManager(void)
	{
		NDELETE(large);
		NDELETE(medium);
		NDELETE(sml);
	}

	/* Public Static Functions */
	GLFontManager *GLFontManager::getInstance(void)
	{
		if(instance == NULL)
		{
			instance = new GLFontManager();
		}

		return (GLFontManager *)instance;
	}

	/* Public Member Functions */
	void GLFontManager::renderString(Font font, const std::string &text, const Point2f &position) const
	{
		GLTextureFont *f = NULL;

		switch(font)
		{
			case Font::LARGE:
				f = large;
				break;
			case Font::MEDIUM:
				f = medium;
				break;
			case Font::SMALL:
				f = sml;
				break;
		}

		assert(f);
		f->renderString(text, position);
	}

	Vector2f GLFontManager::queryBox(Font font, const std::string &text) const
	{
		GLTextureFont *f = NULL;

		switch(font)
		{
			case Font::LARGE:
				f = large;
				break;
			case Font::MEDIUM:
				f = medium;
				break;
			case Font::SMALL:
				f = sml;
				break;
		}

		assert(f);
		return f->queryBox(text);
	}
}
