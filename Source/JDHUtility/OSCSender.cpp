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
#include <iostream.h>
#include <JDHUtility/FileLocationUtility.h>
#include "Ndelete.h"
#include "OSCSender.h"

namespace JDHUtility
{
	/* Constructors */
	OSCSender::OSCSender(int addressA, int addressB, int addressC, int addressD, int port, bool isEnabled)
	{
        this->isEnabled = isEnabled;
        
        addressChanged = NULL;
        transmitSocket = NULL;
		
        setDestination(addressA, addressB, addressC, addressD, port);
	}

	OSCSender::~OSCSender(void)
	{
		NDELETE(transmitSocket);
	}

	/* Public Member Functions */
    int OSCSender::getAddressA(void) const
    {
        return addressA;
    }
    
    int OSCSender::getAddressB(void) const
    {
        return addressB;
    }
    
    int OSCSender::getAddressC(void) const
    {
        return addressC;
    }
    
    int OSCSender::getAddressD(void) const
    {
        return addressD;
    }
    
    
    bool OSCSender::getIsEnabled(void) const
    {
        return isEnabled;
    }
    
    
    int OSCSender::getPort(void) const
    {
        return port;
    }
	
    void OSCSender::send(osc::OutboundPacketStream p) const
	{
        if(isEnabled)
        {
            assert(transmitSocket);
            transmitSocket->Send(p.Data(), p.Size());
        }
	}
    
    void OSCSender::setAddressChangedCallback(AddressChangedCallback addressChanged)
    {
        this->addressChanged = addressChanged;
    }

    void OSCSender::setIsEnabled(bool isEnabled)
    {
        this->isEnabled = isEnabled;
    }
    
    void OSCSender::setDestination(int addressA, int addressB, int addressC, int addressD, int port)
    {
        this->addressA = addressA;
        this->addressB = addressB;
        this->addressC = addressC;
        this->addressD = addressD;
        this->port = port;
        
        UdpTransmitSocket *oldSocket = transmitSocket;
        transmitSocket = new UdpTransmitSocket(IpEndpointName(addressA, addressB, addressC, addressD, port));
        
        if(oldSocket != NULL)
        {
            NDELETE(oldSocket);
        }
        
        if(addressChanged != NULL)
        {
            addressChanged();
        }
    }
}