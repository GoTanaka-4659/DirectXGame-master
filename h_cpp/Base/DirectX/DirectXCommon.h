#pragma once

#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"

//DirectX基盤
class DirectXCommon
{
private:
	//デバイス
	Microsoft::WRL::ComPtr<ID3D12Device>dev;
	//DxGIファクトリー
	Microsoft::WRL::ComPtr<IDXGIFactory6> dxgiFactory;
	//コマンドアロケータ
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
	//コマンドリスト
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;
	//コマンドキュー
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> cmdQueue;
	//スワップチェーン
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchain;
	//
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	//
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;
	//バックバッファ
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;

	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer;
	//WindowsAPI
	WinApp *winApp ;

	// フェンスの生成
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;

	UINT64 fenceVal = 0;
private:
	//デバイスの初期化
	void InitilizeDevice();
	//コマンド関連の初期化
	void InitializeCommand();
	//スワップチェーンの初期化
	void InitilizeSwapchain();
	//レンダーターゲットビューの初期化
	void InitializeRenderTargetView();
	//深度バッファの初期化
	void InitilizeDepthBuffer();
	//フェンスの初期化
	void InitilizeFence();

public://メンバ関数
	//初期化
	void Initialize(WinApp *winApp);
	//描画処理前
	void PreDraw();
	//描画後処理
	void PostDraw();
	//デバイス取得
	//Microsoft::WRL::ComPtr<ID3D12Device>GetDev() { return dev; }
	ID3D12Device *GetDev() { return dev.Get(); }
	//コマンドリスト取得
	ID3D12GraphicsCommandList *GetCmdList() { return cmdList.Get(); }
};

