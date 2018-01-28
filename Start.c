#include "Include.h"

M_Boolean PressKey;
M_Int32 Move;
M_Int32 Replay;

void FC()
{
	switch(Check)
	{
	case Set:
		State();
	break;

	case Play:
		Update();
		Draw();
	break;

	case SetEnd:
		Destroy();
	break;
	}

}
void State()
{
	GetImageFromResID(&Img[0],"Main");
	Move = 0;
	Replay = 0;
	BollCheck = 1;
	MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_TRANS_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255,0,255));
		
	Check=Play;
}
void Draw()
{
	if(Change==Start){
	MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(14, 133, 220));
	MC_grpFillRect( g_screenBuffer, 0, 0, nSXS, nSYS,	&g_GC);
	MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(0, 0, 0));

	DrawImage(0,0,176,220,Img[0],Move,0);
	DrawImage(-8,10,69,75,Img[0],25,247);
	DrawImage(58,10,60,63,Img[0],104,253);
	DrawImage(110,10,69,73,Img[0],170,249);
	DrawImage(59+nGSX,100+nGSY,56,36,Img[0],107,352);
	DrawImage(110,10,69,73,Img[0],170,249);

	if(PressKey%2 == 0)
		String("Any Key!!",64+nGSX,180+nGSY);

	}
}
void Update()
{
	PressKey += 1;
	Move += 1;
}

void MenuKey(M_Int32 Key)
{
	Check=SetEnd;
}
void Destroy()
{
	MC_grpDestroyImage(Img[0]);
	Change = Menu;
	Check = Set;
	MC_grpInitContext( &g_GC );
}
