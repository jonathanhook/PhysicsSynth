/**
 * Class:	ImpulseSoundEvent
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <osc/OscOutboundPacketStream.h>
#include <JDHUtility/OSCSender.h>
#include "ImpulseSoundEvent.h"
#include "Manager.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const char *ImpulseSoundEvent::PROFILE = "/psynth";

	/* Constructors */
	ImpulseSoundEvent::ImpulseSoundEvent(unsigned int worldId, unsigned int sampleId,	float transpose, float stretch, float drive, float frequency, float resonance, float decay, float pan) :
		SoundEvent(worldId, sampleId)
	{
		this->transpose	= transpose;
		this->stretch	= stretch;
		this->drive		= drive;
		this->frequency	= frequency;
		this->resonance	= resonance;
		this->decay		= decay;
		this->pan		= pan;
	}

	ImpulseSoundEvent::~ImpulseSoundEvent(void)
	{
	}

	/* Public Member Functions */
	void ImpulseSoundEvent::send(void) const
	{
		OSCSender *sender = Manager::getOscSender();
		assert(sender);

		char buffer[BUFFER_SIZE];
		osc::OutboundPacketStream p(buffer, BUFFER_SIZE);

		p << osc::BeginBundleImmediate
			<< osc::BeginMessage(PROFILE) 
				<< (int)worldId
				<< (int)sampleId 
				<< transpose
				<< stretch
				<< drive
				<< frequency
				<< resonance
				<< decay
				<< pan
			<< osc::EndMessage
        << osc::EndBundle;

		sender->send(p);
	}
}
