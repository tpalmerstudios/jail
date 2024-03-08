#include <string>

#ifndef ACTOR_H
#define ACTOR_H


typedef enum
{
	ALIVE,		// I think therefore I am.
	DEAD,		// Well, that's it. The end of life.
	RESPAWN		// Pulling a Jesus Christ.
} PlayerState;

class Actor
{
	private:
		unsigned short int uniqueID;	// Runtime ID - Constructor order
		unsigned short int typeID;		// A static type database
		unsigned short int faction;		// A static faction enum
		unsigned short int flags;		// Flags that can be flipped
		/******************************************************************
		 * Preliminary Flags
		 * 	0000 0000 0000 0000
		 * 	^ Bit 0xF Determines Friendliness (0 for Friendly)
		 * 	 ^ Bit 0xE Determines Aggressive (0 for Neutral)
		 * 	  ^ Bit 0xD Determines Alien (0 for Human)
		 * 	   ^ Bit 0xC Determines Stationary (0 for Mobile)
		 * 	     ^ Bit 0xB Determines Invisible (1 for Visible)
		 * 	      ^ Bit 0xA Determines AI (1 for AI)
		 * 	       ^ Bit 0x9 Determines Report (1 for Report)
		 * 	        ^ Bit 0x8 Determines Monitoring (0 for Monitor)
		 * ****************************************************************/
		float x, y, z;			// Player Positioning
		float walkSpeed, runSpeed;		// Movement Speed (0-10)
		// Speed should be used as meters per second. 
		unsigned short int health;
		// Add Inventory class as a sub class of Actor
		// Add Appearance class as a sub Class of Inventory
		int fov = 90;					// 1-180
		unsigned short int angle;		// 0-359
		float height, width, depth;		// Dimensions >= 0
		std::string name;				// Character Title (64 chars)
		std::string description;		// A tagline (512 chars)
		PlayerState state;				// Alive, dead, respawn enum

	public:
};
class Object
{
	private:
		float x, y, z;
		float height, width, depth;
		unsigned short int angle;
		unsigned short int runtimeID;
		unsigned short int typeID;
	public:
};
class Holdable : private Object
{
     private:
     public:
		 // void pickup ();
		 // Holdable ();
		 // ~Holdable ();
};
class Inventory : private Holdable
{
     private:
     public:
};

#endif // ACTOR_H
