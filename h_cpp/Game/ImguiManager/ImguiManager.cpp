#include "ImguiManager.h"

ImguiManager::ImguiManager(HWND hwnd, ID3D12GraphicsCommandList *com, ID3D12Device *_dev)
{
	Hwnd = hwnd;
	Com = com;
	Dev = _dev;


	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	desc.NodeMask = 0;
	desc.NumDescriptors = 1;
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	Dev->CreateDescriptorHeap(
		&desc, IID_PPV_ARGS(_heapForImgui.ReleaseAndGetAddressOf()));

	if (ImGui::CreateContext() == nullptr) {
		assert(0);
	}

	blnResult = ImGui_ImplWin32_Init(Hwnd);
	if (!blnResult)
	{
		assert(0);
	}

		
	blnResult = ImGui_ImplDX12_Init(
		Dev,
		3,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		_heapForImgui.Get(),
		_heapForImgui.Get()->GetCPUDescriptorHandleForHeapStart(),//CPUハンドル
		_heapForImgui.Get()->GetGPUDescriptorHandleForHeapStart()//GPUハンドル
	);
}

void ImguiManager::CreateImGuiFrame()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImguiManager::Draw()
{
	ImGui::Render();

	Com->SetDescriptorHeaps(
		1, _heapForImgui.GetAddressOf());
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), Com);
}

