//
//  AddressPicker.h
//  PhysicsSynth
//
//  Created by Jonathan Hook on 06/11/2012.
//  Copyright (c) 2012 Jonathan Hook. All rights reserved.
//
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