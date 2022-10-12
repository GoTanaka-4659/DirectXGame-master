#pragma once

#include "FBX_Model.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>

#include "Camera.h"

class Fbx_Obj3d
{
private://�G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	//�f�o�C�X
	static ID3D12Device *device;
	//�J����
	static Camera *camera;
private:
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffTransform;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static	ComPtr<ID3D12PipelineState> pipelinestate;

	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };
	// ���[�J�����W
	XMFLOAT3 position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	//���f��
	FBXModel *model = nullptr;
	//�{�[���̍ő�l
	static const int MAX_BONES = 32;
	//�萔�o�b�t�@(�X�L��)
	ComPtr<ID3D12Resource> constBuffSkin;
	//1�t���[���̎���
	FbxTime frameTime;
	//�A�j���[�V�����J�n����
	FbxTime startTime;
	//�A�j���[�V�����I������
	FbxTime endTime;
	//���ݎ���(�A�j���[�V����)
	FbxTime currentTime;
	//�A�j���[�V�����Đ���
	bool isPlay = false;

public://�T�u�N���X
	//�萔�o�b�t�@�p�f�[�^�\���́i���W�Ԋҗ��p�j
	// �萔�o�b�t�@�p�f�[�^�\����B0
	struct ConstBufferDataB0
	{
		XMMATRIX viewproj;    // �r���[�v���W�F�N�V�����s��
		XMMATRIX world; // ���[���h�s��
		XMFLOAT3 cameraPos;//�J�������W
	};
	// �萔�o�b�t�@�p�f�[�^�\���́i�X�L�j���O�j
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};

public: // �ÓI�����o�֐�
	//setter
	static void SetDevice(ID3D12Device *device) { Fbx_Obj3d::device = device; }
	static void SetCamera(Camera *camera) { Fbx_Obj3d::camera = camera; }
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }
	void SetPosition(XMFLOAT3 position) { this->position = position; }
public://�����o�֐�
	//������
	void Initilize();
	//�X�V
	void Update();
	//�`��
	void Draw(ID3D12GraphicsCommandList *cmdList);
	//���f���Z�b�g
	void SetModel(FBXModel *model) { this->model = model; }
	//�O���t�B�b�N�X�p�C�v���C���̐���
	static void CreateGraphicsPipeline();
	//�A�j���[�V�����J�n
	void PlayAnimetion();
};

