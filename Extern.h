#ifndef __EXTERN_H__
#define __EXTERN_H__

extern MC_GrpContext g_GC;
extern MC_GrpFrameBuffer g_screenBuffer;

extern M_Int32 x;
extern M_Int32 y;
extern M_Int32 Checking;

extern M_Int32 nSXS;                 // �� LCD ���� 
extern M_Int32 nSYS;                 // �� LCD ���� 
extern M_Int32 nCXS;                 // �� LCD ����/2
extern M_Int32 nCYS;                 // �� LCD ����/2

extern M_Int32 nGXS;				// ���� ���� ���� 
extern M_Int32 nGYS;				// ���� ���� ���� 
extern M_Int32 nGSX;				// ���� ȭ���� X ������ 
extern M_Int32 nGSY;				// ���� ȭ���� Y ������

extern MC_GrpImage img[1];

extern M_Int32 nKey;
extern M_Int32 Change;
extern M_Int32	Check;
extern M_Int32 Game1AiSpeed;
extern M_Int32 BollCheck;


#endif