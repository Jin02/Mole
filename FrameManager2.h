/*
* 2008. 8. 30
* Wipi-C FrameManager - C -
* Create by LEE. Sang. Gil
*/
#ifndef __FRAMEMANAGER_H__
#define __FRAMEMANAGER_H__

#include "Include.h"


extern MC_GrpImage				Img[1];
/*
* 여러개의 씬을 관리하기 위해 연결리스트를 만들 노드를 정의
*/
typedef struct _SceneList{
	M_Uint32 listID;			//리스트의 ID
	M_Int32  No;				//씬의 번호
	
	M_Uint32 sceneID;			//씬의 ID
	Scene* scene;				//생성된 씬의 주소값 저장
	
	M_Uint32 PreLinkID;			//씬을 이중 연결 리스트로 만들기 위한 링크
	M_Uint32 NextLinkID;
}SceneList;

/*
* 씬을 관리 및 현재 프레임 출력을 위한 정보를 가지고 있는 구조체
*/
typedef struct _FrameManager{
	M_Int32 sceneID;			//현재 활성회된 씬의 ID
	Scene* scene;				//현재 활성화된 씬
	
	M_Int32 HeadID;				//씬 리스트의 시작 씬의 ID 
	M_Int32 RearID;				//씬 리스트의 마지막 씬의 ID
	
	SceneList* Head;			//씬 리스트의 시작 씬 
	SceneList* Rear;			//씬 리스트의 마지막 씬
	
	M_Int32 curFrame;			//씬에서 활성화된 프레임번호
	M_Boolean bFrameOnceCompleted; //씬의 애니메이션이 한번이상 반복되었는지 확인하기 위한 변수

	M_Int64 FrameTime;//출력된 프레임 시간 기록


}FrameManager;

void		addScene(FrameManager* Manager, M_Int32 name);
M_Boolean	sceneNameComp(SceneList* serchScene, M_Int32 num);
void		SetScene(FrameManager* Manager, M_Int32 name);
void		DrawFrame(FrameManager* Manager, M_Int32 x, M_Int32 y);
void		delSceneElement(Scene* pScene);
void		delScene(FrameManager* Manager, M_Int32 name);
void		delAllScene(FrameManager* Manager);
void		SetMaxFrame(FrameManager* Manager, M_Int32 maxFrame);
void		setMaxElementOfFrame(FrameManager* Manager, M_Int32 maxElement, M_Int32 frameTime);
void		setMaxElementOfFrame2(FrameManager* Manager, M_Int32 frameIdx, M_Int32 maxElement, M_Int32 frameTime);
void		addElementOfFrame(FrameManager* Manager, M_Int32 imageIdx, M_Int32 frameIntervalX, M_Int32 frameIntervalY,
							  M_Int32 imageIntervalX, M_Int32 imageIntervalY, M_Int32 w, M_Int32 h, M_Int32 layer);
void		addElementOfFrame2(FrameManager* Manager, M_Int32 frameIdx, M_Int32 elementIdx, M_Int32 imageIdx,
							   M_Int32 frameIntervalX, M_Int32 frameIntervalY,
							   M_Int32 imageIntervalX, M_Int32 imageIntervalY, M_Int32 w, M_Int32 h, M_Int32 layer);
void		setFirstFrame(FrameManager* Manager);
void		setLastFrame(FrameManager* Manager);
void		nextFrame(FrameManager* Manager);
M_Int32		getMaxFrame(FrameManager* Manager);
M_Int32		getLayer(FrameManager* Manager);
M_Int32		getCurFrame(FrameManager* Manager);
void		getFrameManagerPtr(FrameManager* Manager);
Scene*		getScenePtr(M_Uint32 ID);

#endif