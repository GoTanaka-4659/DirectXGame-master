#pragma once
#include <DirectXMath.h>
#include "PipelineSet.h"

class SpriteCommon
{
public://メンバ関数
	//初期化
	void Initilize(ID3D12Device *dev, ID3D12GraphicsCommandList *commandList,int window_width, int window_height);
	//描画前処理
	void PreDraw();

	//テクスチャ読み込み
	void LoadTexture(UINT texnumber, const wchar_t *filename);

	void SetGraphicsRootDescriptorTable(UINT rootParameterIndex,UINT texNumber);
public:
	//テクスチャの最大枚数
	static const int spriteSRVCount = 512;

	//テクスチャリソース
	ID3D12Resource *GetTexBuff(int texnum);

	ID3D12Device *GetDevice() { return device; }

	const DirectX::XMMATRIX &GetMatProjection() { return matProjection; }

	ID3D12GraphicsCommandList *GetCommandList() { return cmdList; }
private:
	// パイプラインセット
	PipelineSet pipelineSet;
	// 射影行列
	DirectX::XMMATRIX matProjection{};
	// テクスチャ用デスクリプタヒープの生成
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
	// テクスチャリソース（テクスチャバッファ）の配列
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff[spriteSRVCount];
	//デバイス
	ID3D12Device *device = nullptr;
	//コマンドリスト
	ID3D12GraphicsCommandList *cmdList = nullptr;
private:
	//パイプライン生成
	void CreateGraphicsPipeline();
};

