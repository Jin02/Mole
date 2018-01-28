#include "Include.h"

#define UPing		1
#define DOWNing		2
#define LEFTing		3
#define RIGHTing	4

M_Boolean Checkers;
M_Int32		x;
M_Int32		y;

void CatchFC()
{
	switch(Check)
	{
	case Set:
		MC_knlPrintk("Catch playing\n");
		CatchState();
	break;

	case Play:
		CatchUpdate();
		CatchDraw();
	break;

	case SetEnd:
		CatchDestroy();
	break;
	}
}

void CatchState()
{
	Checkers = 0;
	x		 = 10;
	y		 = 10;
	Check	 = Play;
}

void CatchDraw()
{
	MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(0, 0, 0));
	FillRect(x,y,10,10);
	MC_knlPrintk("Catch playing\n");
	
}

void CatchUpdate()
{
	switch(Checkers)
	{
		case UPing:
			y-=2;
			break;
		case DOWNing:
			y+=2;
			break;
		case LEFTing:
			x-=2;
			break;
		case RIGHTing:
			x+=2;
			break;
		
	}
}

void CatchMenuKey(M_Int32 Key)
{
	switch(Key)
	{
	case MC_KEY_UP:
		Checkers=UPing;
		break;
	case MC_KEY_DOWN:
		Checkers=DOWNing;
		break;
	case MC_KEY_LEFT:
		Checkers=LEFTing;
		break;
	case MC_KEY_RIGHT:
		Checkers=RIGHTing;
		break;

	}
}

void CatchDestroy()
{
}