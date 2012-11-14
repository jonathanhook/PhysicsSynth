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
#pragma once

#include <string>
#include "Point2f.h"
#include "Vector2f.h"

namespace JDHUtility
{
	class GLTextureFont;

	class GLFontManager
	{
	public:
        enum Font { LARGE, MEDIUM, SMALL };
        
        static const std::string LARGE_FONT;
		static const std::string MEDIUM_FONT;
		static const std::string SMALL_FONT;
		static const std::string LARGE_TEX;
		static const std::string MEDIUM_TEX;
		static const std::string SMALL_TEX;

		static GLFontManager *getInstance(void);
		
		void		renderString	(Font font, const std::string &text, const Point2f &position) const;
		Vector2f	queryBox		(Font font, const std::string &text) const;	

	private:
        static GLFontManager *instance;
        
		GLFontManager(void);
		~GLFontManager(void);

		GLTextureFont *large;
		GLTextureFont *medium;
		GLTextureFont *sml;
	};
}

