#ifndef __EXTERN_H__
#define __EXTERN_H__

extern MC_GrpContext g_GC;
extern MC_GrpFrameBuffer g_screenBuffer;

extern M_Int32 x;
extern M_Int32 y;
extern M_Int32 Checking;

extern M_Int32 nSXS;                 // 폰 LCD 가로 
extern M_Int32 nSYS;                 // 폰 LCD 세로 
extern M_Int32 nCXS;                 // 폰 LCD 가로/2
extern M_Int32 nCYS;                 // 폰 LCD 세로/2

extern M_Int32 nGXS;				// 게임 가로 넓이 
extern M_Int32 nGYS;				// 게임 세로 넓이 
extern M_Int32 nGSX;				// 게임 화면의 X 시작점 
extern M_Int32 nGSY;				// 게임 화면의 Y 시작점

extern MC_GrpImage img[1];

extern M_Int32 nKey;
extern M_Int32 Change;
extern M_Int32	Check;
extern M_Int32 Game1AiSpeed;
extern M_Int32 BollCheck;


#endif