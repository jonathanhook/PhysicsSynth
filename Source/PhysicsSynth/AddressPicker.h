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
#include "LabelledUIElement.h"

namespace PhysicsSynth
{
    class NumberDial;
    
    class AddressPicker :
        public LabelledUIElement
    {
    public:
        AddressPicker(std::string label, const Point2i &position, unsigned int width);
        ~AddressPicker(void);
        
        bool contains(const FingerEventArgs &e) const;
        void render(void);
        void setPosition(const Point2i &position);
        
    private:
        NumberDial *addressA;
        NumberDial *addressB;
        NumberDial *addressC;
        NumberDial *addressD;
        NumberDial *port;
        bool initialised;
        
        void initDials(void);
        void dial_ValueChanged(unsigned int value);
        void sender_AddressChanged(void);
    };
}