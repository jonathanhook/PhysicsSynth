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
#include <map>
#include "Point2f.h"

namespace JDHUtility
{
	class GLTexture;
    class GLVbo;
    
	class GLTextureFont
	{
	public:
		struct FontInfo
		{
			int id;
			int x;
			int y;
			int width;
			int height;
			int xOffset;
			int yOffset;
			int xAdvance;
		};

		GLTextureFont(const std::string &fontPath, const std::string &texturePath);
		~GLTextureFont(void);
		
		void		renderString(const std::string &text, const Point2f &position) const;
		Vector2f	queryBox	(const std::string &text) const;

		GLTexture *texture;
	
	private:
		float getSizef(int val) const;
		void parseFontInfo(const std::string &infoPath);

		int						lineHeight;
		int						base;
		int						scaleW;
		int						scaleH;
		std::map<unsigned int, FontInfo *>	info;
        GLVbo                   *vbo;
	};
}