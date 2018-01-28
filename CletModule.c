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

M_Int32 nKey = 0;			//Ű���� ����
MCTimer g_Timer;			//Ÿ�̸� ����

M_Int32 x;
M_Int32 y;
M_Int32 Checking;
M_Int32 Game1AiSpeed;

M_Int32 nSXS;                 // �� LCD ���� 
M_Int32 nSYS;                 // �� LCD ���� 
M_Int32 nCXS;                 // �� LCD ����/2
M_Int32 nCYS;                 // �� LCD ����/2

M_Int32 nGXS;				// ���� ���� ���� 
M_Int32 nGYS;				// ���� ���� ���� 
M_Int32 nGSX;				// ���� ȭ���� X ������ 
M_Int32 nGSY;				// ���� ȭ���� Y ������

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


/* �̺�Ʈ�� ó���ϴ� �Լ��̴�.*/
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

/* ���α׷��� ���۵� �� �Ҹ��� �Լ��̴�. */
void startClet( int argc, char *argv[] )
{
	
	g_screenBuffer = MC_grpGetScreenFrameBuffer(0);
	MC_grpInitContext( &g_GC );

	nSXS = MC_GRP_GET_FRAME_BUFFER_WIDTH(g_screenBuffer);    // LCD ����
	nSYS = MC_GRP_GET_FRAME_BUFFER_HEIGHT(g_screenBuffer);   // LCD ����
	nCXS = nSXS >> 1;                              // LCD ����/2
	nCYS = nSYS >> 1;                              // LCD ����/2

	nGXS = 176;										// ���� ���� ���� 
	nGYS = 220;										// ���� ���� ���� 
	nGSX = (nSXS-nGXS)/2;						// ���� ȭ���� X ������ 
	nGSY = (nSYS-nGYS)/2;						// ���� ȭ���� Y ������


	Game1AiSpeed=PLSPEED;

	MC_knlDefTimer( &g_Timer, Timer ); // Ÿ�̸� ����
	MC_knlSetTimer( &g_Timer, 1000, NULL );	// 1�� �Ŀ� Ÿ�̸� �۵�(ms ����)
}


/* ���α׷��� ��� ���߾� ���� �� �Լ��� ȣ���� �ش�.*/
void pauseClet( void )
{
}

/* ���α׷��� �簳�� �� �� �Լ��� ȣ���� �ش�. */
void resumeClet( void )
{
}


/* ���α׷��� ����� �� �Ҹ���. */
void destroyClet( void )
{
}


/*ȭ���� �Ϻκ��� �ٽ� ĥ�ؾ� �ϴ� ��쿡 �Ҹ��� �Լ��̴�./ */
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
	MC_knlSetTimer( &g_Timer, Game1AiSpeed, NULL ); // 0.1�� �Ŀ� Ÿ�̸� �۵�(ms ����)
 
	
}