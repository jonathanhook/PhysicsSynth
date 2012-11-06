//
//  AddressPicker.cpp
//  PhysicsSynth
//
//  Created by Jonathan Hook on 06/11/2012.
//  Copyright (c) 2012 Jonathan Hook. All rights reserved.
//
#include <assert.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/OSCSender.h>
#include <JDHUtility/Ndelete.h>
#include "AddressPicker.h"
#include "LabelledUIElement.h"
#include "NumberDial.h"
#include "Manager.h"

namespace PhysicsSynth
{
    /* Public Constructors */
    AddressPicker::AddressPicker(std::string label, const Point2i &position, unsigned int width) :
        LabelledUIElement(label, position, width)
    {
        OSCSender *sender = Manager::getOscSender();
        assert(sender);
        sender->setAddressChangedCallback(MakeDelegate(this, &AddressPicker::sender_AddressChanged));
        
        initialised = false;
        
        initDials();
    }
    
    AddressPicker::~AddressPicker(void)
    {
        NDELETE(addressA);
        NDELETE(addressB);
        NDELETE(addressC);
        NDELETE(addressD);
        NDELETE(port);
    }
    
    /* Public Functions */
    bool AddressPicker::contains(const FingerEventArgs &e) const
    {
        return false;
    }
    
    void AddressPicker::render(void)
    {
        LabelledUIElement::render();
        
        float px = getSizef(position.getX());
        float py = getSizef(position.getY());
        
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(px, py, 0.0f);
        
        addressA->render();
        addressB->render();
        addressC->render();
        addressD->render();
        port->render();
        
        glPopMatrix();
    }
    
    void AddressPicker::setPosition(const Point2i &position)
    {
        UIElement::setPosition(position);
     
        addressA->setParentPosition(position);
        addressB->setParentPosition(position);
        addressC->setParentPosition(position);
        addressD->setParentPosition(position);
        port->setParentPosition(position);
    }
    
    /* Private Functions */
    void AddressPicker::initDials(void)
    {
        OSCSender *sender = Manager::getOscSender();
        assert(sender);
        
        unsigned int a = sender->getAddressA();
        unsigned int b = sender->getAddressB();
        unsigned int c = sender->getAddressC();
        unsigned int d = sender->getAddressD();
        unsigned int p = sender->getPort();
        
        unsigned int width = dimensions.getX();
        unsigned int charWidth = (width - (BORDER * 6)) / 16;
        unsigned int ipWidth = charWidth * 3;
        unsigned int portWidth = width -  ((ipWidth * 4) + (BORDER * 5));
        
        Point2i pos = Point2i(0.0f, 0.0f);
        pos.translateY(getLabelHeight());
        pos.translateX(BORDER);
        
        addressA = new NumberDial(pos, ipWidth, 0, 255, a);
        addressA->setNumberChangedCallback(MakeDelegate(this, &AddressPicker::dial_ValueChanged));
        registerEventHandler(addressA);
        pos.translateX(BORDER + ipWidth);
        
        addressB = new NumberDial(pos, ipWidth, 0, 255, b);
        addressB->setNumberChangedCallback(MakeDelegate(this, &AddressPicker::dial_ValueChanged));
        registerEventHandler(addressB);
        pos.translateX(BORDER + ipWidth);
        
        addressC = new NumberDial(pos, ipWidth, 0, 255, c);
        addressC->setNumberChangedCallback(MakeDelegate(this, &AddressPicker::dial_ValueChanged));
        registerEventHandler(addressC);
        pos.translateX(BORDER + ipWidth);
        
        addressD = new NumberDial(pos, ipWidth, 0, 255, d);
        addressD->setNumberChangedCallback(MakeDelegate(this, &AddressPicker::dial_ValueChanged));
        registerEventHandler(addressD);
        pos.translateX(BORDER + ipWidth);
        
        port = new NumberDial(pos, portWidth, 0, 9999, p);
        port->setNumberChangedCallback(MakeDelegate(this, &AddressPicker::dial_ValueChanged));
        registerEventHandler(port);
        
        dimensions.translateY(getLabelHeight());
        dimensions.translateY(addressA->getDimensions().getY());
    }

    void AddressPicker::dial_ValueChanged(unsigned int value)
    {
        unsigned int a = addressA->getValue();
        unsigned int b = addressB->getValue();
        unsigned int c = addressC->getValue();
        unsigned int d = addressD->getValue();
        unsigned int p = port->getValue();
        
        OSCSender *sender = Manager::getOscSender();
        assert(sender);
        
        sender->setDestination(a, b, c, d, p);
    }
    
    void AddressPicker::sender_AddressChanged(void)
    {
        if(!initialised)
        {
            OSCSender *sender = Manager::getOscSender();
            assert(sender);
        
            unsigned int a = sender->getAddressA();
            unsigned int b = sender->getAddressB();
            unsigned int c = sender->getAddressC();
            unsigned int d = sender->getAddressD();
            unsigned int p = sender->getPort();
        
            addressA->setValue(a);
            addressB->setValue(b);
            addressC->setValue(c);
            addressD->setValue(d);
            port->setValue(p);
            
            initialised = true;
        }
    }
}