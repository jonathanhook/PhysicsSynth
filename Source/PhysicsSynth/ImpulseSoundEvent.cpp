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
