#include "Include.h"

void SetFC()
{
	switch(Check)
	{
	case Set:
		SetState();
	break;

	case Play:
		SetUpdate();
		SetDraw();
	break;

	case SetEnd:
		SetDestroy();
	break;
	}
}

void SetState()
{
	Check = Play;
}

void SetDraw()
{
	String("Setting",10,10);
}

void SetUpdate()
{
}

void SetMenuKey(M_Int32 Key)
{
	switch(Key)
	{
	case MC_KEY_CLEAR:
		Change = Menu;
		Check = Set;
		break;
	}
}

void SetDestroy()
{
}