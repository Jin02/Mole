#ifndef __SCENE_H__
#define __SCENE_H__

#include "Include.h"

typedef struct _Scene{
	M_Int32 maxFrame;				//�ִ� ������ ��

	M_Uint32 maxElementOfFrameID;
	M_Int32* maxElementOfFrame;		//�������� �����ϴ� ����� ����

	M_Uint32 elementListOfFrameID;
	M_Uint32* elementListOfFrame;	//��Ҹ���Ʈ(ex �̹���1, �̹���2)

	M_Uint32 frameIntervalXID;
	M_Uint32* frameIntervalX;		//�������� X��ǥ ��ġ

	M_Uint32 frameIntervalYID;
	M_Uint32* frameIntervalY;		//�������� Y��ǥ ��ġ

	M_Uint32 ImageIntervalXID;
	M_Uint32* ImageIntervalX;		//�̹����󿡼� �о�� �̹����� X��ǥ

	M_Uint32 ImageIntervalYID;
	M_Uint32* ImageIntervalY;		//�̹����󿡼� �о�� �̹����� Y��ǥ

	M_Uint32 ImageWidthID;
	M_Uint32* ImageWidth;			//��� �̹����� ����

	M_Uint32 ImageHeightID;
	M_Uint32* ImageHeight;			//��� �̹����� ����

	M_Uint32 layerID;
	M_Uint32* layer;

	M_Uint32 frameTimeID;
	M_Int32* frameTime;
}Scene;

#endif