#pragma once
#include "cGameManager.h"

class cNPC
{
	ID2D1Bitmap* NPC_Host;
	ID2D1Bitmap* NPC_Host_A;
	ID2D1Bitmap* NPC_Host_B;

	POINT NPC_HostPos;

	float Dis;

public:
	cNPC();
	~cNPC();

	int GetCrushOn(int a);
	int CrushOn;
	int SpeechDelay;
	float delta;

	int NPC_Host_Speech;
	void Update();
	void Render(cD2DRenderer& renderer);
	void SpeechRender(cD2DRenderer& renderer);
	void LoadImages(cD2DRenderer& renderer, HWND hWnd);
};

