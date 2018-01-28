#include "Include.h"


M_Int32 frameIdx;	//�������� �߰��� �� �߰��Ǿ�� �� ���� ����Ų��.
M_Int32 elementframeIdx; //�������� ��Ұ� �߰��ɶ� ������
M_Int32 elementIdx; //�������� ��Ұ� �߰��Ǿ�� �� ���� ����Ų��.


//////////////////////////////////////////////////////////////////////////
//
// int addScene() : ������ �޴����� ���� �����Ѵ�.
//
// ���ڰ� : M_Uint32 Manager - ���Ե� ������ �޴����� ID��
//          M_Int32 name	 - ���Ե� ���� ������ȣ(Ű)
//
// ��ȯ�� : ����
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
		if(sceneNameComp((SceneList*)MC_GETDPTR(Manager->HeadID), name))	//�̹� ���Ե� ���� �̸��� �ߺ��ɶ� ���� �ߴ�
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
// M_Boolean sceneNameComp() : �ش� �����Ӹ޴����� ���� �̸��� ���� �����ϴ��� �����Ѵ�.
//
// ���ڰ� : SceneList* serchScene - ����� �����Ӹ޴����� ������Ʈ�� ó�� ��� �ּ�
//          M_Char* name		  - ���Ե� ���� �̸�(Ű)
//
// ��ȯ�� : true - ������ �̸� �߽߰�
//          false - ������ �̸� �߰߾��� ������ ������ �˻������
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
// void SetScene() : �ش� �����Ӹ޴����� ���� ���� �����Ѵ�.
//
// ���ڰ� : M_Uint32 Manager - ����� �����Ӹ޴���
//          M_Int32 name	 - ���õ� ���� ��ȣ(Ű)
//
// ��ȯ�� : ����
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
// void DrawFrame() : ���� ���� �������� ����Ѵ�.
//
// ���ڰ� : M_Uint32 Manager - ��µ� �����Ӹ޴���
//			M_Int32 x		 - ��µ� X��ǥ
//			M_Int32 y        - ��µ� Y��ǥ
//          
// ��ȯ�� : ����
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
// void delSceneElement() : ���õ� ���� �����޸𸮸� ��� �����Ѵ�.
//
// ���ڰ� : Scene* pScene - ���õ� ��
//          
// ��ȯ�� : ����
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
// void delScene() : ������ ���� �����Ӹ޴������� �����Ѵ�.
//
// ���ڰ� : M_Uint32 Manager - �ش� �����Ӹ޴���
//          M_Int32 name     - ������ ���� ��ȣ(Ű)
//          
// ��ȯ�� : ����
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
// void delAllScene() : ������ �����Ӹ޴����� ��� ���� �����Ѵ�.
//
// ���ڰ� : M_Uint32 Manager - ���õ� �����Ӹ޴���
//          
// ��ȯ�� : ����
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
// void SetMaxFrame() : ������ ���� �������� �����ϰ� �̿� ���� ��� ��������� ũ�⸦ �Ҵ��Ѵ�.
//
// ���ڰ� : M_Uint32 Manager	  - �����Ӹ޴���
//          M_Char* name		  - ���� �̸�(Ű)
//          M_Int32 maxFrame	  - �ش� ���� ��ü ������ ��
//          
// ��ȯ�� : ����
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
// void setMaxElementOfFrame() : ������  ���� �������� �������� �ʰ� ��ó������ �������� �����ϴ� ����� �ִ� ������ �����Ѵ�.
//
// ���ڰ� : FrameManager* Manager - ������ �޴���
//			M_Int32 maxElement - �ִ� ��� ��
//          M_Int32 frameTime  - ������ �ð�
//          
// ��ȯ�� : ����
//
void setMaxElementOfFrame(FrameManager* Manager, M_Int32 maxElement, M_Int32 frameTime)
{
	setMaxElementOfFrame2(Manager, frameIdx+1, maxElement, frameTime);
	frameIdx++;
}

//////////////////////////////////////////////////////////////////////////
//
// void setMaxElementOfFrame2() : ������ ���� �������� �����Ͽ� �������� �����ϴ� ����� �ִ� ������ �����Ѵ�.
//
// ���ڰ� : FrameManager* Manager	- ������ �޴���
//          M_Int32 frameIdx		- ���� ������
//          M_Int32 maxElement		- �����Ӹ޴���
//          M_Int32 frameTime		- ���� �̸�(Ű)
//          
// ��ȯ�� : ����
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
// void setMaxElementOfFrame() : �������� ��Ҹ� �߰��Ѵ�.
//
// ���ڰ� : M_Uint32 Manager		- ������ �޴��� �̸�
//			M_Int32 imageIdx		- �̹��� ��ȣ(�̹��� ID)
//          M_Int32 frameIntervalX  - ���������κ��� X������ �̵��Ͽ� ����� ��
//			M_Int32 frameIntervalY	- ���������κ��� Y������ �̵��Ͽ� ����� ��
//			M_Int32 imageIntervalX	- �̹����� X��
//			M_Int32 imageIntervalY	- �̹����� Y��
//			M_Int32 w				- �̹����� ����
//			M_Int32 h				- �̹����� ����
//			M_Int32 layer			- �������� ���̾�
//          
// ��ȯ�� : ����
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
// void setMaxElementOfFrame2() : �������� ��Ҹ� �߰��Ѵ�.
//
// ���ڰ� :M_Uint32 Manager			- ������ �޴��� �̸�
//			M_Int32 frameIdx		- �߰��Ϸ��� ��Ҹ� ������ �����ӹ�ȣ
//			M_Int32 elementIdx		- �߰��Ϸ��� ����� ��ġ
//			M_Int32 imageIdx		- �̹��� ��ȣ
//			M_Int32 frameIntervalX	- ���������κ��� X������ �̵��Ͽ� ����� ��
//			M_Int32 frameIntervalY	- ���������κ��� Y������ �̵��Ͽ� ����� ��
//			M_Int32 imageIntervalX	- �̹����� X��
//			M_Int32 imageIntervalY	- �̹����� Y��
//			M_Int32 w				- �̹����� ����
//			M_Int32 h				- �̹����� ����
//			M_Int32 layer			- �������� ���̾�
//          
// ��ȯ�� : ����
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
// void setFirstFrame() : ���� ���� �������� ù ���������� �����Ѵ�.
//
// ���ڰ� : M_Uint32 Manager	- �ش� ������ �Ŵ���
//          
// ��ȯ�� : ����
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
// void setLastFrame() : ���� ���� �������� ������ ���������� �����Ѵ�.
//
// ���ڰ� : M_Uint32 Manager	- �ش� ������ �Ŵ���
//          
// ��ȯ�� : ����
//
void setLastFrame(FrameManager* Manager)
{
	getFrameManagerPtr(Manager);
	
	Manager->curFrame = Manager->scene->maxFrame - 1;
		Manager->FrameTime=MC_knlCurrentTime();

}


//////////////////////////////////////////////////////////////////////////
//
// void nextFrame() : ���� ���� �������� �������� ���� ���������� �����Ѵ�.
//
// ���ڰ� : M_Uint32 Manager	- �ش� ������ �Ŵ���
//          
// ��ȯ�� : ����
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
// M_Int32 getMaxFrame() : ���� ���� �ִ� �������� ���� ��ȯ�Ѵ�.
//
// ���ڰ� : M_Uint32 Manager	- �ش� ������ �Ŵ���
//          
// ��ȯ�� : ����
//
M_Int32 getMaxFrame(FrameManager* Manager)
{
	getFrameManagerPtr(Manager);
	
	return Manager->scene->maxFrame;
}


//////////////////////////////////////////////////////////////////////////
//
// M_Int32 getLayer() : ���� ���� ���̾ ��ȯ�Ѵ�.
//
// ���ڰ� : M_Uint32 Manager	- �ش� ������ �Ŵ���
//          
// ��ȯ�� : ����
//
M_Int32 getLayer(FrameManager* Manager)
{
	getFrameManagerPtr(Manager);
	
	return *(Manager->scene->layer);
}


//////////////////////////////////////////////////////////////////////////
//
// M_Int32 getCurFrame() : ���� ���� �������� ��ȯ�Ѵ�.
//
// ���ڰ� : M_Uint32 Manager	- �ش� ������ �Ŵ���
//          
// ��ȯ�� : ����
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