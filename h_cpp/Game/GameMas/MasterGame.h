#pragma once

#include "Framework.h"
//#include "Fbx_Obj3d.h"

#include <vector>
#include "PostEffect.h"



class MasterGame : public Framework
{
private://エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	std::vector<Sprite *>sprites;
	PostEffect *postEffect = nullptr;

	Sprite *title = nullptr;
	Sprite *end = nullptr;
	
	float x = 0, y = 0.5, z = 1;
	bool jumping=false;
	float jump=0;

	int Scene = 0;
public:
	void Initilize() override;
	void Update()override;
	void Draw();
	void Finalize()override;
};
