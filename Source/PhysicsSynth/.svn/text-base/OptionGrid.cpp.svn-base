/**
 * Class:	OptionGrid
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/Ndelete.h>
#include "OptionGrid.h"
#include "OptionGridItem.h"

namespace PhysicsSynth
{
	/* Private Member FUnctions */
	const unsigned int OptionGrid::COLUMNS = 2;

	/* Constructors */
	OptionGrid::OptionGrid(std::vector<Option> items, std::string label, const Point2i &position, unsigned int width) :
		LabelledUIElement(label, position, width)
	{
		init(items);
	}

	OptionGrid::~OptionGrid(void)
	{
		for(unsigned int i = 0; i < options.size(); i++)
		{
			NDELETE(options[i]);
		}
		options.clear();
	}

	/* Public Member Functions */
	const OptionGridItem &OptionGrid::getSelectedItem(void) const
	{
		for(unsigned int i = 0; i < options.size(); i++)
		{
			OptionGridItem *item = options[i];
			assert(item);

			if(item->isChecked())
			{
				return *item;
			}
		}

		return *(OptionGridItem *)NULL;
	}

	void OptionGrid::render(void)
	{
		LabelledUIElement::render();

		for(unsigned int i = 0; i < options.size(); i++)
		{
			OptionGridItem *o = options[i];
			assert(o);

			o->render();
		}
	}

	void OptionGrid::setPosition(const Point2i &position)
	{
		int tx = position.getX() - this->position.getX();
		int ty = position.getY() - this->position.getY();

		this->position = position;

		// update children
		for(unsigned int i = 0; i < options.size(); i++)
		{
			OptionGridItem *item = options[i];
			assert(item);

			Point2i itemPos = item->getPosition();
			itemPos.translateX(tx);
			itemPos.translateY(ty);

			item->setPosition(itemPos);
		}
	}

	void OptionGrid::setSelectedItem(OptionGridItem *selectedItem)
	{
		selectedItem->setChecked(true);

		for(unsigned int i = 0; i < options.size(); i++)
		{
			OptionGridItem *other = options[i];
			assert(other);

			if(selectedItem != other)
			{
				other->setChecked(false);
			}
		}
	}

	void OptionGrid::setSelectedItem(unsigned int id)
	{
		OptionGridItem *item = NULL;
		for(unsigned int i = 0; i < options.size(); i++)
		{
			OptionGridItem *other = options[i];
			assert(other);

			if(other->getOption().id == id)
			{
				item = other;
			}
		}

		if(item != NULL)
		{
			setSelectedItem(item);
		}
	}

	void OptionGrid::setSelectionChangedCallback(SelectionChangedCallback selectionChanged)
	{
		this->selectionChanged = selectionChanged;
	}

	/* Private Member Functions */
	void OptionGrid::init(std::vector<Option> items)
	{
		unsigned int	width			= dimensions.getX() / COLUMNS;
		unsigned int	height			= getLabelHeight();
		Point2i			itemDimensions	= Point2i(width, height);

		unsigned int size = items.size();
		for(unsigned int i = 0; i < size; i++)
		{
			Option item = items[i];
		
			unsigned int column	= i % COLUMNS;
			unsigned int row	= i / COLUMNS;
			
			Point2i itemPos(width * column, height * row);
			itemPos.translateY(height);
			itemPos.translate(position.getX(), position.getY());
			
			OptionGridItem *ogi = new OptionGridItem(item, itemPos, itemDimensions);
			ogi->setCheckedCallback(MakeDelegate(this, &OptionGrid::optionGridItem_Checked));

			options.push_back(ogi);
			registerEventHandler(ogi);
		}
		
		dimensions.setY((height * (size / COLUMNS)) + height);
	}

	void OptionGrid::optionGridItem_Checked(OptionGridItem *option)
	{
		setSelectedItem(option);

		if(selectionChanged != NULL)
		{
			selectionChanged(option->getOption());
		}
	}
}
