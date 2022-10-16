#include "MasterGame.h"

void MasterGame::Initilize()
{
	//基底クラスの初期化
	Framework::Initilize();

	// スプライト共通テクスチャ読み込み
	spriteCommon->LoadTexture(0, L"Resources/Gorushi.png");
	spriteCommon->LoadTexture(1, L"Resources/Gorushi.png");
	
	spriteCommon->LoadTexture(100, L"Resources/white1x1.png");
	postEffect = new PostEffect();
	postEffect->Initialize(dxCommon->GetDev());

	// スプライトの生成
	for (int i = 0; i < 1; i++)
	{
		int texNumber = rand() %2;
		Sprite *sprite = Sprite::Create(spriteCommon, 100, { 0,0 }, false, false);

		// スプライトの座標変更
		//sprite->SetPosition({ (float)(rand() % 1280),(float)(rand() % 720),0 });
		//sprite->SetRotation((float)(rand() % 360));
		//sprite->SetSize({ (float)(rand() % 400) ,(float)(rand() % 100) });

		// 頂点バッファに反映
		sprite->TransferVertexBuffer();

		sprites.push_back(sprite);
		sprite->SetPosition({ 500,300,0 });
	}

	//タイトル画像
	titleSpriteCommon->LoadTexture(0, L"Resources/title.png");
	titleSpriteCommon->LoadTexture(1, L"Resources/end.png");

	title = Sprite::Create(titleSpriteCommon, 0, { 0,0 }, false, false);
	title->SetSize({ (float)1400 ,(float)1400 });
	title->SetPosition({ 000,000,0 });
	// 頂点バッファに反映
	title->TransferVertexBuffer();


	int counter = 0; // アニメーションの経過時間カウンター
	//FBXモデル
	fbxobj->SetScale({ 0.1f,0.1f,0.1f });
	fbxobj->SetPosition({ 0,1,0 });

}

void MasterGame::Update()
{
	//基底クラスの更新
	Framework::Update();

	ImGui::Begin("aaa");
	ImGui::SetWindowSize(ImVec2(400, 500), ImGuiCond_::ImGuiCond_FirstUseEver);
	ImGui::End();

	if (Scene == 0)
	{
		if (input->PushKey(DIK_SPACE)) {
			Scene = 1;
		}
	}
	else if (Scene == 1)
	{

		// DirectX毎フレーム処理　ここから
		//3dオブジェクト更新
		object3d->Update();
		object3d_2->Update();
		object3d_3->Update();
		Player->Update();
		for (auto &sprite : sprites) {
			sprite->Update();
		}

		y -= 0.005;
		y += jump;

		// 座標操作
		if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
		{
			if (input->PushKey(DIK_UP)) {
				x -= 0.005;
			}

			if (input->PushKey(DIK_DOWN)) {
				y -= 0.005;

			}

			if (input->PushKey(DIK_RIGHT)) {
				x += 0.005;

			}

			if (input->PushKey(DIK_LEFT)) {
				x -= 0.005;

			}
		}
		if (input->PushKey(DIK_SPACE) && jumping == false)
		{
			jumping = true;
		}
		if (jumping == true) {
			jump += 0.003;
			jumping = false;
		}
		if (jump > 0) {
			jump -= 0.001;
		}
		if (y <= -0.25) {
			y = -0.25;
		}
		Player->SetPosition({ x,y,z });
	}
	else {
		
	}

	// DirectX毎フレーム処理　ここまで

}

void MasterGame::Draw()
{

	postEffect->PreDrawScene(dxCommon->GetCmdList(),dxCommon->GetDev());

	dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

	//fbxオブジェクト描画
	fbxobj->Draw(dxCommon->GetCmdList());

	//スプライト共通コマンド

	spriteCommon->PreDraw();
	//スプライト描画
	for (auto &sprite : sprites) {
		sprite->Draw();
	}

	//デバックテキスト
	debugText->DrawAll();

	// 描画コマンドここまで
	postEffect->PostDrawScene(dxCommon->GetCmdList());
	
	dxCommon->PreDraw();
	
	titleSpriteCommon->PreDraw();
	//タイトル
	if (Scene == 0) {
		title->Draw();
	}


	//3dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCmdList());
	//3dオブジェクトの描画
	object3d->Draw();
	object3d_2->Draw();
	object3d_3->Draw();
	Player->Draw();
	//3dオブジェクト描画後処理
	Object3d::PostDraw();

	postEffect->Draw(dxCommon->GetCmdList(),dxCommon->GetDev());

	imguiManager->Draw();

	dxCommon->PostDraw();
	
}

void MasterGame::Finalize()
{
	//スプライト個別開放
	for (auto &sprite : sprites) {
		delete sprite;
	}
	sprites.clear();

	delete title;
	delete postEffect;

	//3Dオブジェクト解放
	delete object3d;
	delete object3d_2;
	delete object3d_3;
	delete Player;
	//3Dモデルを解放
	delete model;
	delete modelPlayer;

	delete fbxmodel;
	delete fbxobj;

	//基底クラスの終了処理
	Framework::Finalize();
}
