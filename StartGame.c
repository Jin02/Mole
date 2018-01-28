#include "Include.h"


void GameFC()
{
	switch(Check)
	{
	case Set:
		GameState();
	break;

	case Play:
		GameUpdate();
		GameDraw();
	break;

	case SetEnd:
		GameDestroy();
	break;
	}
}

void GameState()
{
	Check = Play;
}

void GameDraw()
{
	String("Game Select",10,10);
}

void GameUpdate()
{
}

void GameMenuKey(M_Int32 Key)
{
	switch(Key)
	{
	case MC_KEY_CLEAR:
		Change=Menu;
		Check=Set;
		break;
	case MC_KEY_1:
		Change=Wing;
		Check=Set;
		break;
	case MC_KEY_2:
		Change=Catch;
		Check=Set;		
		break;
	}
}

void GameDestroy()
{
}

void fm_Init()
{
}