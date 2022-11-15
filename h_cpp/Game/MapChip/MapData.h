#pragma once

#include <vector>
#include <DirectXMath.h>
#include "Object3d.h"
#include "Model.h"
#include "MapChip.h"
#include "DirectXCommon.h"
#include "WinApp.h"

using namespace std;

class MapData
{
public:
	vector<vector<vector<MapChip>>> mapdata;
	vector<vector<vector<MapChip>>> startMapdata;

	//起動時のマップ
	static const int startMaxX = 0;
	static const int startMaxY = 0;
	static const int startMaxZ = 0;

public:
	MapData();
	~MapData();

	//マップサイズ保存
	int MaxX = 0;
	int MaxY = 0;
	int MaxZ = 0;

	//読込
	void LoadMap(vector<vector<vector<int>>> data, DirectX::XMINT3 size);

	static const int MaxBlock = 10;

	Object3d *objBlock[MaxBlock];
	Model *block = nullptr;
	DirectXCommon *dxCommon = nullptr;
	//描画
	void DrawMap();
	void Initilize();
};

