#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"

#include "WinApp.h"
#include "DirectXCommon.h"

using Microsoft::WRL::ComPtr;

class ImguiManager
{
private:

	ComPtr<ID3D12DescriptorHeap> _heapForImgui;

	HWND Hwnd;
	ID3D12GraphicsCommandList *Com;
	ID3D12Device *Dev;

	bool blnResult;

public:
	/// <summary>
	/// 初期化コンストラクタ
	/// </summary>
	ImguiManager(HWND hwnd, ID3D12GraphicsCommandList *com, ID3D12Device *_dev);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 描画前処理
	/// </summary>
	void CreateImGuiFrame();
};

