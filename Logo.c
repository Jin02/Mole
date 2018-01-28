#include "Include.h"

M_Int32 StartTimei;
M_Int32 LogoTimei;
M_Int32 i;
M_Int32 j;
M_Int32 BollCheck;


void LogoFC()
{
	switch(Check)
	{
	case Set:
		LogoState();
	break;

	case Play:
		LogoUpdate();
		LogoDraw();
	break;

	case SetEnd:
		LogoDestroy();
	break;
	}
}

void LogoState()
{
	GetImageFromResID(&Img[1],"Logo");
	i			= 10;
	j			= 0;
	BollCheck	= 0;
	Check 		= Play;
}

void LogoDraw()
{
	if(BollCheck==0)
	{
		MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_ALPHA_IDX, (void*)i);
		FillRect(0,0,nGSX,nGSY);
	}

	DrawImage(0,0,176,220,Img[1],0,0);
}

void LogoUpdate()
{
	if( i < 250 && j==0 )
		i+=10;

	MC_knlPrintk("%d\n",i);	
}
void LogoMenuKey(M_Int32 Key)
{
	Check = SetEnd;
}
void LogoDestroy()
{
	MC_grpDestroyImage(Img[1]);
	Change = Start;
	Check = Set;
	MC_grpInitContext( &g_GC );
}
