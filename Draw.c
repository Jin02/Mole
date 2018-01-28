#include "Include.h"




void String(M_Char * str, M_Int32 x, M_Int32 y)
{
	MC_grpDrawString(g_screenBuffer, x, y, str, strlen(str), &g_GC);
}

void FillRect(M_Int32 x, M_Int32 y, M_Int32 w, M_Int32 h)
{
	MC_grpFillRect( g_screenBuffer, x, y, w, h,	&g_GC);
}
void DrawImage(M_Int32 x, M_Int32 y, M_Int32 w, M_Int32 h,MC_GrpImage img,M_Int32 ImageX,M_Int32 ImageY)
{

	MC_grpDrawImage(g_screenBuffer, x+nGSX, y+nGSY,w,h,img,ImageX,ImageY,&g_GC);

}