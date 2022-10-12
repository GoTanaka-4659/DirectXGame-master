#pragma once

#include "fbxsdk.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <string>
#include "FBX_Model.h"
#include "DirectXTex.h"
#include <DirectXMath.h>

class FbxLoader
{
private://エイリアス
	using string = std::string;
public://定数
//モデル格納ルートパス
//static const string baseDirectory;

/// <summary>
/// 静的メンバ変数の実態
/// </summary>
	const std::string FbxLoader::baseDirectory = "Resources/";

	//テクスチャがない場合の標準テクスチャファイル名
	static const std::string defaultTextureFileName;

public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader *GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device">D3D12デバイス</param>
	void Initilize(ID3D12Device *device);
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// ファイルからFBXモデルを読込
	/// </summary>
	/// <param name="modelName">モデル名</param>
	FBXModel* LoadModelFromFile(const string &modelName);
	//void LoadModelFromFile(const string &modelName);
	
	//FBXの行列をXMMatrixに変換
	static void ConvertMatrixFromFbx(DirectX::XMMATRIX *dst, const FbxAMatrix &src);

private:
	/// <summary>
	/// 再帰的にノード構成を解析
	/// </summary>
	/// <param name="model">読込先モデルオブジェクト</param>
	/// <param name="fbxNode">解析対象のノード</param>
	/// <param name="parent">親ノード</param>
	void ParseNodeRecursive(FBXModel *model, FbxNode *fbxNode, Node *parent = nullptr);

	/// <summary>
	/// メッシュ読み取り
	/// </summary>
	/// <param name="model">呼び込み先モデルオブジェクト</param>
	/// <param name="fbxNode">解析対象ノード</param>
	void ParseMesh(FBXModel *model, FbxNode *fbxNode);
	//頂点座標読み取り
	void ParseMeshVertices(FBXModel *model, FbxMesh *fbxMesh);
	//面情報読み取り
	void ParceMeshFaces(FBXModel *model, FbxMesh *fbxMesh);
	//マテリアル読み取り
	void ParceMaterial(FBXModel *model, FbxNode *fbxnode);
	//テクスチャ読み取り
	void LoadTexture(FBXModel *model, const std::string &fullpath);

private:
	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader &obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader &obj) = delete;

private:
	//ID3D12デバイス
	ID3D12Device *device = nullptr;
	//FBXマネージャ
	FbxManager *fbxManager = nullptr;
	//FBXインポータ
	FbxImporter *fbxImporter = nullptr;
	//ディレクトリを含んだファイルパスからファイル名を抽出する
	std::string ExtractFileName(const std::string &path);


public:

	//スキニング情報の読み取り
	void ParseSkin(FBXModel *model, FbxMesh *fbxmesh);
};