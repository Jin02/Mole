#include "Include.h"


MC_GrpImage				Img[1];

void GetImageFromResID( MC_GrpImage *pGrpImage, M_Char *szResName )
{
	M_Int32 iResourceSample;
	M_Int32 iResourceSampleSize;
	M_Int32 iImage;

	// �̹��� ���ҽ��� ID�� ��´�. 
	iResourceSample =  MC_knlGetResourceID( szResName, &iResourceSampleSize );
	// �̹��� ���ҽ��� ���۸� �Ҵ��Ѵ�. 
	iImage = MC_knlCalloc( iResourceSampleSize );
	// �̹��� ���ҽ� �����͸� ���ۿ� �ִ´�. 
	MC_knlGetResource( iResourceSample, (void*)iImage, iResourceSampleSize );
	// �̹����� �����. 
	MC_grpCreateImage( pGrpImage, iImage, 0, iResourceSampleSize );
}