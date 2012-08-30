/**
 * Class:	Slider
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <JDHUtility/OpenGL.h>
#include "Slider.h"

namespace PhysicsSynth
{
	/* Constructors */
	Slider::Slider(std::string label, const Point2i &position, unsigned int width) :
		LabelledUIElement(label, position, width)
	{
		sliderDl	= -1;
		sliderBarDl	= -1;
		value		= 0.0f;

		dimensions.setY(getLabelHeight() * 2);
	}

	Slider::~Slider(void)
	{
	}

	/* Public Member Functions */
	void Slider::fingerAdded(const FingerEventArgs &e)
	{
		UIElement::fingerAdded(e);
		updateValue(e);
	}

	void Slider::fingerUpdated(const FingerEventArgs &e)
	{
		UIElement::fingerUpdated(e);
		updateValue(e);
	}

	void Slider::fingerRemoved(const FingerEventArgs &e)
	{
		UIElement::fingerRemoved(e);
		updateValue(e);
	}

	float Slider::getValue(void) const
	{
		return value;
	}

	void Slider::render(void)
	{
		LabelledUIElement::render();

		float px			= getSizef(position.getX());
		float py			= getSizef(position.getY() + getLabelHeight());
		float border		= getSizef(BORDER);
		float labelHeight	= getSizef(getLabelHeight());
		float width			= getSizef(dimensions.getX());

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + border, py + border, 0.0f);
		glScalef(width - border, labelHeight - border, 1.0f);

		glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// selected region
		if(selected)
		{
			LIGHT_COLOUR.use();
		}
		else
		{
			DARK_COLOUR.use();
		}

		if(sliderDl == -1)
		{
			sliderDl = glGenLists(1);
			glNewList(sliderDl, GL_COMPILE);

			glBegin(GL_QUADS);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(1.0f, 0.0f, 0.0f);
				glVertex3f(1.0f, 1.0f, 0.0f);
				glVertex3f(0.0f, 1.0f, 0.0f);
			glEnd();

			glEndList();
		}
		glCallList(sliderDl);
		glPopMatrix();

		border		= getSizef(BORDER);
		labelHeight	= getSizef(getLabelHeight());
		width		= getSizef(dimensions.getX());

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + border, py + border, 0.0f);
		glScalef((width - border) * value, labelHeight - border, 1.0f);

		if(sliderBarDl == -1)
		{
			sliderBarDl = glGenLists(1);
			glNewList(sliderBarDl, GL_COMPILE);

			VALUE_COLOUR.use();
			glBegin(GL_QUADS);
				glVertex3f(0.0f,	0.0f,	0.0f);
				glVertex3f(1.0f,	0.0f,	0.0f);
				glVertex3f(1.0f,	1.0f,	0.0f);
				glVertex3f(0.0f,	1.0f,	0.0f);
			glEnd();

			glEndList();
		}
		glCallList(sliderBarDl);
		glPopMatrix();
		glPopAttrib(); // GL_CURRENT_BIT | GL_ENABLE_BIT
	}

	void Slider::setValue(float value)
	{
		this->value = value;
	}

	void Slider::setValueChangedCallback(ValueChangedCallback valueChanged)
	{
		this->valueChanged = valueChanged;
	}

	/* Private Member Functions */
	void Slider::updateValue(const FingerEventArgs &e)
	{
		float fingerX			= e.getPosition().getX();
		float fingerY			= e.getPosition().getY();
		float targetRegionX		= getSizef(position.getX() + BORDER);
		float targetRegionWidth	= getSizef(dimensions.getX() - (BORDER * 2));
		float tx				= (fingerX - targetRegionX) / targetRegionWidth;

		// clamp
		if(tx < 0.0f)
		{
			tx = 0.0f;
		}
		else if(tx > 1.0f)
		{
			tx = 1.0f;
		}

		bool changed = (value != tx);
		value = tx;

		if(changed && valueChanged != NULL)
		{
			valueChanged(value);
		}
	}
}
