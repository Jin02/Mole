#include "Include.h"


void MenuFC()
{
	switch(Check)
	{
	case Set:
		MenuState();
	break;

	case Play:
		MenuUpdate();
		MenuDraw();
	break;

	case SetEnd:
		MenuDestroy();
	break;
	}
}

void MenuState()
{
	Check = Play;
}

void MenuDraw()
{

}

void MenuUpdate()
{
}

void MKey(M_Int32 Key)
{
	switch(Key)
	{
	case MC_KEY_1:
		Change = GameStart;
		Check = Set;
		break;

	case MC_KEY_2:
		Change = Info;
		Check = Set;
		break;

	case MC_KEY_3:
		Change = Setting;
		Check = Set;
		break;

	case MC_KEY_4:
		break;
	}
}

void MenuDestroy()
{
}
