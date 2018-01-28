#include "Include.h"

void InfoFC()
{
	switch(Check)
	{
	case Set:
		InfoState();
	break;

	case Play:
		InfoUpdate();
		InfoDraw();
	break;

	case SetEnd:
		InfoDestroy();
	break;
	}
}

void InfoState()
{
	Check=Play;
}

void InfoDraw()
{
	String("Info",10,10);
}

void InfoUpdate()
{
}

void InfoKey(M_Int32 Key)
{
	switch(Key)
	{
	case MC_KEY_CLEAR:
		Change=Menu;
		Check=Set;
		break;
	}
}

void InfoDestroy()
{
}
