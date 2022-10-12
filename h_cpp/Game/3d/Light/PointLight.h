//#pragma once
//
//#include <DirectXMath.h>
//
/////点光源
//class PointLight
//{
//private: // エイリアス
//// Microsoft::WRL::を省略
//	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
//	// DirectX::を省略
//	using XMFLOAT2 = DirectX::XMFLOAT2;
//	using XMFLOAT3 = DirectX::XMFLOAT3;
//	using XMFLOAT4 = DirectX::XMFLOAT4;
//	using XMMATRIX = DirectX::XMMATRIX;
//public://サブクラス
//	//定数バッファ用データ構造体
//	struct ConstBufferData
//	{
//		XMFLOAT3 lightpos;
//		float pad1;
//		XMFLOAT3 lightcolor;
//		float pad2;
//		XMFLOAT3 lightatten;
//		unsigned int active;
//	};
//public://メンバ関数
//	inline void SetLightPos(const XMFLOAT3 &lightpos) { this->lightpos = lightpos; }
//	inline const XMFLOAT3 &SetLightPos() { return lightpos; }
//	inline void SetLightColor(const XMFLOAT3 &lightcolor) { this->lightpos = lightcolor; }
//	inline const XMFLOAT3 &SetLightColor() { return lightcolor; }
//	inline void SetLightAtten(const XMFLOAT3 &lightAtten) { this->lightAtten = lightAtten; }
//	inline const XMFLOAT3 &SetLightAtten() { return lightAtten; }
//	inline void SetActive(bool active) { this->active = active; }
//	inline bool IsActive() { return active; }
//
//private://メンバ変数
//	//ライト座標（ワールド座標）
//	XMFLOAT3 lightpos = { 0,0,0 };
//	//ライト色
//	XMFLOAT3 lightcolor = { 1,1,1 };
//	//ライト距離減衰係数
//	XMFLOAT3 lightAtten = { 1.0f,1.0f,1.0f };
//	//有効フラグ
//	bool active = false;
//};
//
