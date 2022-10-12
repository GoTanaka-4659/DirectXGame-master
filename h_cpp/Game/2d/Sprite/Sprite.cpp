#include "Sprite.h"
#include <d3dx12.h>

using namespace DirectX;

Sprite::Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY)
{
	this->position = position;
	this->size = size;
	this->anchorpoint = anchorpoint;
	this->matWorld = XMMatrixIdentity();
	this->color = color;
	this->texNumber = texNumber;
	this->isFlipX = isFlipX;
	this->isFlipY = isFlipY;
	this->texSize = size;
}

Sprite *Sprite::Create(SpriteCommon *spriteCommon, UINT texNum, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY)
{
	//メモリ確保
	Sprite *instance = new Sprite();
	//インスタンス初期化
	instance->Initialize(spriteCommon, texNum, anchorpoint, isFlipX, isFlipY);

	return instance;
}

Sprite::Sprite()
{
}

void Sprite::Initialize(SpriteCommon *spritecommon, UINT texNumber, XMFLOAT2 anchorpoint , bool isFlipX , bool isFlipY )
{
	HRESULT result = S_FALSE;

	spritecommon_ = spritecommon;
	// テクスチャ番号をコピー
	texNumber_ = texNumber;
	// アンカーポイントをコピー
	anchorpoint_ = anchorpoint;
	// 反転フラグをコピー
	isFlipX_ = isFlipX;
	isFlipY_ = isFlipY;

	// 頂点データ
	VertexPosUv vertices[4];

	// 指定番号の画像が読み込み済みなら
	if (spritecommon_->GetTexBuff(texNumber_)) {
		// テクスチャ情報取得
		D3D12_RESOURCE_DESC resDesc = spritecommon_->GetTexBuff(texNumber_)->GetDesc();

		// スプライトの大きさを画像の解像度に合わせる
		size_ = { (float)resDesc.Width, (float)resDesc.Height };
		texSize_ = { (float)resDesc.Width, (float)resDesc.Height };
	}

	// 頂点バッファ生成
	result = spritecommon_->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices)),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertBuff_));
	if (FAILED(result)) {
		assert(0);
	}
	// 頂点バッファデータ転送
	TransferVertexBuffer();

	// 頂点バッファビューの作成
	vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress();
	vbView_.SizeInBytes = sizeof(vertices);
	vbView_.StrideInBytes = sizeof(vertices[0]);

	// 定数バッファの生成
	result = spritecommon_->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff_));

	if (FAILED(result)) {
		assert(0);
	}

	// 定数バッファにデータ転送
	ConstBufferData *constMap = nullptr;
	result = constBuff_->Map(0, nullptr, (void **)&constMap);
	constMap->color = XMFLOAT4(1, 1, 1, 1); // 色指定（RGBA）
	constMap->mat = spritecommon_->GetMatProjection();
	constBuff_->Unmap(0, nullptr);
	if (FAILED(result)) {
		assert(0);
	}
}

void Sprite::TransferVertexBuffer()
{
	HRESULT result = S_FALSE;
	if (FAILED(result)) {
		assert(0);
	}

	// 頂点データ
	VertexPosUv vertices[] = {
		//     u     v
		{{}, {0.0f, 1.0f}}, // 左下
		{{}, {0.0f, 0.0f}}, // 左上
		{{}, {1.0f, 1.0f}}, // 右下
		{{}, {1.0f, 0.0f}}, // 右上
	};

	// 左下、左上、右下、右上
	enum { LB, LT, RB, RT };

	float left = (0.0f - anchorpoint_.x) * size_.x;
	float right = (1.0f - anchorpoint_.x) * size_.x;
	float top = (0.0f - anchorpoint_.y) * size_.y;
	float bottom = (1.0f - anchorpoint_.y) * size_.y;

	if (isFlipX_)
	{// 左右入れ替え
		left = -left;
		right = -right;
	}

	if (isFlipY_)
	{// 左右入れ替え
		top = -top;
		bottom = -bottom;
	}

	vertices[LB].pos = { left, bottom,  0.0f }; // 左下
	vertices[LT].pos = { left, top,     0.0f }; // 左上
	vertices[RB].pos = { right, bottom, 0.0f }; // 右下
	vertices[RT].pos = { right, top,    0.0f }; // 右上

	// 指定番号の画像が読み込み済みなら
	if (spritecommon_->GetTexBuff(texNumber_)) {
		// テクスチャ情報取得
		D3D12_RESOURCE_DESC resDesc = spritecommon_->GetTexBuff(texNumber_)->GetDesc();

		float tex_left = texLeftTop_.x / resDesc.Width;
		float tex_right = (texLeftTop_.x + texSize_.x) / resDesc.Width;
		float tex_top = texLeftTop_.y / resDesc.Height;
		float tex_bottom = (texLeftTop_.y + texSize_.y) / resDesc.Height;

		vertices[LB].uv = { tex_left,   tex_bottom }; // 左下
		vertices[LT].uv = { tex_left,   tex_top }; // 左上
		vertices[RB].uv = { tex_right,  tex_bottom }; // 右下
		vertices[RT].uv = { tex_right,  tex_top }; // 右上
	}

	// 頂点バッファへのデータ転送
	VertexPosUv *vertMap = nullptr;
	result = vertBuff_->Map(0, nullptr, (void **)&vertMap);
	if (SUCCEEDED(result)) {
		memcpy(vertMap, vertices, sizeof(vertices));
		vertBuff_->Unmap(0, nullptr);
	}
	vertBuff_->Unmap(0, nullptr);
}

void Sprite::Draw()
{
	if (isInvisible_) {
		return;
	}

	ID3D12GraphicsCommandList *cmdList = spritecommon_->GetCommandList();

	// 頂点バッファをセット
	cmdList->IASetVertexBuffers(0, 1, &vbView_);

	// 定数バッファをセット
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff_->GetGPUVirtualAddress());

	// シェーダリソースビューをセット
	spritecommon_->SetGraphicsRootDescriptorTable(1, texNumber_);

	// ポリゴンの描画（4頂点で四角形）
	cmdList->DrawInstanced(4, 1, 0, 0);
}

void Sprite::Update()
{
	// ワールド行列の更新
	matWorld_ = XMMatrixIdentity();
	// Z軸回転
	matWorld_ *= XMMatrixRotationZ(XMConvertToRadians(rotation_));
	// 平行移動
	matWorld_ *= XMMatrixTranslation(position_.x, position_.y, 0);

	// 定数バッファの転送
	ConstBufferData *constMap = nullptr;
	HRESULT result = constBuff_->Map(0, nullptr, (void **)&constMap);
	constMap->color = color_;
	constMap->mat = matWorld_ * spritecommon_->GetMatProjection();
	constBuff_->Unmap(0, nullptr);
}
