#ifndef __WING_H__
#define __WING_H__

typedef struct _Mole{

	M_Int64 StartTime;
	M_Int64 PlayTime;
	M_Int32 CC;
	M_Int32 AI[225];
	M_Int32 Pl[225];

	M_Int32 OneStageone[3];
	M_Int32 OneStagetwo[4];
	M_Int32 TwoStageone[5];
	M_Int32 TwoStagetwo[6];
	M_Int32 ThreeStageone[7];
	M_Int32 ThreeStagetwo[8];
	M_Int32 FourStageone[9];
	M_Int32 FourStagetwo[10];

	M_Int32 OneStagePlayone[3];
	M_Int32 OneStagePlaytwo[4];
	M_Int32 TwoStagePlayone[5];
	M_Int32 TwoStagePlaytwo[6];
	M_Int32 ThreeStagePlayone[7];
	M_Int32 ThreeStagePlaytwo[8];
	M_Int32 FourStagePlayone[9];
	M_Int32 FourStagePlaytwo[10];

	M_Int32 GamePlayChecking;
	M_Int64 AiTime;
	M_Int64 PlTime;
	M_Int64 ChTime;
	M_Int32 Changing;
	//

}MOLE;

void WingFC();
void Winglnit();
void WingDraw();
void WingUpdate();
void ReadyDraw();
void ReadyKey(M_Int32 Key);
void PlayKeyoff(M_Int32 Key);
void PlayKey(M_Int32 Key);
void WingDestroy();
void iAi();
M_Int32 GetRand(M_Int32 min,M_Int32 max);
void DrawFillRect();
void CountSystem();
void GettingString();
void Stagenumber();
void PlayerCheck();
void switchgamespeed();
void TrueandFalseCheck();
void zeroCheck();
void PLUScheck();

#endif