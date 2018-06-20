#ifndef _IMANAGER_H_
#define _IMANAGER_H_


/************************************************************************/
/* It is a interface class for all managers in game. All the managers 
in game have to implement this interface so that their tick function will
be called every frame. Beside tick function, it has a pure virtual clean function
that every manager has to clean itself.

so if you want to add a manager to the game, only thing to do is to implement
IManager class and add the manager to scene manager. Then, scene manager will care the
rest such as updating manager every frame etc..
*/
/************************************************************************/
class IManager
{
public:
	// It is called every  frame
	virtual void tick()		= 0;
	//makes cleaning stuff
	virtual void  clean()	= 0;

};

#endif