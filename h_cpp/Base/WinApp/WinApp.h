#pragma once
#include <windows.h>

class WinApp
{
public://静的メンバ関数
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public://定数
	//ウィンドウ横幅
	static const int Window_width = 1280;
	//ウィンドウ縦幅
	static const int Window_height = 720;

public://メンバ関数
	//初期化
	void Initilize();
	//更新
	void Update();
	//終了
	void Finalize();
	//メッセージの処理
	bool ProcessMessage();
public:
	//getter
	HWND GetHwnd() { return hwnd; }
	HINSTANCE GetHinstance() { return w.hInstance; }
private:
	//ウィンドウハンドル
	HWND hwnd = nullptr;
	//ウィンドウクラスの設定
	WNDCLASSEX w{};
};

