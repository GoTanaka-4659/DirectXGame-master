#pragma once
#include "SpriteCommon.h"
#include "Sprite.h"
#include "PipelineSet.h"
#include "WinApp.h"
#include "d3dx12.h"
#include "DirectXCommon.h"

class PostEffect :
	public Sprite
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
	PipelineSet *pipelineset;
	DirectXCommon *directXCommon;

	ComPtr<ID3D12Resource>texBuff[2];
	ComPtr<ID3D12DescriptorHeap>descHeapSRV;
	//深度バッファ
	ComPtr<ID3D12Resource>depthBuff;
	ComPtr<ID3D12DescriptorHeap>descHeapRTV;
	ComPtr<ID3D12DescriptorHeap>descHeapDSV;

	ComPtr<ID3D12PipelineState>pipelineState;
	ComPtr<ID3D12RootSignature>rootSignature;
public:
	PostEffect();

	void Draw(ID3D12GraphicsCommandList *cmdList, ID3D12Device *device);

	void Initialize(ID3D12Device *device);

	void PreDrawScene(ID3D12GraphicsCommandList *cmdList, ID3D12Device *device);
	void PostDrawScene(ID3D12GraphicsCommandList *cmdList);

	//パイプライン生成
	void CreateGraphicsPipelineState(ID3D12Device *device);
private:
	static const float clearColor[4];
};

