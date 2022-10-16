#include "MasterGame.h"

void MasterGame::Initilize()
{
	//���N���X�̏�����
	Framework::Initilize();

	// �X�v���C�g���ʃe�N�X�`���ǂݍ���
	spriteCommon->LoadTexture(0, L"Resources/Gorushi.png");
	spriteCommon->LoadTexture(1, L"Resources/Gorushi.png");
	
	spriteCommon->LoadTexture(100, L"Resources/white1x1.png");
	postEffect = new PostEffect();
	postEffect->Initialize(dxCommon->GetDev());

	// �X�v���C�g�̐���
	for (int i = 0; i < 1; i++)
	{
		int texNumber = rand() %2;
		Sprite *sprite = Sprite::Create(spriteCommon, 100, { 0,0 }, false, false);

		// �X�v���C�g�̍��W�ύX
		//sprite->SetPosition({ (float)(rand() % 1280),(float)(rand() % 720),0 });
		//sprite->SetRotation((float)(rand() % 360));
		//sprite->SetSize({ (float)(rand() % 400) ,(float)(rand() % 100) });

		// ���_�o�b�t�@�ɔ��f
		sprite->TransferVertexBuffer();

		sprites.push_back(sprite);
		sprite->SetPosition({ 500,300,0 });
	}

	//�^�C�g���摜
	titleSpriteCommon->LoadTexture(0, L"Resources/title.png");
	titleSpriteCommon->LoadTexture(1, L"Resources/end.png");

	title = Sprite::Create(titleSpriteCommon, 0, { 0,0 }, false, false);
	title->SetSize({ (float)1400 ,(float)1400 });
	title->SetPosition({ 000,000,0 });
	// ���_�o�b�t�@�ɔ��f
	title->TransferVertexBuffer();


	int counter = 0; // �A�j���[�V�����̌o�ߎ��ԃJ�E���^�[
	//FBX���f��
	fbxobj->SetScale({ 0.1f,0.1f,0.1f });
	fbxobj->SetPosition({ 0,1,0 });

}

void MasterGame::Update()
{
	//���N���X�̍X�V
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

		// DirectX���t���[�������@��������
		//3d�I�u�W�F�N�g�X�V
		object3d->Update();
		object3d_2->Update();
		object3d_3->Update();
		Player->Update();
		for (auto &sprite : sprites) {
			sprite->Update();
		}

		y -= 0.005;
		y += jump;

		// ���W����
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

	// DirectX���t���[�������@�����܂�

}

void MasterGame::Draw()
{

	postEffect->PreDrawScene(dxCommon->GetCmdList(),dxCommon->GetDev());

	dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//dxCommon->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

	//fbx�I�u�W�F�N�g�`��
	fbxobj->Draw(dxCommon->GetCmdList());

	//�X�v���C�g���ʃR�}���h

	spriteCommon->PreDraw();
	//�X�v���C�g�`��
	for (auto &sprite : sprites) {
		sprite->Draw();
	}

	//�f�o�b�N�e�L�X�g
	debugText->DrawAll();

	// �`��R�}���h�����܂�
	postEffect->PostDrawScene(dxCommon->GetCmdList());
	
	dxCommon->PreDraw();
	
	titleSpriteCommon->PreDraw();
	//�^�C�g��
	if (Scene == 0) {
		title->Draw();
	}


	//3d�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCmdList());
	//3d�I�u�W�F�N�g�̕`��
	object3d->Draw();
	object3d_2->Draw();
	object3d_3->Draw();
	Player->Draw();
	//3d�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	postEffect->Draw(dxCommon->GetCmdList(),dxCommon->GetDev());

	imguiManager->Draw();

	dxCommon->PostDraw();
	
}

void MasterGame::Finalize()
{
	//�X�v���C�g�ʊJ��
	for (auto &sprite : sprites) {
		delete sprite;
	}
	sprites.clear();

	delete title;
	delete postEffect;

	//3D�I�u�W�F�N�g���
	delete object3d;
	delete object3d_2;
	delete object3d_3;
	delete Player;
	//3D���f�������
	delete model;
	delete modelPlayer;

	delete fbxmodel;
	delete fbxobj;

	//���N���X�̏I������
	Framework::Finalize();
}
