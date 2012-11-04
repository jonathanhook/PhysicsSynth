/**
 * Class:	OSCSender
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include "Ndelete.h"
#include "OSCSender.h"

namespace JDHUtility
{
	/* Constructors */
	OSCSender::OSCSender(int addressA, int addressB, int addressC, int addressD, int port)
	{
        transmitSocket = NULL;
		setDestination(addressA, addressB, addressC, addressD, port);
	}

	OSCSender::~OSCSender(void)
	{
		NDELETE(transmitSocket);
	}

	/* Public Member Functions */
	void OSCSender::send(osc::OutboundPacketStream p) const
	{
		assert(transmitSocket);
		transmitSocket->Send(p.Data(), p.Size());
	}
    
    void OSCSender::setDestination(int addressA, int addressB, int addressC, int addressD, int port)
    {
        UdpTransmitSocket *oldSocket = transmitSocket;
        transmitSocket = new UdpTransmitSocket(IpEndpointName(addressA, addressB, addressC, addressD, port));
        
        if(oldSocket != NULL)
        {
            NDELETE(oldSocket);
        }
    }
}