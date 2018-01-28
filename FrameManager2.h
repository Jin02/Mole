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
* �������� ���� �����ϱ� ���� ���Ḯ��Ʈ�� ���� ��带 ����
*/
typedef struct _SceneList{
	M_Uint32 listID;			//����Ʈ�� ID
	M_Int32  No;				//���� ��ȣ
	
	M_Uint32 sceneID;			//���� ID
	Scene* scene;				//������ ���� �ּҰ� ����
	
	M_Uint32 PreLinkID;			//���� ���� ���� ����Ʈ�� ����� ���� ��ũ
	M_Uint32 NextLinkID;
}SceneList;

/*
* ���� ���� �� ���� ������ ����� ���� ������ ������ �ִ� ����ü
*/
typedef struct _FrameManager{
	M_Int32 sceneID;			//���� Ȱ��ȸ�� ���� ID
	Scene* scene;				//���� Ȱ��ȭ�� ��
	
	M_Int32 HeadID;				//�� ����Ʈ�� ���� ���� ID 
	M_Int32 RearID;				//�� ����Ʈ�� ������ ���� ID
	
	SceneList* Head;			//�� ����Ʈ�� ���� �� 
	SceneList* Rear;			//�� ����Ʈ�� ������ ��
	
	M_Int32 curFrame;			//������ Ȱ��ȭ�� �����ӹ�ȣ
	M_Boolean bFrameOnceCompleted; //���� �ִϸ��̼��� �ѹ��̻� �ݺ��Ǿ����� Ȯ���ϱ� ���� ����

	M_Int64 FrameTime;//��µ� ������ �ð� ���


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