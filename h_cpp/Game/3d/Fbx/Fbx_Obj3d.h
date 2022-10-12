#pragma once

#include "FBX_Model.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>

#include "Camera.h"

class Fbx_Obj3d
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
	//デバイス
	static ID3D12Device *device;
	//カメラ
	static Camera *camera;
private:
	//定数バッファ
	ComPtr<ID3D12Resource> constBuffTransform;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static	ComPtr<ID3D12PipelineState> pipelinestate;

	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	// ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	//モデル
	FBXModel *model = nullptr;
	//ボーンの最大値
	static const int MAX_BONES = 32;
	//定数バッファ(スキン)
	ComPtr<ID3D12Resource> constBuffSkin;
	//1フレームの時間
	FbxTime frameTime;
	//アニメーション開始時間
	FbxTime startTime;
	//アニメーション終了時間
	FbxTime endTime;
	//現在時間(アニメーション)
	FbxTime currentTime;
	//アニメーション再生中
	bool isPlay = false;

public://サブクラス
	//定数バッファ用データ構造体（座標返還利用）
	// 定数バッファ用データ構造体B0
	struct ConstBufferDataB0
	{
		XMMATRIX viewproj;    // ビュープロジェクション行列
		XMMATRIX world; // ワールド行列
		XMFLOAT3 cameraPos;//カメラ座標
	};
	// 定数バッファ用データ構造体（スキニング）
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};

public: // 静的メンバ関数
	//setter
	static void SetDevice(ID3D12Device *device) { Fbx_Obj3d::device = device; }
	static void SetCamera(Camera *camera) { Fbx_Obj3d::camera = camera; }
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }
	void SetPosition(XMFLOAT3 position) { this->position = position; }
public://メンバ関数
	//初期化
	void Initilize();
	//更新
	void Update();
	//描画
	void Draw(ID3D12GraphicsCommandList *cmdList);
	//モデルセット
	void SetModel(FBXModel *model) { this->model = model; }
	//グラフィックスパイプラインの生成
	static void CreateGraphicsPipeline();
	//アニメーション開始
	void PlayAnimetion();
};

