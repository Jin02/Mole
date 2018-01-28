#include "Include.h"


M_Int32 frameIdx;	//프레임이 추가할 때 추가되어야 할 곳을 가르킨다.
M_Int32 elementframeIdx; //프레임의 요소가 추가될때 프레임
M_Int32 elementIdx; //프레임의 요소가 추가되어야 할 곳을 가르킨다.


//////////////////////////////////////////////////////////////////////////
//
// int addScene() : 프레임 메니져에 씬을 생성한다.
//
// 인자값 : M_Uint32 Manager - 삽입될 프레임 메니져의 ID값
//          M_Int32 name	 - 삽입될 씬의 고유번호(키)
//
// 반환값 : 없음
//
void addScene(FrameManager* Manager, M_Int32 name)
{
	M_Uint32 newSceneID;
	SceneList* newScene = NULL;
	
	getFrameManagerPtr(Manager);
	
	if(Manager->HeadID == NULL || Manager->HeadID == 0)
	{

	}
	else
	{
		if(sceneNameComp((SceneList*)MC_GETDPTR(Manager->HeadID), name))	//이미 삽입된 씬의 이름과 중복될때 삽입 중단
		return;
	}
	
	//MC_knlPrintk("addScene_3\n");
	newSceneID = MC_knlCalloc(sizeof(SceneList));
	newScene = (SceneList*)MC_GETDPTR(newSceneID);
	
	newScene->listID = newSceneID;
	newScene->No = name;
	newScene->sceneID = MC_knlCalloc(sizeof(Scene));
	newScene->scene = (Scene*)MC_GETDPTR(newScene->sceneID);
	newScene->NextLinkID = 0;
	newScene->PreLinkID  = 0;

	if(Manager->HeadID == 0 || Manager->HeadID == NULL)
	{
		Manager->HeadID = newSceneID;
	}
	else
	{
		((SceneList*)MC_GETDPTR(Manager->RearID))->NextLinkID = newSceneID;
		newScene->PreLinkID = Manager->RearID;
	}
	Manager->RearID = newSceneID;
	Manager->sceneID = newScene->sceneID;
}

//////////////////////////////////////////////////////////////////////////
//
// M_Boolean sceneNameComp() : 해당 프레임메니져에 같은 이름의 씬이 존재하는지 조사한다.
//
// 인자값 : SceneList* serchScene - 조사될 프레임메니져의 씬리스트의 처음 노드 주소
//          M_Char* name		  - 삽입될 씬의 이름(키)
//
// 반환값 : true - 동일한 이름 발견시
//          false - 동일한 이름 발견없이 마지막 노드까지 검사종료시
//
M_Boolean sceneNameComp(SceneList* serchScene, M_Int32 num)
{
	while(serchScene != NULL)
	{
		if(serchScene->No == num)
			return 1;
		if(serchScene->NextLinkID == 0)
			serchScene = NULL;
		else
			serchScene = (SceneList*)MC_GETDPTR(serchScene->NextLinkID);
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
// void SetScene() : 해당 프레임메니저에 현재 씬을 설정한다.
//
// 인자값 : M_Uint32 Manager - 조사될 프레임메니져
//          M_Int32 name	 - 선택될 씬의 번호(키)
//
// 반환값 : 없음
//
void SetScene(FrameManager* Manager, M_Int32 name)
{
	SceneList* serchScene;
	
	getFrameManagerPtr(Manager);
	serchScene = (SceneList*)MC_GETDPTR(Manager->HeadID);
	
	while(serchScene != NULL)
	{
		if(serchScene->No == name)
			break;
		if(serchScene->NextLinkID == 0)
			serchScene = NULL;
		else
			serchScene = (SceneList*)MC_GETDPTR(serchScene->NextLinkID);
	}
	
	if(serchScene == NULL)
		return;
	else
	{
		Manager->sceneID = serchScene->sceneID;
		Manager->curFrame = 0;
		Manager->bFrameOnceCompleted = 0;
		Manager->FrameTime=MC_knlCurrentTime();
	}
}

//////////////////////////////////////////////////////////////////////////
//
// void DrawFrame() : 현재 씬의 프레임을 출력한다.
//
// 인자값 : M_Uint32 Manager - 출력될 프레임메니져
//			M_Int32 x		 - 출력될 X좌표
//			M_Int32 y        - 출력될 Y좌표
//          
// 반환값 : 없음
//
void DrawFrame(FrameManager* Manager, M_Int32 x, M_Int32 y)
{
	int i;
	M_Int32* temp;
	M_Int32 sx, sy, w, h, imgNo, fx, fy;
	getFrameManagerPtr(Manager);

	Manager->scene->maxElementOfFrame	= (M_Int32*)MC_GETDPTR(Manager->scene->maxElementOfFrameID);
	Manager->scene->elementListOfFrame	= (M_Uint32*)MC_GETDPTR(Manager->scene->elementListOfFrameID);
	Manager->scene->frameIntervalX		= (M_Uint32*)MC_GETDPTR(Manager->scene->frameIntervalXID);
	Manager->scene->frameIntervalY		= (M_Uint32*)MC_GETDPTR(Manager->scene->frameIntervalYID);
	Manager->scene->ImageIntervalX		= (M_Uint32*)MC_GETDPTR(Manager->scene->ImageIntervalXID);
	Manager->scene->ImageIntervalY		= (M_Uint32*)MC_GETDPTR(Manager->scene->ImageIntervalYID);
	Manager->scene->ImageWidth			= (M_Uint32*)MC_GETDPTR(Manager->scene->ImageWidthID);
	Manager->scene->ImageHeight			= (M_Uint32*)MC_GETDPTR(Manager->scene->ImageHeightID);
	Manager->scene->layer				= (M_Uint32*)MC_GETDPTR(Manager->scene->layerID);
	Manager->scene->frameTime			= (M_Int32*)MC_GETDPTR(Manager->scene->frameTimeID);
	
	for(i=0; i<Manager->scene->maxElementOfFrame[Manager->curFrame]; i++)
	{
		temp = (M_Int32*)MC_GETDPTR(Manager->scene->frameIntervalX[Manager->curFrame]);
		fx = temp[i];

		temp = (M_Int32*)MC_GETDPTR(Manager->scene->frameIntervalY[Manager->curFrame]);
		fy = temp[i];

		temp = (M_Int32*)MC_GETDPTR(Manager->scene->ImageWidth[Manager->curFrame]);
		w = temp[i];

		temp = (M_Int32*)MC_GETDPTR(Manager->scene->ImageHeight[Manager->curFrame]);
		h = temp[i];

		temp = (M_Int32*)MC_GETDPTR(Manager->scene->ImageIntervalX[Manager->curFrame]);
		sx = temp[i];

		temp = (M_Int32*)MC_GETDPTR(Manager->scene->ImageIntervalY[Manager->curFrame]);
		sy = temp[i];

		temp = (M_Int32*)MC_GETDPTR(Manager->scene->elementListOfFrame[Manager->curFrame]);
		imgNo = temp[i];
		
		MC_grpDrawImage(g_screenBuffer, x + fx, y + fy, w, h, Img[imgNo], sx, sy, &g_GC);
	}
}


//////////////////////////////////////////////////////////////////////////
//
// void delSceneElement() : 선택된 씬의 동적메모리를 모두 해제한다.
//
// 인자값 : Scene* pScene - 선택된 씬
//          
// 반환값 : 없음
//
void delSceneElement(Scene* pScene)
{
	MC_knlFree(pScene->maxElementOfFrameID);
	MC_knlFree(pScene->elementListOfFrameID);
	
	MC_knlFree(pScene->frameIntervalXID);
	MC_knlFree(pScene->frameIntervalYID);
	MC_knlFree(pScene->ImageIntervalXID);
	MC_knlFree(pScene->ImageIntervalYID);
	
	MC_knlFree(pScene->ImageHeightID);
	MC_knlFree(pScene->ImageWidthID);
	
	MC_knlFree(pScene->frameTimeID);
	MC_knlFree(pScene->layerID);
}


//////////////////////////////////////////////////////////////////////////
//
// void delScene() : 선택한 씬을 프레임메니져에서 삭제한다.
//
// 인자값 : M_Uint32 Manager - 해당 프레임메니져
//          M_Int32 name     - 삭제될 씬의 번호(키)
//          
// 반환값 : 없음
//
void delScene(FrameManager* Manager, M_Int32 name)
{
	SceneList* serchScene;
	
	getFrameManagerPtr(Manager);
	serchScene = (SceneList*)MC_GETDPTR(Manager->HeadID);
	
	while(serchScene != NULL)
	{
		if(serchScene->No == name)
			break;
		if(serchScene->NextLinkID == 0)
			serchScene = NULL;
		else
			serchScene = (SceneList*)MC_GETDPTR(serchScene->NextLinkID);
	}
	
	if(serchScene == NULL)
		return;
	else
	{
		if(Manager->Head == serchScene)
		{
			Manager->HeadID = serchScene->NextLinkID;
			serchScene->PreLinkID = 0;
			if(Manager->Rear == serchScene)
			{
				Manager->RearID = NULL;
			}
		}
		else if(Manager->Rear == serchScene)
		{
			Manager->RearID = serchScene->PreLinkID;
			((SceneList*)MC_GETDPTR(serchScene->PreLinkID))->NextLinkID = serchScene->NextLinkID;
		}
		else
		{
			((SceneList*)MC_GETDPTR(serchScene->PreLinkID))->NextLinkID = serchScene->NextLinkID;
			((SceneList*)MC_GETDPTR(serchScene->NextLinkID))->PreLinkID = serchScene->PreLinkID;
		}
		delSceneElement((Scene*)MC_GETDPTR(serchScene->sceneID));
		MC_knlFree(serchScene->sceneID);
		MC_knlFree(serchScene->listID);
	}
}

//////////////////////////////////////////////////////////////////////////
//
// void delAllScene() : 선택한 프레임메니져의 모든 씬을 삭제한다.
//
// 인자값 : M_Uint32 Manager - 선택된 프레임메니져
//          
// 반환값 : 없음
//
void delAllScene(FrameManager* Manager)
{
	SceneList* TempList;
	
	getFrameManagerPtr(Manager);
	
	while(Manager->HeadID != 0)
	{
		TempList = (SceneList*)MC_GETDPTR(Manager->HeadID);
		Manager->HeadID = TempList->NextLinkID;
		
		delSceneElement((Scene*)MC_GETDPTR(TempList->sceneID));
		MC_knlFree(TempList->sceneID);
		MC_knlFree(TempList->listID);
	}
	
	Manager->RearID = 0;
}

//////////////////////////////////////////////////////////////////////////
//
// void SetMaxFrame() : 선택한 씬의 프레임을 설정하고 이에 따른 모든 저장장소의 크기를 할당한다.
//
// 인자값 : M_Uint32 Manager	  - 프레임메니져
//          M_Char* name		  - 씬의 이름(키)
//          M_Int32 maxFrame	  - 해당 씬의 전체 프레임 수
//          
// 반환값 : 없음
//
void SetMaxFrame(FrameManager* Manager, M_Int32 maxFrame)
{
	
	getFrameManagerPtr(Manager);
	
	Manager->scene->maxFrame = maxFrame;
	
	Manager->scene->maxElementOfFrameID		= MC_knlCalloc(sizeof(M_Int32) * maxFrame);
	//Manager->scene->maxElementOfFrame		= (M_Int32*)MC_GETDPTR(Manager->scene->maxElementOfFrameID);
	Manager->scene->elementListOfFrameID	= MC_knlCalloc(sizeof(M_Uint32) * maxFrame);
	Manager->scene->frameIntervalXID		= MC_knlCalloc(sizeof(M_Uint32) * maxFrame);
	Manager->scene->frameIntervalYID		= MC_knlCalloc(sizeof(M_Uint32) * maxFrame);
	Manager->scene->ImageIntervalXID		= MC_knlCalloc(sizeof(M_Uint32) * maxFrame);
	Manager->scene->ImageIntervalYID		= MC_knlCalloc(sizeof(M_Uint32) * maxFrame);
	Manager->scene->ImageWidthID			= MC_knlCalloc(sizeof(M_Uint32) * maxFrame);
	Manager->scene->ImageHeightID			= MC_knlCalloc(sizeof(M_Uint32) * maxFrame);
	Manager->scene->layerID					= MC_knlCalloc(sizeof(M_Uint32) * maxFrame);
	Manager->scene->frameTimeID				= MC_knlCalloc(sizeof(M_Int32) * maxFrame);
	
	frameIdx = -1;
}

//////////////////////////////////////////////////////////////////////////
//
// void setMaxElementOfFrame() : 생성된  씬의 프레임을 지정하지 않고 순처적으로 프레임을 구성하는 요소의 최대 개수를 설정한다.
//
// 인자값 : FrameManager* Manager - 프레임 메니져
//			M_Int32 maxElement - 최대 요수 수
//          M_Int32 frameTime  - 프레임 시간
//          
// 반환값 : 없음
//
void setMaxElementOfFrame(FrameManager* Manager, M_Int32 maxElement, M_Int32 frameTime)
{
	setMaxElementOfFrame2(Manager, frameIdx+1, maxElement, frameTime);
	frameIdx++;
}

//////////////////////////////////////////////////////////////////////////
//
// void setMaxElementOfFrame2() : 생성된 씬의 프레임을 지정하여 프레임을 구성하는 요소의 최대 개수를 설정한다.
//
// 인자값 : FrameManager* Manager	- 프레임 메니져
//          M_Int32 frameIdx		- 설정 프레임
//          M_Int32 maxElement		- 프레임메니져
//          M_Int32 frameTime		- 씬의 이름(키)
//          
// 반환값 : 없음
//
void setMaxElementOfFrame2(FrameManager* Manager, M_Int32 frameIdx, M_Int32 maxElement, M_Int32 frameTime)
{
	getFrameManagerPtr(Manager);
	
	Manager->scene->maxElementOfFrame	= (M_Int32*)MC_GETDPTR(Manager->scene->maxElementOfFrameID);
	Manager->scene->elementListOfFrame	= (M_Uint32*)MC_GETDPTR(Manager->scene->elementListOfFrameID);
	Manager->scene->frameIntervalX		= (M_Uint32*)MC_GETDPTR(Manager->scene->frameIntervalXID);
	Manager->scene->frameIntervalY		= (M_Uint32*)MC_GETDPTR(Manager->scene->frameIntervalYID);
	Manager->scene->ImageIntervalX		= (M_Uint32*)MC_GETDPTR(Manager->scene->ImageIntervalXID);
	Manager->scene->ImageIntervalY		= (M_Uint32*)MC_GETDPTR(Manager->scene->ImageIntervalYID);
	Manager->scene->ImageWidth			= (M_Uint32*)MC_GETDPTR(Manager->scene->ImageWidthID);
	Manager->scene->ImageHeight			= (M_Uint32*)MC_GETDPTR(Manager->scene->ImageHeightID);
	Manager->scene->layer				= (M_Uint32*)MC_GETDPTR(Manager->scene->layerID);
	Manager->scene->frameTime			= (M_Int32*)MC_GETDPTR(Manager->scene->frameTimeID);
	
	Manager->scene->maxElementOfFrame[frameIdx] = maxElement;
	//*(Manager->scene->maxElementOfFrame + frameIdx) = maxElement;
	Manager->scene->frameTime[frameIdx]	= frameTime;
	
	Manager->scene->elementListOfFrame[frameIdx] =  MC_knlCalloc(sizeof(M_Int32) * maxElement);
	Manager->scene->frameIntervalX[frameIdx]	 =  MC_knlCalloc(sizeof(M_Int32) * maxElement);
	Manager->scene->frameIntervalY[frameIdx]	 =  MC_knlCalloc(sizeof(M_Int32) * maxElement);
	Manager->scene->ImageIntervalX[frameIdx]	 =  MC_knlCalloc(sizeof(M_Int32) * maxElement);
	Manager->scene->ImageIntervalY[frameIdx]	 =  MC_knlCalloc(sizeof(M_Int32) * maxElement);
	Manager->scene->ImageWidth[frameIdx]		 =  MC_knlCalloc(sizeof(M_Int32) * maxElement);
	Manager->scene->ImageHeight[frameIdx]		 =  MC_knlCalloc(sizeof(M_Int32) * maxElement);
	Manager->scene->layer[frameIdx]				 =  MC_knlCalloc(sizeof(M_Int32) * maxElement);
	elementIdx = 0;
	elementframeIdx = frameIdx;	
}

//////////////////////////////////////////////////////////////////////////
//
// void setMaxElementOfFrame() : 프레임의 요소를 추가한다.
//
// 인자값 : M_Uint32 Manager		- 프레임 메니져 이름
//			M_Int32 imageIdx		- 이미지 번호(이미지 ID)
//          M_Int32 frameIntervalX  - 기준점으로부터 X축으로 이동하여 출력할 값
//			M_Int32 frameIntervalY	- 기준점으로부터 Y축으로 이동하여 출력할 값
//			M_Int32 imageIntervalX	- 이미지의 X축
//			M_Int32 imageIntervalY	- 이미지의 Y축
//			M_Int32 w				- 이미지의 넓이
//			M_Int32 h				- 이미지의 높이
//			M_Int32 layer			- 프레임의 레이어
//          
// 반환값 : 없음
//
void addElementOfFrame(FrameManager* Manager, M_Int32 imageIdx, M_Int32 frameIntervalX, M_Int32 frameIntervalY,
					   M_Int32 imageIntervalX, M_Int32 imageIntervalY, M_Int32 w, M_Int32 h, M_Int32 layer)
{
	addElementOfFrame2(Manager, elementframeIdx, elementIdx, imageIdx, frameIntervalX, frameIntervalY, 
		imageIntervalX, imageIntervalY, w, h, layer);
	elementIdx++;
}

//////////////////////////////////////////////////////////////////////////
//
// void setMaxElementOfFrame2() : 프레임의 요소를 추가한다.
//
// 인자값 :M_Uint32 Manager			- 프레임 메니져 이름
//			M_Int32 frameIdx		- 추가하려는 요소를 소유한 프레임번호
//			M_Int32 elementIdx		- 추가하려는 요소의 위치
//			M_Int32 imageIdx		- 이미지 번호
//			M_Int32 frameIntervalX	- 기준점으로부터 X축으로 이동하여 출력할 값
//			M_Int32 frameIntervalY	- 기준점으로부터 Y축으로 이동하여 출력할 값
//			M_Int32 imageIntervalX	- 이미지의 X축
//			M_Int32 imageIntervalY	- 이미지의 Y축
//			M_Int32 w				- 이미지의 넓이
//			M_Int32 h				- 이미지의 높이
//			M_Int32 layer			- 프레임의 레이어
//          
// 반환값 : 없음
//
void addElementOfFrame2(FrameManager* Manager, M_Int32 frameIdx, M_Int32 elementIdx, M_Int32 imageIdx,
						M_Int32 frameIntervalX, M_Int32 frameIntervalY,
						M_Int32 imageIntervalX, M_Int32 imageIntervalY, M_Int32 w, M_Int32 h, M_Int32 layer)
{
	M_Int32* temp;
	getFrameManagerPtr(Manager);
	
	Manager->scene->maxElementOfFrame	= (M_Int32*)MC_GETDPTR(Manager->scene->maxElementOfFrameID);
	Manager->scene->elementListOfFrame	= (M_Uint32*)MC_GETDPTR(Manager->scene->elementListOfFrameID);
	Manager->scene->frameIntervalX		= (M_Uint32*)MC_GETDPTR(Manager->scene->frameIntervalXID);
	Manager->scene->frameIntervalY		= (M_Uint32*)MC_GETDPTR(Manager->scene->frameIntervalYID);
	Manager->scene->ImageIntervalX		= (M_Uint32*)MC_GETDPTR(Manager->scene->ImageIntervalXID);
	Manager->scene->ImageIntervalY		= (M_Uint32*)MC_GETDPTR(Manager->scene->ImageIntervalYID);
	Manager->scene->ImageWidth			= (M_Uint32*)MC_GETDPTR(Manager->scene->ImageWidthID);
	Manager->scene->ImageHeight		= (M_Uint32*)MC_GETDPTR(Manager->scene->ImageHeightID);
	Manager->scene->layer				= (M_Uint32*)MC_GETDPTR(Manager->scene->layerID);
	
	temp = (M_Int32*)MC_GETDPTR(Manager->scene->elementListOfFrame[frameIdx]);
	temp[elementIdx] = imageIdx;
	
	temp = (M_Int32*)MC_GETDPTR(Manager->scene->frameIntervalX[frameIdx]);
	temp[elementIdx] = frameIntervalX;
	
	temp = (M_Int32*)MC_GETDPTR(Manager->scene->frameIntervalY[frameIdx]);
	temp[elementIdx] = frameIntervalY;
	
	temp = (M_Int32*)MC_GETDPTR(Manager->scene->ImageIntervalX[frameIdx]);
	temp[elementIdx] = imageIntervalX;
	
	temp = (M_Int32*)MC_GETDPTR(Manager->scene->ImageIntervalY[frameIdx]);
	temp[elementIdx] = imageIntervalY;
	
	temp = (M_Int32*)MC_GETDPTR(Manager->scene->ImageWidth[frameIdx]);
	temp[elementIdx] = w;
	
	temp = (M_Int32*)MC_GETDPTR(Manager->scene->ImageHeight[frameIdx]);
	temp[elementIdx] = h;
	
	temp = (M_Int32*)MC_GETDPTR(Manager->scene->layer[frameIdx]);
	temp[elementIdx] = layer;
	
}


//////////////////////////////////////////////////////////////////////////
//
// void setFirstFrame() : 현재 씬의 프레임을 첫 프레임으로 설정한다.
//
// 인자값 : M_Uint32 Manager	- 해당 프레임 매니져
//          
// 반환값 : 없음
//
void setFirstFrame(FrameManager* Manager)
{
	
	getFrameManagerPtr(Manager);
	
	Manager->curFrame = 0;
	Manager->bFrameOnceCompleted = 0;
		Manager->FrameTime=MC_knlCurrentTime();
}

//////////////////////////////////////////////////////////////////////////
//
// void setLastFrame() : 현재 씬의 프레임을 마지막 프레임으로 설정한다.
//
// 인자값 : M_Uint32 Manager	- 해당 프레임 매니져
//          
// 반환값 : 없음
//
void setLastFrame(FrameManager* Manager)
{
	getFrameManagerPtr(Manager);
	
	Manager->curFrame = Manager->scene->maxFrame - 1;
		Manager->FrameTime=MC_knlCurrentTime();

}


//////////////////////////////////////////////////////////////////////////
//
// void nextFrame() : 현재 씬의 프레임을 증가시켜 다음 프레임으로 설정한다.
//
// 인자값 : M_Uint32 Manager	- 해당 프레임 매니져
//          
// 반환값 : 없음
//
void nextFrame(FrameManager* Manager)
{
	getFrameManagerPtr(Manager);
	
	if(MC_knlCurrentTime()-Manager->FrameTime < Manager->scene->frameTime[Manager->curFrame])
		return;

	Manager->curFrame += 1;
	
	if(Manager->curFrame >= Manager->scene->maxFrame)
	{
		Manager->curFrame = 0;
		Manager->bFrameOnceCompleted = 1;
	}
	Manager->FrameTime=MC_knlCurrentTime();
}


//////////////////////////////////////////////////////////////////////////
//
// M_Int32 getMaxFrame() : 현재 씬의 최대 프레임의 수를 반환한다.
//
// 인자값 : M_Uint32 Manager	- 해당 프레임 매니져
//          
// 반환값 : 없음
//
M_Int32 getMaxFrame(FrameManager* Manager)
{
	getFrameManagerPtr(Manager);
	
	return Manager->scene->maxFrame;
}


//////////////////////////////////////////////////////////////////////////
//
// M_Int32 getLayer() : 현재 씬의 레이어를 반환한다.
//
// 인자값 : M_Uint32 Manager	- 해당 프레임 매니져
//          
// 반환값 : 없음
//
M_Int32 getLayer(FrameManager* Manager)
{
	getFrameManagerPtr(Manager);
	
	return *(Manager->scene->layer);
}


//////////////////////////////////////////////////////////////////////////
//
// M_Int32 getCurFrame() : 현재 씬의 프레임을 반환한다.
//
// 인자값 : M_Uint32 Manager	- 해당 프레임 매니져
//          
// 반환값 : 없음
//
M_Int32 getCurFrame(FrameManager* Manager)
{
	getFrameManagerPtr(Manager);
	
	return Manager->curFrame;
}

void getFrameManagerPtr(FrameManager* Manager)
{
	if(Manager->HeadID == 0)
		Manager->Head = NULL;
	else
		Manager->Head = (SceneList*)MC_GETDPTR(Manager->HeadID);
	if(Manager->RearID == 0)
		Manager->Rear = NULL;
	else
		Manager->Rear = (SceneList*)MC_GETDPTR(Manager->RearID);
	if(Manager->sceneID == 0)
		Manager->scene = NULL;
	else
		Manager->scene = (Scene*)MC_GETDPTR(Manager->sceneID);	
}

Scene* getScenePtr(M_Uint32 ID)
{
	return (Scene*)MC_GETDPTR(ID);
}