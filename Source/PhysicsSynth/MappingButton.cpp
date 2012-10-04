/**
 * Class:	MappingButton
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/Ndelete.h>
#include <JDHUtility/Vector2f.h>
#include <JDHUtility/GLFontManager.h>
#include <JDHUtility/GLPrimitives.h>
#include "MappingButton.h"
#include "PushButton.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const std::string MappingButton::LEFT_TEXTURE_PATH	= "../../../Data/Textures/MappingButton/left.tga";
	const std::string MappingButton::RIGHT_TEXTURE_PATH	= "../../../Data/Textures/MappingButton/right.tga";

	/* Constructors */
	MappingButton::MappingButton(MappingGrid::MappingGridItem from, std::vector<MappingGrid::MappingGridItem> options, const Point2i &position, const Point2i &dimensions) :
		UIElement(position, dimensions)
	{
		assert(options.size() > 0);

		this->from		= from;
		this->options	= options;

		mappingChanged	= NULL;
		to				= options[0];
		toId			= 0;

		initButtons();
	}

	MappingButton::~MappingButton(void)
	{
		NDELETE(leftButton);
		NDELETE(rightButton);
	}

	/* Public Member Functions */
	MappingGrid::MappingGridItem MappingButton::getFrom(void) const
	{
		return from;
	}

	MappingGrid::MappingGridItem MappingButton::getTo(void) const
	{
		return to;
	}

	void MappingButton::render(void)
	{
		float px		= getSizef(position.getX());
		float py		= getSizef(position.getY());
		float buttonDim	= getSizef(getLabelHeight() * 2);
		float border	= getSizef(BORDER);
		float width		= getSizef(dimensions.getX()) - (buttonDim * 2.0f) - border;
		float height	= getSizef(dimensions.getY() / 2);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + buttonDim + border, py + border, 0.0f);
		glScalef(width, height - border, 1.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        LIGHT_COLOUR.use();
        GLPrimitives::getInstance()->renderSquare();

		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + buttonDim, py, 0.0f);

		GLFontManager *f = GLFontManager::getInstance();
		assert(f);

		f->renderString(GLFontManager::MEDIUM, from.label, Point2f(border * 6.0f, border * 3.0f));
		f->renderString(GLFontManager::MEDIUM, to.label, Point2f(border * 6.0f, height + (border * 3.0f)));

		glPopMatrix();

		// render buttons
		assert(leftButton);
		assert(rightButton);

		leftButton->render();
		rightButton->render();
	}

	void MappingButton::setMappingChangedCallback(MappingChangedCallback mappingChanged)
	{
		this->mappingChanged = mappingChanged;
	}

	void MappingButton::setTo(MappingGrid::MappingGridItem to)
	{
		this->to = to;
	}

	/* Pirvate Member Functions */
	void MappingButton::initButtons(void)
	{
		unsigned int d = getLabelHeight() * 2;
		Point2i dim(d, d);

		leftButton = new PushButton(LEFT_TEXTURE_PATH, position, dim);
		leftButton->setClickedCallback(MakeDelegate(this, &MappingButton::leftButton_Clicked));
		registerEventHandler(leftButton);

		Point2i rPos(position.getX() + (dimensions.getX() - d), position.getY());
		rightButton = new PushButton(RIGHT_TEXTURE_PATH, rPos, dim);
		rightButton->setClickedCallback(MakeDelegate(this, &MappingButton::rightButton_Clicked));
		registerEventHandler(rightButton);
	}

	void MappingButton::leftButton_Clicked	(UIElement *sender)
	{
		to = options[(--toId) % options.size()];

		if(mappingChanged != NULL)
		{
			mappingChanged(from, to);
		}
	}

	void MappingButton::rightButton_Clicked(UIElement *sender)
	{
		to = options[(++toId) % options.size()];

		if(mappingChanged != NULL)
		{
			mappingChanged(from, to);
		}
	}
}