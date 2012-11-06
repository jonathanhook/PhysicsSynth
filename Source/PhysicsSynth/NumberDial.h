//
//  NumberDial.h
//  PhysicsSynth
//
//  Created by Jonathan Hook on 05/11/2012.
//  Copyright (c) 2012 Jonathan Hook. All rights reserved.
//
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