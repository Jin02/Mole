#include "Include.h"


void StateChange()
{
	switch(Change)
	{
	case Logo:
		LogoFC();
		break;
	case Start:
		FC();
		break;
	case Menu:
		MenuFC();
		break;
	case GameStart:
		GameFC();
		break;
	case Setting:
		SetFC();
		break;
	case Info:
		InfoFC();
		break;
	case Wing:
		WingFC();
		break;	
	case Catch:
		CatchFC();
		break;
	}
}

void KeyChange(M_Int32 Key)
{
	switch(Change)
	{
	case Logo:
		LogoMenuKey(Key);
		break;
	case Start:
		MenuKey(Key);
		break;
	case Menu:
		MKey(Key);
		break;
	case GameStart:
		GameMenuKey(Key);
		break;
	case Setting:
		SetMenuKey(Key);
		break;
	case Info:
		InfoKey(Key);
		break;
	case Wing:
		PlayKey(Key);
		break;
	case Catch:
		CatchMenuKey(Key);
		break;
	}

}
void Keyoff(M_Int32 Key)
{
	if(Key == Wing)
		PlayKeyoff(Key);
}