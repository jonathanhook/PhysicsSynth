/**
 * Class:	GLFontManager
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once

#include <string>
#include "Point2f.h"
#include "Vector2f.h"
#include "Singleton.h"

namespace JDHUtility
{
	class GLTextureFont;

	class GLFontManager :
		public Singleton
	{
	public:
        enum Font { LARGE, MEDIUM, SMALL };

		static GLFontManager *getInstance(void);
		
		void		renderString	(Font font, const std::string &text, const Point2f &position) const;
		Vector2f	queryBox		(Font font, const std::string &text) const;	

	private:
		static const std::string LARGE_FONT;
		static const std::string MEDIUM_FONT;
		static const std::string SMALL_FONT;
		static const std::string LARGE_TEX;
		static const std::string MEDIUM_TEX;
		static const std::string SMALL_TEX;
		
		GLFontManager(void);
		~GLFontManager(void);

		GLTextureFont *large;
		GLTextureFont *medium;
		GLTextureFont *sml;
	};
}

