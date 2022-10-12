#include <Windows.h>
#include "DirectXTex.h"

#include <fstream>

#include "MasterGame.h"

//using namespace DirectX;
//using namespace Microsoft::WRL;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	HRESULT result;
	Framework* game = new MasterGame();

	game->Run();

	delete game;

	return 0;
}