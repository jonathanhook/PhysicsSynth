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
        assert(transmitSocket);
        transmitSocket->Send(p.Data(), p.Size());
	}
    
    void OSCSender::setAddressChangedCallback(AddressChangedCallback addressChanged)
    {
        this->addressChanged = addressChanged;
    }
    
    void OSCSender::setIsEnabled(bool isEnabled)
    {
        this->isEnabled = isEnabled;
        
        if(!isEnabled)
        {
            setDestination(127, 0, 0, 1, 3334);
        }
        else
        {
            setDestination(addressA, addressB, addressC, addressD, port);
        }
    }
    
    void OSCSender::setDestination(int addressA, int addressB, int addressC, int addressD, int port)
    {
        if(addressA != 127 &&
           addressB != 0 &&
           addressC != 0 &&
           addressD != 1 &&
           port != 3334)
        {
            this->addressA = addressA;
            this->addressB = addressB;
            this->addressC = addressC;
            this->addressD = addressD;
            this->port = port;
        }
        
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