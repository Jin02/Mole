#ifndef __SCENE_H__
#define __SCENE_H__

#include "Include.h"

typedef struct _Scene{
	M_Int32 maxFrame;				//최대 프레임 수

	M_Uint32 maxElementOfFrameID;
	M_Int32* maxElementOfFrame;		//프레임을 구성하는 요수의 갯수

	M_Uint32 elementListOfFrameID;
	M_Uint32* elementListOfFrame;	//요소리스트(ex 이미지1, 이미지2)

	M_Uint32 frameIntervalXID;
	M_Uint32* frameIntervalX;		//프레임의 X좌표 위치

	M_Uint32 frameIntervalYID;
	M_Uint32* frameIntervalY;		//프레임의 Y좌표 위치

	M_Uint32 ImageIntervalXID;
	M_Uint32* ImageIntervalX;		//이미지상에서 읽어올 이미지의 X좌표

	M_Uint32 ImageIntervalYID;
	M_Uint32* ImageIntervalY;		//이미지상에서 읽어올 이미지의 Y좌표

	M_Uint32 ImageWidthID;
	M_Uint32* ImageWidth;			//출력 이미지의 넓이

	M_Uint32 ImageHeightID;
	M_Uint32* ImageHeight;			//출력 이미지의 높이

	M_Uint32 layerID;
	M_Uint32* layer;

	M_Uint32 frameTimeID;
	M_Int32* frameTime;
}Scene;

#endif