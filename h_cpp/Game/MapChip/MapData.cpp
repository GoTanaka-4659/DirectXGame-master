#include "MapData.h"

MapData::MapData()
{
	for (int i = 0; i <= MaxBlock; i++) {
		objBlock[MaxBlock] = nullptr;
	}
}

MapData::~MapData()
{
}

void MapData::LoadMap(vector<vector<vector<int>>> data, DirectX::XMINT3 size)
{
	mapdata.clear();
	startMapdata.clear();

	MaxX = size.x;
	MaxY = size.y;
	MaxZ = size.z;

	mapdata.resize(MaxX);

	for (int x = 0; x < MaxX; ++x)
	{
		mapdata[x].resize(MaxY);
		for (int y = 0; y < MaxY; ++y)
		{
			mapdata[x][y].resize(MaxZ);
		}
	}

	startMapdata.resize(MaxX);
	for (int x = 0; x < MaxX; ++x) 
	{
		startMapdata[x].resize(MaxY);
		for (int y = 0; y < MaxY; ++y)
		{
			startMapdata[x][y].resize(MaxZ);
		}
	}
	for (int x = 0; x < MaxX; x++) {
		for (int y = 0; y < MaxY; y++) {
			for (int z = 0; z < MaxZ; z++) {
				startMapdata[x][y][z].chipType = mapdata[x][y][z].chipType;
			}
		}
	}
}

void MapData::DrawMap()
{
	for (int i = 0; i <= MaxBlock; i++) {
		objBlock[MaxBlock]->Draw();
	}
}

void MapData::Initilize()
{
	//モデル
	const std::string objname = "Cube";
	//OBJからモデルデータを読み込む
	block = Model::LoadFromOBJ(dxCommon->GetDev(), objname);

	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::Window_width, WinApp::Window_height);
	//3Dオブジェクト生成
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::Window_width, WinApp::Window_height);
	for (int i = 0; i <= MaxBlock; i++) {
		objBlock[MaxBlock] = Object3d::Create();
		objBlock[MaxBlock]->SetModel(block);
		objBlock[MaxBlock]->SetPosition({ 0,0,0 });
		objBlock[MaxBlock]->SetPosition({ 0.001,0.001,0.001 });
	}
}
