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
#include <iostream>
#include <fstream>
#include <sstream>
#include "FileLocationUtility.h"
#include "WindowingUtils.h"
#include "Ndelete.h"
#include "GLTexture.h"
#include "GLTextureFont.h"
#include "GLVbo.h"

namespace JDHUtility
{
	GLTextureFont::GLTextureFont(const std::string &fontPath, const std::string &texturePath)
	{
		texture = new GLTexture(texturePath);
        
        std::string resourcePath = FileLocationUtility::getFileInResourcePath(fontPath);   
		parseFontInfo(resourcePath);
        
        GLfloat verts[12] =
        {
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f
        };
        vbo = new GLVbo(GL_TRIANGLE_STRIP, GL_DYNAMIC_DRAW, verts, 4);
        
	}

	GLTextureFont::~GLTextureFont(void)
	{
		for(std::map<unsigned int, FontInfo *>::iterator it = info.begin(); it != info.end(); it++)
		{
			NDELETE((*it).second);
		}
		info.clear();

		NDELETE(texture);
	}

	void GLTextureFont::renderString(const std::string &text, const Point2f &position) const
	{
		if(texture->isTexture())
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			texture->bind();

			float cx = position.getX();
			float cy = position.getY();
			
			for(unsigned int i = 0; i < text.size(); i++)
			{
				char letter = text[i];

				std::map<unsigned int, FontInfo *>::const_iterator it = info.find(letter);
				if (it != info.end())
				{
					FontInfo *f = it->second;

					float u0 = (float)f->x / (float)scaleW;
					float v0 = 1.0f - ((float)f->y / (float)scaleH);
					float u1 = (float)(f->x + f->width) / (float)scaleW;
					float v1 = 1.0f - ((float)(f->y + f->height) / (float)scaleH);

					float w		= getSizef(f->width);
					float h		= getSizef(f->height);
					float ox	= getSizef(f->xOffset);
					float oy	= getSizef(f->yOffset);

					glMatrixMode(GL_MODELVIEW);
					glPushMatrix();
					glTranslatef(cx + ox, cy + oy, 0.0f);
					glScalef(w, h, 1.0f);
					
                    GLfloat uvs[8] =
                    {
                        u0, v0,
                        u0, v1,
                        u1, v0,
                        u1, v1
                    };
                    
                    // TODO: this is inefficient
                    vbo->update(GL_TRIANGLE_STRIP, GL_DYNAMIC_DRAW, NULL, 4, uvs);
                    vbo->render();
      
					glPopMatrix();

					cx += getSizef(f->xAdvance);
				}
			}
            
            texture->unbind();
            glDisable(GL_BLEND);
		}
	}

	Vector2f GLTextureFont::queryBox(const std::string &text) const
	{
		float width = 0.0f;
		float height = 0.0f;

		for(unsigned int i = 0; i < text.size(); i++)
		{
			char letter = text[i];

			std::map<unsigned int, FontInfo *>::const_iterator it = info.find(letter);
			if (it != info.end())
			{
				FontInfo *f = it->second;
				assert(f);
				
				width += getSizef(f->xAdvance);
	
				float h = getSizef(f->height + f->yOffset);
				if(h > height)
				{
					height = h;
				}
			}
		}

		return Vector2f(width, height);
	}

	float GLTextureFont::getSizef(int val) const
	{
		float w = WindowingUtils::getWindowDimensions().getX();
		return (float)val / w;
	}

	void GLTextureFont::parseFontInfo(const std::string &infoPath)
	{
		std::ifstream f;
		f.open (infoPath.c_str(), std::ios::in);
		
		if (f.is_open())
		{
			while (f.good())
			{
				std::string line, read, key, value;
				std::stringstream lineStream;
				std::size_t i;

				std::getline(f, line);
				lineStream << line;
				lineStream >> read;

				if(read == "common")
				{
					while(!lineStream.eof())
					{
						lineStream >> read;
						i = read.find('=');

						key = read.substr(0, i);
						value = read.substr(i + 1);

						std::stringstream converter;
						converter << value;
						if(key == "lineHeight")
						{
							converter >> lineHeight;
						}
						else if(key == "base")
						{
							converter >> base;
						}
						else if(key == "scaleW")
						{
							converter >> scaleW;
						}
						else if(key == "scaleH")
						{
							converter >> scaleH;
						}
					}
				}
				else if(read == "char")
				{	
					FontInfo *fi = new FontInfo;

					while(!lineStream.eof())
					{
						lineStream >> read;
						i = read.find('=');

						key = read.substr(0, i);
						value = read.substr(i + 1);

						std::stringstream converter;
						converter << value;
						if(key == "id")
						{
							converter >> fi->id;
						}
						else if(key == "x")
						{
							converter >> fi->x;
						}
						else if(key == "y")
						{
							converter >> fi->y;
						}
						else if(key == "width")
						{
							converter >> fi->width;
						}
						else if(key == "height")
						{
							converter >> fi->height;
						}
						else if(key == "xoffset")
						{
							converter >> fi->xOffset;
						}
						else if(key == "yoffset")
						{
							converter >> fi->yOffset;
						}
						else if(key == "xadvance")
						{
							converter >> fi->xAdvance;
						}
					}

					info[fi->id] = fi;
				}
			}	
			f.close();
		}
	}
}