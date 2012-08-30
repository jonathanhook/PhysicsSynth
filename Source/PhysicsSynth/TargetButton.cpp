/**
 * Class:	TargetButton
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <math.h>
#include "TargetButton.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const float			TargetButton::SNAP_THRESHOLD	= 0.05f;

	/* Constructors */
	TargetButton::TargetButton(std::string text, const Point2i &position, unsigned int width) :
		LabelledUIElement(text, position, width)
	{
		backgroundDl		= -1;	
		hLineDisplayList	= -1;
		vLineDisplayList	= -1;
	
		targetPosition.setX(0.0f);
		targetPosition.setY(0.0f);

		dimensions.setY(getLabelHeight() * 4);
	}

	TargetButton::~TargetButton(void)
	{
	}

	/* Public Member Functions */
	void TargetButton::fingerAdded(const FingerEventArgs &e)
	{
		LabelledUIElement::fingerAdded(e);
		updateTargetPosition(e);
	}
	
	void TargetButton::fingerUpdated(const FingerEventArgs &e)
	{
		LabelledUIElement::fingerUpdated(e);
		updateTargetPosition(e);
	}
	
	void TargetButton::fingerRemoved(const FingerEventArgs &e)
	{
		LabelledUIElement::fingerRemoved(e);
		updateTargetPosition(e);
	}

	const Vector2f &TargetButton::getTargetPosition(void) const
	{
		return targetPosition;
	}

	void TargetButton::render(void)
	{
		LabelledUIElement::render();

		float width		= getSizef(dimensions.getX() - (BORDER));
		float height	= getSizef(dimensions.getY() - (BORDER) - getLabelHeight());
		float px		= getSizef(position.getX() + BORDER);
		float py		= getSizef(position.getY() + BORDER + getLabelHeight());

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px, py, 0.0f);
		glScalef(width, height, 1.0f);

		if(backgroundDl == -1)
		{
			backgroundDl = glGenLists(1);
			glNewList(backgroundDl, GL_COMPILE);

			glPushAttrib(GL_LINE_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			DARK_COLOUR.use();
			glBegin(GL_QUADS);
				glVertex3f(0.0f,	0.0f,	0.0f);
				glVertex3f(1.0f,	0.0f,	0.0f);
				glVertex3f(1.0f,	1.0f,	0.0f);
				glVertex3f(0.0f,	1.0f,	0.0f);
			glEnd();

			glPopAttrib();
			glEndList();
		}
		glCallList(backgroundDl);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(0.0f, (targetPosition.getY() / 2.0f) + 0.5f, 0.0f);

		if(hLineDisplayList == -1)
		{
			hLineDisplayList = glGenLists(1);
			glNewList(hLineDisplayList, GL_COMPILE);

			glPushAttrib(GL_LINE_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glLineWidth(1.0f);
			VALUE_COLOUR.use();

			glBegin(GL_LINES);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(1.0f, 0.0f, 0.0f);
			glEnd();

			glPopAttrib(); // GL_LINE_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT
			glEndList();
		}
		glCallList(hLineDisplayList);
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef((targetPosition.getX() / 2.0f) + 0.5f, 0.0f, 0.0f);

		if(vLineDisplayList == -1)
		{
			vLineDisplayList = glGenLists(1);
			glNewList(vLineDisplayList, GL_COMPILE);

			glPushAttrib(GL_LINE_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glLineWidth(1.0f);
			VALUE_COLOUR.use();

			glBegin(GL_LINES);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, 1.0f, 0.0f);
			glEnd();

			glPopAttrib(); // GL_LINE_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT
			glEndList();
		}
		glCallList(vLineDisplayList);
		glPopMatrix();
		glPopMatrix();
	}

	void TargetButton::setTargetChangedCallback(TargetChangedCallback targetChanged)
	{
		this->targetChanged = targetChanged;
	}

	void TargetButton::setTargetPosition(const Vector2f &targetPosition)
	{
		this->targetPosition = targetPosition;
	}

	/* Private Member Functions */
	void TargetButton::updateTargetPosition(const FingerEventArgs &e)
	{
		float fingerX				= e.getPosition().getX();
		float fingerY				= e.getPosition().getY();
		float targetRegionX			= getSizef(position.getX());
		float targetRegionY			= getSizef(position.getY() + getLabelHeight());
		float targetRegionWidth		= getSizef(dimensions.getX() / 2);
		float targetRegionHeight	= getSizef((dimensions.getY() - getLabelHeight()) / 2);
		float tx					= ((fingerX - targetRegionX) / targetRegionWidth) - 1.0f;
		float ty					= ((fingerY - targetRegionY) / targetRegionHeight) - 1.0f;

		// clamp
		if(tx > 1.0f)
		{
			tx = 1.0f;
		}
		else if(tx < -1.0f)
		{
			tx = -1.0f;
		}

		if(ty > 1.0f)
		{
			ty = 1.0f;
		}
		else if(ty < -1.0f)
		{
			ty = -1.0f;
		}

		// snap to centre
		if(fabs(tx) < SNAP_THRESHOLD)
		{
			tx = 0.0f; 
		}

		if(fabs(ty) < SNAP_THRESHOLD)
		{
			ty = 0.0f;
		}

		bool changed = (targetPosition.getX() != tx) || (targetPosition.getY() != ty);

		targetPosition.setX(tx);
		targetPosition.setY(ty);

		if(changed && targetChanged != NULL)
		{
			targetChanged(targetPosition);
		}
	}
}
