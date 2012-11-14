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
#include "FastDelegate.h"
#include <ip/IpEndpointName.h>
#include <ip/UdpSocket.h>
#include <osc/OscOutboundPacketStream.h>
#include <JDHUtility/OpenGL.h>

using namespace fastdelegate;

namespace JDHUtility
{
	class OSCSender
	{
	public:
        typedef FastDelegate0<> AddressChangedCallback;

		OSCSender	(int addressA, int addressB, int addressC, int addressD, int port, bool isEnabled = true);
		~OSCSender	(void);

        int getAddressA(void) const;
        int getAddressB(void) const;
        int getAddressC(void) const;
        int getAddressD(void) const;
        bool getIsEnabled(void) const;
        int getPort(void) const;
		void send(osc::OutboundPacketStream p) const;
        void setAddressChangedCallback(AddressChangedCallback addressChanged);
        void setDestination(int addressA, int addressB, int addressC, int addressD, int port);
        void setIsEnabled(bool isEnabled);
        
	private:
        AddressChangedCallback addressChanged;
        int addressA;
        int addressB;
        int addressC;
        int addressD;
        bool isEnabled;
        int port;
		UdpTransmitSocket *transmitSocket;
	};
}

