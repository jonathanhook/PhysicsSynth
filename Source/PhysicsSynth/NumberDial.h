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

#include <JDHUtility/GLTextureFont.h>
#include "LabelledUIElement.h"

using namespace JDHUtility;

namespace PhysicsSynth
{
    class NumberDial :
        public UIElement
    {
    public:
        typedef FastDelegate1<unsigned int> NumberChangedCallback;
        
        NumberDial(const Point2i &position, unsigned int width, unsigned int min, unsigned int max, unsigned int initial);
        ~NumberDial(void);
        
        bool contains(const FingerEventArgs &e) const;
        void fingerAdded(const FingerEventArgs &e);
        void fingerUpdated(const FingerEventArgs &e);
        void fingerRemoved(const FingerEventArgs &e);
        unsigned int getValue(void) const;
        void render(void);
        void setNumberChangedCallback(NumberChangedCallback numberChanged);
        void setParentPosition(const Point2i &parentPosition);
        void setValue(unsigned int value);
        
    private:
        static const unsigned int HEIGHT;
        
        unsigned int current;
        float downY;
        int downVal;
        bool hasMoved;
        float offset;
        unsigned int min;
        unsigned int max;
        NumberChangedCallback numberChanged;
        Point2i parentPosition;
    };
}