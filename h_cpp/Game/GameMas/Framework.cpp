#include "Framework.h"

void Framework::Initilize()
{

	//WinAppの初期化
	winApp = new WinApp();
	winApp->Initilize();

	//DirectXの初期化
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//入力の初期化
	input = new Input();
	input->Initilize(winApp);

	//カメラ
	camera = new Camera(winApp->Window_width, winApp->Window_height);
	//スプライト
	spriteCommon = new SpriteCommon();
	spriteCommon->Initilize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->Window_width, winApp->Window_height);

	// デバッグテキスト
	debugText = new DebugText();
	// デバッグテキスト用のテクスチャ番号を指定
	const int debugTextTexNumber = 2;
	// デバッグテキスト用のテクスチャ読み込み
	spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText->Initialize(spriteCommon, debugTextTexNumber);


	titleSpriteCommon = new SpriteCommon();
	titleSpriteCommon->Initilize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->Window_width, winApp->Window_height);


	//オーディオの初期化
	audio = new Audio();
	audio->Initilize();
	// 音声読み込み
	audio->LoadWave("Resources/BGM_SE/Alarm01.wav");
	// 音声再生
	//audio->PlayWave("Resources/Alarm01.wav");


	//FBX
	FbxLoader::GetInstance()->Initilize(dxCommon->GetDev());

	//デバイスセット
	Fbx_Obj3d::SetDevice(dxCommon->GetDev());
	//グラフィックスパイプライン生成
	Fbx_Obj3d::CreateGraphicsPipeline();

	//モデル名を指定してファイルを読み込み
	//FbxLoader::GetInstance()->LoadModelFromFile("cube");
	fbxmodel = FbxLoader::GetInstance()->LoadModelFromFile("cube");

	//3dオブジェクト生成とモデルのセット
	fbxobj = new Fbx_Obj3d;
	fbxobj->Initilize();
	fbxobj->SetModel(fbxmodel);

	const std::string objname = "plane";
	//OBJからモデルデータを読み込む
	model = Model::LoadFromOBJ(dxCommon->GetDev(), objname);
	// 3Dオブジェクトの数
	const int OBJECT_NUM = 4;
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::Window_width, WinApp::Window_height);
	//3Dオブジェクト生成
	object3d = Object3d::Create();
	object3d_2 = Object3d::Create();
	object3d_3 = Object3d::Create();
	//オブジェクトにモデルを紐づけ
	object3d->SetModel(model);
	object3d->SetPosition({ -1,-0.5,1 });
	object3d->SetScale({ 0.001,0.001,0.001 });
	//object3d_2->SetPosition({ 0,0,0 });
	object3d_2->SetModel(model);
	object3d_2->SetPosition({ -0.1,-0.5,1 });
	object3d_2->SetScale({ 0.001,0.001,0.001 });
	object3d_3->SetModel(model);
	object3d_3->SetPosition({ 0.8,-0.5,1 });
	object3d_3->SetScale({ 0.001,0.001,0.001 });

	const std::string objPlayername = "player";
	//OBJからモデルデータを読み込む
	modelPlayer = Model::LoadFromOBJ(dxCommon->GetDev(), objPlayername);
	//3Dオブジェクト生成
	Player = Object3d::Create();
	//オブジェクトにモデルを紐づけ
	Player->SetModel(modelPlayer);
	Player->SetPosition({ 0,0.5,1 });
	Player->SetScale({ 0.01,0.01,0.01 });

	//Imgui
	imguiManager = new ImguiManager(winApp->GetHwnd(), dxCommon->GetCmdList(), dxCommon->GetDev());

}

void Framework::Finalize()
{
	//Fbx
	FbxLoader::GetInstance()->Finalize();

	//デバッグテキスト解放
	debugText->Finalize();
	delete debugText;
	//スプライトクラス解放
	delete spriteCommon;
	delete titleSpriteCommon;
	//Imguiクラス解放
	delete imguiManager;
	//オーディオクラス開放
	audio->Finalize();
	delete audio;
	//DirectX解放
	delete dxCommon;
	//WindowsAPIの終了処理
	winApp->Finalize();
	//WindowsAPIの解放
	delete winApp;
	//入力解放
	delete input;

}

void Framework::Update()
{

	//ImGui
	imguiManager->CreateImGuiFrame();
	//Windowsのメッセージ処理
	if (winApp->ProcessMessage()) {
		//ゲームを抜ける
		endFlag = true;
		return;
	}
	//入力更新
	input->Update();

	//カメラ
	/*camera->SetEye({ 0, 60, 0 });
	camera->SetTarget(object3d->GetPosition());*/
	camera->Update();
	//カメラセット
	Player->SetCamera(camera);
	//fbxobj->SetCamera(camera);
	//3dオブジェクト更新
	object3d->Update();
	object3d_2->Update();
	object3d_3->Update();
	Player->Update();

	//Fbx
	fbxobj->Update();

	//Escを押したら終了
	if (input->PushKey(DIK_ESCAPE)) {
		endFlag = true;
	}
}

void Framework::Run()
{
	Initilize();

	while (true)  // ゲームループ
	{
		Update();
		if (endFlag == true) {
			break;
		}
		Draw();
	}
	//ゲームの終了
	Finalize();
}
