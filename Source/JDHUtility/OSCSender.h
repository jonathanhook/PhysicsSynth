/**
 * Class:	OSCSender
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "FastDelegate.h"
#include <ip/IpEndpointName.h>
#include <ip/UdpSocket.h>
#include <osc/OscOutboundPacketStream.h>

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

