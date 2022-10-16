#include "Framework.h"

void Framework::Initilize()
{

	//WinApp�̏�����
	winApp = new WinApp();
	winApp->Initilize();

	//DirectX�̏�����
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//���͂̏�����
	input = new Input();
	input->Initilize(winApp);

	//�J����
	camera = new Camera(winApp->Window_width, winApp->Window_height);
	//�X�v���C�g
	spriteCommon = new SpriteCommon();
	spriteCommon->Initilize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->Window_width, winApp->Window_height);

	// �f�o�b�O�e�L�X�g
	debugText = new DebugText();
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
	const int debugTextTexNumber = 2;
	// �f�o�b�O�e�L�X�g�p�̃e�N�X�`���ǂݍ���
	spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// �f�o�b�O�e�L�X�g������
	debugText->Initialize(spriteCommon, debugTextTexNumber);


	titleSpriteCommon = new SpriteCommon();
	titleSpriteCommon->Initilize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->Window_width, winApp->Window_height);


	//�I�[�f�B�I�̏�����
	audio = new Audio();
	audio->Initilize();
	// �����ǂݍ���
	audio->LoadWave("Resources/BGM_SE/Alarm01.wav");
	// �����Đ�
	//audio->PlayWave("Resources/Alarm01.wav");


	//FBX
	FbxLoader::GetInstance()->Initilize(dxCommon->GetDev());

	//�f�o�C�X�Z�b�g
	Fbx_Obj3d::SetDevice(dxCommon->GetDev());
	//�O���t�B�b�N�X�p�C�v���C������
	Fbx_Obj3d::CreateGraphicsPipeline();

	//���f�������w�肵�ăt�@�C����ǂݍ���
	//FbxLoader::GetInstance()->LoadModelFromFile("cube");
	fbxmodel = FbxLoader::GetInstance()->LoadModelFromFile("cube");

	//3d�I�u�W�F�N�g�����ƃ��f���̃Z�b�g
	fbxobj = new Fbx_Obj3d;
	fbxobj->Initilize();
	fbxobj->SetModel(fbxmodel);

	const std::string objname = "plane";
	//OBJ���烂�f���f�[�^��ǂݍ���
	model = Model::LoadFromOBJ(dxCommon->GetDev(), objname);
	// 3D�I�u�W�F�N�g�̐�
	const int OBJECT_NUM = 4;
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::Window_width, WinApp::Window_height);
	//3D�I�u�W�F�N�g����
	object3d = Object3d::Create();
	object3d_2 = Object3d::Create();
	object3d_3 = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f����R�Â�
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
	//OBJ���烂�f���f�[�^��ǂݍ���
	modelPlayer = Model::LoadFromOBJ(dxCommon->GetDev(), objPlayername);
	//3D�I�u�W�F�N�g����
	Player = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f����R�Â�
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

	//�f�o�b�O�e�L�X�g���
	debugText->Finalize();
	delete debugText;
	//�X�v���C�g�N���X���
	delete spriteCommon;
	delete titleSpriteCommon;
	//Imgui�N���X���
	delete imguiManager;
	//�I�[�f�B�I�N���X�J��
	audio->Finalize();
	delete audio;
	//DirectX���
	delete dxCommon;
	//WindowsAPI�̏I������
	winApp->Finalize();
	//WindowsAPI�̉��
	delete winApp;
	//���͉��
	delete input;

}

void Framework::Update()
{

	//ImGui
	imguiManager->CreateImGuiFrame();
	//Windows�̃��b�Z�[�W����
	if (winApp->ProcessMessage()) {
		//�Q�[���𔲂���
		endFlag = true;
		return;
	}
	//���͍X�V
	input->Update();

	//�J����
	/*camera->SetEye({ 0, 60, 0 });
	camera->SetTarget(object3d->GetPosition());*/
	camera->Update();
	//�J�����Z�b�g
	Player->SetCamera(camera);
	//fbxobj->SetCamera(camera);
	//3d�I�u�W�F�N�g�X�V
	object3d->Update();
	object3d_2->Update();
	object3d_3->Update();
	Player->Update();

	//Fbx
	fbxobj->Update();

	//Esc����������I��
	if (input->PushKey(DIK_ESCAPE)) {
		endFlag = true;
	}
}

void Framework::Run()
{
	Initilize();

	while (true)  // �Q�[�����[�v
	{
		Update();
		if (endFlag == true) {
			break;
		}
		Draw();
	}
	//�Q�[���̏I��
	Finalize();
}
