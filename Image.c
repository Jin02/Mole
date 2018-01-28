#include "Include.h"


MC_GrpImage				Img[1];

void GetImageFromResID( MC_GrpImage *pGrpImage, M_Char *szResName )
{
	M_Int32 iResourceSample;
	M_Int32 iResourceSampleSize;
	M_Int32 iImage;

	// 이미지 리소스의 ID를 얻는다. 
	iResourceSample =  MC_knlGetResourceID( szResName, &iResourceSampleSize );
	// 이미지 리소스의 버퍼를 할당한다. 
	iImage = MC_knlCalloc( iResourceSampleSize );
	// 이미지 리소스 데이터를 버퍼에 넣는다. 
	MC_knlGetResource( iResourceSample, (void*)iImage, iResourceSampleSize );
	// 이미지를 만든다. 
	MC_grpCreateImage( pGrpImage, iImage, 0, iResourceSampleSize );
}