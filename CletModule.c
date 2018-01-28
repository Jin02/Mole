/*
** ===========================================================================
**
** Project: 
**     WIPI
**
** File:
**     CletModule.c
**
** Description: 
**     Application Skeleton 
**
** ===========================================================================
*/



/* 
**----------------------------------------------------------------------------
**  INCLUDE FILES FOR MODULE
**---------------------------------------------------------------------------- 
*/
#include "Include.h"


/* 
**----------------------------------------------------------------------------
**  VARIABLES FOR MODULE
**---------------------------------------------------------------------------- 
*/
MC_GrpContext g_GC;
MC_GrpFrameBuffer g_screenBuffer;

M_Int32 Change=Logo;
M_Int32	Check=Set;

M_Int32 nKey = 0;			//키정보 저장
MCTimer g_Timer;			//타이머 변수

M_Int32 x;
M_Int32 y;
M_Int32 Checking;
M_Int32 Game1AiSpeed;

M_Int32 nSXS;                 // 폰 LCD 가로 
M_Int32 nSYS;                 // 폰 LCD 세로 
M_Int32 nCXS;                 // 폰 LCD 가로/2
M_Int32 nCYS;                 // 폰 LCD 세로/2

M_Int32 nGXS;				// 게임 가로 넓이 
M_Int32 nGYS;				// 게임 세로 넓이 
M_Int32 nGSX;				// 게임 화면의 X 시작점 
M_Int32 nGSY;				// 게임 화면의 Y 시작점

/* 
**----------------------------------------------------------------------------
**  FUCTION PROTOTYPES
**---------------------------------------------------------------------------- 
*/
void Timer(MCTimer* pTm, void* parm);

/* 
**----------------------------------------------------------------------------
**   LAYOUTS FOR MODULE
**---------------------------------------------------------------------------- 
*/


/* 이벤트를 처리하는 함수이다.*/
void handleCletEvent( int type, int param1, int param2 ) 
{
	switch( type )
	{
		case MV_KEY_PRESS_EVENT:
			{
				Checking=1;
				nKey = param1;
				KeyChange(param1);
				//MC_knlPrintk("%d\n",Checking);
			}
			break;
		case MV_KEY_RELEASE_EVENT:
			{	
				Checking=0;
				nKey=param1;
				Keyoff(param1);
				//MC_knlPrintk("%d\n",Checking);
			}
			break;
	}
}

/* 프로그램이 시작될 때 불리는 함수이다. */
void startClet( int argc, char *argv[] )
{
	
	g_screenBuffer = MC_grpGetScreenFrameBuffer(0);
	MC_grpInitContext( &g_GC );

	nSXS = MC_GRP_GET_FRAME_BUFFER_WIDTH(g_screenBuffer);    // LCD 가로
	nSYS = MC_GRP_GET_FRAME_BUFFER_HEIGHT(g_screenBuffer);   // LCD 세로
	nCXS = nSXS >> 1;                              // LCD 가로/2
	nCYS = nSYS >> 1;                              // LCD 세로/2

	nGXS = 176;										// 게임 가로 넓이 
	nGYS = 220;										// 게임 세로 넓이 
	nGSX = (nSXS-nGXS)/2;						// 게임 화면의 X 시작점 
	nGSY = (nSYS-nGYS)/2;						// 게임 화면의 Y 시작점


	Game1AiSpeed=PLSPEED;

	MC_knlDefTimer( &g_Timer, Timer ); // 타이머 선언
	MC_knlSetTimer( &g_Timer, 1000, NULL );	// 1초 후에 타이머 작동(ms 단위)
}


/* 프로그램이 잠시 멈추어 질때 이 함수를 호출해 준다.*/
void pauseClet( void )
{
}

/* 프로그램이 재개될 때 이 함수를 호출해 준다. */
void resumeClet( void )
{
}


/* 프로그램이 종료될 때 불린다. */
void destroyClet( void )
{
}


/*화면의 일부분을 다시 칠해야 하는 경우에 불리는 함수이다./ */
void paintClet( int x, int y, int w, int h )
{
	MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(255, 255, 255));
	MC_grpFillRect( g_screenBuffer, 0, 0, nSXS, nSYS,	&g_GC);
	MC_grpSetContext(&g_GC, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(0, 0, 0));

	StateChange();
//MC_knlPrintk("%d\n",Game1AiSpeed);
	MC_grpFlushLcd( 0, g_screenBuffer, 0, 0, MC_GRP_GET_FRAME_BUFFER_WIDTH( g_screenBuffer ), 
		MC_GRP_GET_FRAME_BUFFER_HEIGHT( g_screenBuffer) );
}

void Timer(MCTimer* pTm, void* parm)
{

	MC_grpRepaint(0, 0, 0, MC_GRP_GET_FRAME_BUFFER_WIDTH( g_screenBuffer ),
		MC_GRP_GET_FRAME_BUFFER_HEIGHT( g_screenBuffer));
	MC_knlSetTimer( &g_Timer, Game1AiSpeed, NULL ); // 0.1초 후에 타이머 작동(ms 단위)
 
	
}