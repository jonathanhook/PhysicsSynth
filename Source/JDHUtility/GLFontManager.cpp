/**
 * This file is part of PhysicsSynth.
 *
 * Created by Jonathan Hook (jonathan.hook@ncl.ac.uk)
 * Copyright (c) 2010-2012 Jonathan Hook. All rights reserved.
 *
 * PhysicsSynth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PhysicsSynth is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PhysicsSynth.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <assert.h>
#include "GLTextureFont.h"
#include "GLFontManager.h"
#include "Ndelete.h"

namespace JDHUtility
{
    GLFontManager *GLFontManager::instance = NULL;
    
	const std::string GLFontManager::LARGE_FONT		= "courier20.fnt";
	const std::string GLFontManager::MEDIUM_FONT	= "courier18.fnt";
	const std::string GLFontManager::SMALL_FONT		= "courier18.fnt";
	const std::string GLFontManager::LARGE_TEX		= "courier20_0.tga";
	const std::string GLFontManager::MEDIUM_TEX		= "courier18_0.tga";
	const std::string GLFontManager::SMALL_TEX		= "courier18_0.tga";

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
