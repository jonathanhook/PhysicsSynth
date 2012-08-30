/**
 * Class:	Manager
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <MultiTouchEvents/MultiTouchEventManager.h>

namespace JDHUtility { class OSCSender; }

using namespace JDHUtility;
using namespace MultiTouchEvents;

namespace PhysicsSynth
{
	class Canvas;
	class Finger;

	class Manager :
		public MultiTouchEventManager
	{
	public:
		static const float FINGER_SIZE;
		static const float WORLD_SCALE;

		static void				clearTrackId	(unsigned char deletedId);
		static Point2f			descale			(const Point2f &p);
		static float			descale			(float f);
		static Vector2f			descale			(const Vector2f &v);
		static OSCSender		*getOscSender	(void);
		static unsigned char	getTrackId		(void);
		static Point2f			scale			(const Point2f &p);
		static float			scale			(float f);
		static Vector2f			scale			(const Vector2f &v);
		static void				setOscSender	(OSCSender *sender);
		static void				setTrackId		(unsigned char toSet);

		Manager(unsigned int width, bool dispatchEvents = true);
		~Manager(void);

		void load			(void);
		void eraseAllObjects(void);
		void eraseAllWorlds	(void);
		void render			(void);
		void save			(void);
		void update			(void);
		void zoom			(float z, const Point2f &p);

	private:
		static const unsigned int	CIRCLE_SEGS;
		static const unsigned int	FRAME_SAMPLE_COUNT;
		static const unsigned int	MAX_WORLDS;
		static const unsigned int	MENU_WIDTH;
		static const float			OPACITY;
		static const std::string	SAVE_FILE;

		static OSCSender		*oscSender;
		static unsigned char	trackIds;

		Canvas								*canvas;
		unsigned int						fingerDl;
		std::map<unsigned int, Finger *>	fingers;
		unsigned int						frames;
		unsigned int						lastRender;
		unsigned int						width;

		void canvas_Saved	(void);
		void peek			(const FingerEventArgs &e);
		void renderFingers	(void);
	};
}


