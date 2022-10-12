#pragma once
#include <DirectXMath.h>
#include "d3dx12.h"

class Camera
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	Camera(int win_widht,int win_height);

	~Camera();

	virtual void Update();
	// ビュー行列を更新
	void UpdateViewMatrix();
	// 射影行列を更新
	void UpdateProjectionMatrix();
	// ビュー行列の取得
	inline const XMMATRIX &GetViewMatrix() {
		return matView;
	}
	// 射影行列の取得
	inline const XMMATRIX &GetProjectionMatrix() {
		return matProjection;
	}
	// ビュー射影行列の取得
	inline const XMMATRIX &GetViewProjectionMatrix() {
		return matViewProjection;
	}
	// ビルボード行列の取得
	inline const XMMATRIX &GetBillboardMatrix() {
		return matBillboard;
	}
	// 視点座標の取得
	inline const XMFLOAT3 &GetEye() {
		return eye;
	}
	// 視点座標の設定
	inline void SetEye(XMFLOAT3 eye) {
		this->eye = eye; viewDirty = true;
	}
	// 注視点座標の取得
	inline const XMFLOAT3 &GetTarget() {
		return target;
	}
	// 注視点座標の設定
	inline void SetTarget(XMFLOAT3 target) {
		this->target = target; viewDirty = true;
	}
	// 上方向ベクトルの取得
	inline const XMFLOAT3 &GetUp() {
		return up;
	}
	// 上方向ベクトルの設定
	inline void SetUp(XMFLOAT3 up) {
		this->up = up; viewDirty = true;
	}

	/// ベクトルによる視点移動
	void MoveEyeVector(const XMFLOAT3 &move);
	void MoveEyeVector(const XMVECTOR &move);
	// ベクトルによる移動
	void MoveVector(const XMFLOAT3 &move);
	void MoveVector(const XMVECTOR &move);
	

private://メンバ変数
	// 視点座標
	//XMFLOAT3 eye = { 0, 20, -500 };
	XMFLOAT3 eye = { 0, -0, 0 };
	
	// 注視点座標
	XMFLOAT3 target = { 0, 0, 1 };
	// 上方向ベクトル
	XMFLOAT3 up = { 0, 1,0 };
	// ビュー行30列
	XMMATRIX matView = DirectX::XMMatrixIdentity();
	// ビルボード行列
	XMMATRIX matBillboard = DirectX::XMMatrixIdentity();
	// Y軸回りビルボード行列
	XMMATRIX matBillboardY = DirectX::XMMatrixIdentity();
	// 射影行列
	XMMATRIX matProjection = DirectX::XMMatrixIdentity();
	// ビュー射影行列
	XMMATRIX matViewProjection = DirectX::XMMatrixIdentity();
	// ビュー行列ダーティフラグ
	bool viewDirty = false;
	// 射影行列ダーティフラグ
	bool projectionDirty = false;
	// アスペクト比
	float aspectRatio = 1.0f;
};

