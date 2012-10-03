/**
 * Class:	GLTextureFont
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
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