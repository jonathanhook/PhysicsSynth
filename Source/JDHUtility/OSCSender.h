/**
 * Class:	OSCSender
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <ip/IpEndpointName.h>
#include <ip/UdpSocket.h>
#include <osc/OscOutboundPacketStream.h>

namespace JDHUtility
{
	class OSCSender
	{
	public:
		OSCSender	(int addressA, int addressB, int addressC, int addressD, int port);
		~OSCSender	(void);

		void send(osc::OutboundPacketStream p) const;
        void setDestination(int addressA, int addressB, int addressC, int addressD, int port);
        
	private:
		UdpTransmitSocket	*transmitSocket;
	};
}

