#include "Include.h"

MOLE Mole;

M_Int64 Seed;

M_Int32 PLUS;

M_Int32 speed;
M_Int32 SeTTing;

M_Int64 CheckingTime;
M_Int64 CheckingTime2;

M_Int32 KeyCheck;

M_Boolean maxs;
M_Boolean stagesetting;

M_Int32 Statuschange;

M_Boolean stageselect;

M_Boolean TrueandFalse;

#define liAil	30

#define PLAYERON 222

#define stageone	1
#define stagetwo	2
#define stagethree	3
#define stagefour	4
#define stagefive	5
#define stagesix	6
#define stageseven	7
#define stageeight	8



void WingFC()
{
	switch(Check)
	{
	case Set:
		Winglnit();
	break;

	case Ready:
		ReadyDraw();
	break;

	case liAil:
		iAi();
		break;

	case Play:
		WingUpdate();
		WingDraw();
	break;

	case SetEnd:
		WingDestroy();
	break;
	}
}
void Winglnit()
{ 
	stagesetting	= stageone;
	speed 			= 0;
	Mole.CC 		= 0;
	SeTTing 		= 0;
	PLUS 			= 1;
	maxs			= 3;
	Statuschange	= 0;
	Game1AiSpeed	= OneStage;
	KeyCheck		= 0;
	stageselect		= 0;
	Seed 			= MC_knlCurrentTime();	
	Check 			= Ready;
	Mole.StartTime 	= MC_knlCurrentTime();	
}
void ReadyDraw()
{
	Mole.PlayTime=(MC_knlCurrentTime()-Mole.StartTime)/1000;

	if(Mole.PlayTime==1)
	{
		Mole.AiTime=MC_knlCurrentTime();
		Check = liAil;
	}
}

void iAi()
{
	switchgamespeed();

	if(stageselect==0)
	{
		Stagenumber();
		stageselect=1;
	}
					
	MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(0, 0, 0));
	DrawFillRect();
			
	Mole.PlTime=(MC_knlCurrentTime()-Mole.AiTime)/1000;
	
	if(Mole.PlTime<5)
		String("Ai 차례입니다.",3,10);

	if(Mole.PlTime>5)
	{	
		GettingString();
		
		switch(SeTTing)
		{
		case 1:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));	
			FillRect(20*1*2,30*1,20,20);
		break;
		case 2:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*2*2,30*1,20,20);
		break;
		case 3:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*3*2,30*1,20,20);
		break;
		case 4:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*1*2,30*2,20,20);
		break;
		case 5:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*2*2,30*2,20,20);
		break;
		case 6:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*3*2,30*2,20,20);
		break;
		case 7:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*1*2,30*3,20,20);
		break;
		case 8:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*2*2,30*3,20,20);
		break;
		case 9:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*3*2,30*3,20,20);
		break;
	}

	if(PLUS<maxs)
		PLUS++;
	
	if(PLUS==maxs)
	{
		Check =. Play;
		Statuschange++;
		if(Statuschange!=5)		PLUS=0;
		else					CountSystem();

		MC_knlPrintk("%d\n",Statuschange);
	}
}

}



void WingUpdate()
{

	Game1AiSpeed=PLSPEED;
	switch(stagesetting)
	{
	case stageone:
			Mole.OneStagePlayone[KeyCheck]=Mole.GamePlayChecking;
		break;
	case stagetwo:
			Mole.OneStagePlaytwo[KeyCheck]=Mole.GamePlayChecking;
		break;
	case stagethree:
			Mole.TwoStagePlayone[KeyCheck]=Mole.GamePlayChecking;
		break;
	case stagefour:
			Mole.TwoStagePlaytwo[KeyCheck]=Mole.GamePlayChecking;
		break;
	case stagefive:
			Mole.ThreeStagePlayone[KeyCheck]=Mole.GamePlayChecking;
		break;
	case stagesix:
			Mole.ThreeStagePlaytwo[KeyCheck]=Mole.GamePlayChecking;
		break;
	case stageseven:
			Mole.FourStagePlayone[KeyCheck]=Mole.GamePlayChecking;
		break;
	case stageeight:
			Mole.FourStagePlaytwo[KeyCheck]=Mole.GamePlayChecking;
		break;
	}

	MC_knlPrintk("%d. = %d\n",KeyCheck,Mole.OneStagePlayone[KeyCheck]);
	TrueandFalseCheck();
	zeroCheck();	
}

void WingDraw()
{
	MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(0, 0, 0));

	DrawFillRect();

	if(Checking==1)
	{
		switch(Mole.CC)
		{
		case 1:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));	
			FillRect(20*1*2,30*1,20,20);
			break;
		case 2:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*2*2,30*1,20,20);
			break;
		case 3:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*3*2,30*1,20,20);
			break;
		case 4:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*1*2,30*2,20,20);
			break;
		case 5:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*2*2,30*2,20,20);
			break;
		case 6:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*3*2,30*2,20,20);
			break;
		case 7:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*1*2,30*3,20,20);
			break;
		case 8:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*2*2,30*3,20,20);
			break;
		case 9:
			MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
			FillRect(20*3*2,30*3,20,20);
			break;
		}
	}

}

void PlayKeyoff(M_Int32 Key)
{
	Mole.CC =. 0;
}

void ReadyKey(M_Int32 Key)
{
}

void PlayKey(M_Int32 Key)
{
	if(Check==Play)
	{
		switch(Key)
		{
			case MC_KEY_1:
					Mole.CC=1;
					PlayerCheck();
					Mole.GamePlayChecking=1;
					
					
			break;
				case MC_KEY_2:
					Mole.CC=2;
					Mole.GamePlayChecking=2;
					PlayerCheck();
			break;
				case MC_KEY_3:
					Mole.CC=3;
					Mole.GamePlayChecking=3;
					PlayerCheck();
			break;
				case MC_KEY_4:
					Mole.CC=4;
					Mole.GamePlayChecking=4;
					PlayerCheck();
			break;
				case MC_KEY_5:
					Mole.CC=5;
					Mole.GamePlayChecking=5;
					PlayerCheck();
			break;
				case MC_KEY_6:
					Mole.CC=6;
					Mole.GamePlayChecking=6;
					PlayerCheck();
			break;
				case MC_KEY_7:
					Mole.CC=7;
					Mole.GamePlayChecking=7;
					PlayerCheck();
			break;
				case MC_KEY_8:
					Mole.CC=8;
					Mole.GamePlayChecking=8;
					PlayerCheck();
			break;		
				case MC_KEY_9:
					Mole.CC=9;
					Mole.GamePlayChecking=9;
					PlayerCheck();
			break;
		}
	}
}

void WingDestroy()
{

}

M_Int32 GetRand(M_Int32 min,M_Int32 max)
{
	if(min == max)
		return min;
	else
		return(M_Int32)(((((Seed=Seed*214013+2531011)>>24)&0x7FFFFFFFF)%(max-min+1))+min);
}

void DrawFillRect()
{
	FillRect(20*1*2,30*1,20,20);
	FillRect(20*2*2,30*1,20,20);
	FillRect(20*3*2,30*1,20,20);
	FillRect(20*1*2,30*2,20,20);
	FillRect(20*2*2,30*2,20,20);
	FillRect(20*3*2,30*2,20,20);
	FillRect(20*1*2,30*3,20,20);
	FillRect(20*2*2,30*3,20,20);
	FillRect(20*3*2,30*3,20,20);
}

void CountSystem()
{
	if(PLUS==3 && stagesetting==stageone &&  Statuschange==5)
	{
		PLUS=0;
		maxs=4;
		Statuschange=0;
		stagesetting=stagetwo;
		MC_knlPrintk("check!!\n");
				
	}
	
	if(PLUS==4 && stagesetting==stagetwo &&  Statuschange==5)
	{
		PLUS=0;
		maxs=5;
		Statuschange=0;
		stagesetting=stagethree;
	}
	
	if(PLUS==5 && stagesetting==stagethree &&  Statuschange==5)
	{
		PLUS=0;
		maxs=6;
		Statuschange=0;
		stagesetting=stagefour;
					
	}
	if(PLUS==6 && stagesetting==stagefour &&  Statuschange==5)
	{
		PLUS=0;
		maxs=7;
		Statuschange=0;
		stagesetting=stagefive;
	}

	if(PLUS==7 && stagesetting==stagefive &&  Statuschange==5)
	{
		PLUS=0;
		maxs=8;
		Statuschange=0;
		stagesetting=stagesix;
	}
	
	if(PLUS==8 && stagesetting==stagesix &&  Statuschange==5)
	{
		PLUS=0;
		maxs=9;
		Statuschange=0;
		stagesetting=stageseven;
	}
	if(PLUS==9 && stagesetting==stageseven &&  Statuschange==5)
	{
		PLUS=0;
		maxs=10;
		Statuschange=0;
		stagesetting=stageeight;
	}
	if(PLUS==10 && stagesetting==stageeight &&  Statuschange==5)
	{
		PLUS=0;
		stagesetting=0;
		maxs=0;
	}
	if(stagesetting==0)
	{
		maxs=0;
		PLUS=0;
	}
}

void GettingString()
{
	switch(stagesetting)
	{
	case stageone:
		Game1AiSpeed=OneStage;
		SeTTing=Mole.OneStageone[PLUS];
		String("1레벨 1스테이지 입니다",100+nGSX,10+nGSY);
		break;

	case stagetwo:
		Game1AiSpeed=OneStage;
		SeTTing=Mole.OneStagetwo[PLUS];
		String("1레벨 2스테이지 입니다",100+nGSX,10+nGSY);
		break;

	case stagethree:
		Game1AiSpeed=TwoStage;
		SeTTing=Mole.TwoStageone[PLUS];
		String("2레벨 1스테이지 입니다",100+nGSX,10+nGSY);
		break;

	case stagefour:
		Game1AiSpeed=TwoStage;
		SeTTing=Mole.TwoStagetwo[PLUS];
		String("2레벨 2스테이지 입니다",100+nGSX,10+nGSY);
		break;

	case stagefive:
		Game1AiSpeed=ThreeStage;
		SeTTing=Mole.ThreeStageone[PLUS];
		String("3레벨 1스테이지 입니다",100+nGSX,10+nGSY);
		break;

	case stagesix:
	Game1AiSpeed=ThreeStage;
		SeTTing=Mole.ThreeStagetwo[PLUS];
		String("3레벨 2스테이지 입니다",100+nGSX,10+nGSY);
		break;

	case stageseven:
		Game1AiSpeed=FourStage;
		SeTTing=Mole.FourStageone[PLUS];
		String("4레벨 1스테이지 입니다",100+nGSX,10+nGSY);
		break;

	case stageeight:
		Game1AiSpeed=FourStage;
		SeTTing=Mole.FourStagetwo[PLUS];
		String("4레벨 2스테이지 입니다",100+nGSX,10+nGSY);
		break;
	}
}

ßvoid Stagenumber()
{
	int i,j,k,l,m,n,b,p;

	switch(stagesetting)
	{
	case stageone:
		for(i=1;i<3;i++)
			Mole.OneStageone[i]=GetRand(1,9);
	break;

	case stagetwo:
		for(j=1;j<4; j++)
			Mole.OneStagetwo[j]=GetRand(1,9);
	break;

	case stagethree:
		for(k=1;k<5;k++)
			Mole.TwoStageone[k]=GetRand(1,9);
	break;
	case stagefour:
		for(l=1; l<6; l++)
			Mole.TwoStagetwo[l]=GetRand(1,9);
	break;
	case stagefive:
		for(m=1; m<7; m++)
			Mole.ThreeStageone[m]=GetRand(1,9);		
	break;
	case stagesix:
		for(n=1; n<8; n++)
			Mole.ThreeStagetwo[n]=GetRand(1,9);		
	break;
	case stageseven:
		for(b=1; b<9; b++)
			Mole.FourStageone[b]=GetRand(1,9);		
	break;
	case stageeight:
		for(p=1; p<10; p++)
			Mole.FourStagetwo[p]=GetRand(1,9);
	break;	
	}
}

void PlayerCheck()
{	
	switch(stagesetting)
	{
	case stageone:
		if(KeyCheck<2)
			KeyCheck++;		
		break;
	}
}

void switchgamespeed()
{
	switch(stagesetting)
	{
	case stageone:
		Game1AiSpeed=OneStage;
		break;
	case stagetwo:
		Game1AiSpeed=OneStage;
		break;
	case stagethree:
		Game1AiSpeed=TwoStage;
		break;
	case stagefour:
		Game1AiSpeed=TwoStage;
		break;
	case stagefive:
		Game1AiSpeed=ThreeStage;
		break;
	case stagesix:
		Game1AiSpeed=ThreeStage;
		break;
	case stageseven:
		Game1AiSpeed=FourStage;
		break;
	case stageeight:
		Game1AiSpeed=FourStage;
		break;
	}
}

void TrueandFalseCheck()
{
	switch(stagesetting)
	{
	case stageone:
		if(Mole.OneStageone[1]==Mole.OneStagePlayone[KeyCheck])
		{
			TrueandFalse=1;
			PLUScheck();
		}	
	break;

	case stagetwo:
		if(Mole.OneStagetwo[KeyCheck]==Mole.OneStagePlaytwo[KeyCheck])
		{
			Check=liAil;
			switchgamespeed();
			stageselect=0;
		}
	break;
	
	case stagethree:
		if(Mole.TwoStageone[KeyCheck]==Mole.TwoStagePlayone[KeyCheck])
		{
			Check=liAil;
			switchgamespeed();
			stageselect=0;
		}
	break;
	
	case stagefour:
		if(Mole.TwoStagetwo[KeyCheck]==Mole.TwoStagePlaytwo[KeyCheck])
		{
			Check=liAil;
			switchgamespeed();
			stageselect=0;
		}
	break;
	
	case stagefive:
		if(Mole.ThreeStageone[KeyCheck]==Mole.ThreeStagePlayone[KeyCheck])
		{
			Check=liAil;
			switchgamespeed();
			stageselect=0;
		}
	break;
	
	case stagesix:
		if(Mole.ThreeStagetwo[KeyCheck]==Mole.ThreeStagePlaytwo[KeyCheck])
		{
			Check=liAil;
			switchgamespeed();
			stageselect=0;
		}
	break;
	
	case stageseven:
		if(Mole.FourStageone[KeyCheck]==Mole.FourStagePlayone[KeyCheck])
		{
			Check=liAil;
			switchgamespeed();
			stageselect=0;
		}
	break;
	
	case stageeight:
		if(Mole.FourStagetwo[KeyCheck]==Mole.FourStagePlaytwo[KeyCheck])
		{
			Check=liAil;
			switchgamespeed();
			stageselect=0;
		}
	break;
	}
}
void zeroCheck()
{
	if(Statuschange==0)
	{
		switch(stagesetting)
		{
		case stagetwo:
			if(Mole.OneStageone[KeyCheck]==Mole.OneStagePlaytwo[KeyCheck])
			{
					Check=liAil;
					switchgamespeed();
					stageselect=0;
			}
		break;
		case stagethree:
			if(Mole.OneStagetwo[KeyCheck]==Mole.TwoStagePlayone[KeyCheck])
			{
					Check=liAil;
					switchgamespeed();
					stageselect=0;
			}
		break;
		case stagefour:
			if(Mole.TwoStageone[KeyCheck]==Mole.TwoStagePlaytwo[KeyCheck])
			{
					Check=liAil;
					switchgamespeed();
					stageselect=0;
			}
		break;
		case stagefive:
			if(Mole.TwoStagetwo[KeyCheck]==Mole.ThreeStagePlayone[KeyCheck])
			{
					Check=liAil;
					switchgamespeed();
					stageselect=0;
			}
		break;
		case stagesix:
			if(Mole.ThreeStageone[KeyCheck]==Mole.ThreeStagePlaytwo[KeyCheck])
			{
					Check=liAil;
					switchgamespeed();
					stageselect=0;
			}
		break;
		case stageseven:
			if(Mole.ThreeStagetwo[KeyCheck]==Mole.FourStagePlayone[KeyCheck])
			{
					Check=liAil;
					switchgamespeed();
					stageselect=0;
			}
		break;
		case stageeight:
			if(Mole.FourStagePlayone[KeyCheck]==Mole.FourStagePlaytwo[KeyCheck])
			{
					Check=liAil;
					switchgamespeed();
					stageselect=0;
			}
		break;
		}
	}
	
}
void PLUScheck()
{
	if(TrueandFalse==1)
	{
		if(Mole.OneStageone[2]==Mole.OneStagePlayone[KeyCheck])
		{
			Check=liAil;
			switchgamespeed();
			stageselect=0;
			TrueandFalse=0;
			MC_knlPrintk("Check!!!\n");
		}
	}
}