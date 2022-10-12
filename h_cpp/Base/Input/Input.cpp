#include "Input.h"
#include <cassert>

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib,"dxguid.lib")

void Input::Initilize(WinApp* winApp)
{
	HRESULT result;
	//NULL検出
	assert(winApp);
	//WinAppのインスタンスを記録
	this->winApp = winApp;
	
	result = DirectInput8Create(winApp->GetHinstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&dinput, nullptr);
	
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	//入力データ形式のセット
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);
	//排他制御レベルのセット
	result = devkeyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

}

void Input::Update()
{
	HRESULT result;


	//キーボード情報の取得開始
	result = devkeyboard->Acquire();
	//前回のキー入力を保存
	memcpy(keyPre, key, sizeof(key));
	
	result = devkeyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNo)
{
	//指定キーを押していればtrue
	if (key[keyNo]) {
		return true;
	}
	//それ以外false
	return false;
}

bool Input::TriggerKey(BYTE keyNo)
{
	if (keyPre[keyNo] == false && key[keyNo]) {
		return true;
	}
	return false;
}


