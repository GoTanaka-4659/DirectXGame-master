#pragma once
#include <windows.h>
#include <wrl.h>

#define DIRECTINPUT_VERSION	0x0800//DirectInputのバージョン指定
#include <dinput.h>
#include "WinApp.h"

class Input
{
public:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	//初期化
	void Initilize(WinApp* winapp);
	//更新
	void Update();

	bool PushKey(BYTE keyNo);	
	bool TriggerKey(BYTE keyNo);

private://メンバ変数
	//DirectInputのインスタンス生成
	ComPtr<IDirectInput8> dinput = nullptr;
	//キーボードのデバイス
	ComPtr<IDirectInputDevice8>devkeyboard;
	//全キーの状態
	BYTE key[256] = {};
	//前回の全キーの状態
	BYTE keyPre[256] = {};
	//WindowsAPI
	WinApp *winApp = nullptr;
};

