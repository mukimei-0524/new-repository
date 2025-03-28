#pragma once

#include "Stage.h"
#include "Player.h"
#include "CameraController.h"
#include "Scene.h"
//#include "Graphics/RenderTarget.h"
#include "Graphics/DepthStencil.h"
#include "Light.h"
#include "Graphics/SkyBox.h"
//#include "PostprocessingRenderer.h"

// �Q�[���V�[��
class SceneGame : public Scene
{
public:
	SceneGame() {}
	~SceneGame() override {}

	// ������
	void Initialize() override;

	// �I����
	void Finalize() override;

	// �X�V����
	void Update(float elapsedTime) override;

	// �`�揈��
	void Render() override;

private:

	// 3D��Ԃ̕`��
	//void Render3DScene();

	// �V���h�E�}�b�v�̕`��
	void RenderShadowmap();


private:
	Stage*				stage = nullptr;

	//std::unique_ptr<StageManager> stageManager;
	std::unique_ptr<Stage> earth;
	std::unique_ptr<Earth> earth2;

	Player*				player = nullptr;
	CameraController*	cameraController = nullptr;
	//// ���s�����f�[�^
	//std::unique_ptr<Light>	directional_light;
	//DirectX::XMFLOAT4		ambientLightColor;

	float   outlinewidth = 0.0f;
	DirectX::XMFLOAT4  outlineColor{ 0,0,0,1 };
	SkyBox* skybox = nullptr;//�����lnull

	//	�V���h�E�}�b�v�p���
	Light* mainDirectionalLight = nullptr;					//	�V���h�E�}�b�v�𐶐����镽�s����
	std::unique_ptr<DepthStencil> shadowmapDepthStencil;	//	�V���h�E�}�b�v�p�[�x�X�e���V���o�b�t�@
	float	shadowDrawRect = 500.0f;	//	�V���h�E�}�b�v�ɕ`�悷��͈�
	DirectX::XMFLOAT4X4	lightViewProjection;				//	���C�g�r���[�v���W�F�N�V�����s��
	DirectX::XMFLOAT3	shadowColor = { 0.2f, 0.2f, 0.2f };	//	�e�̐F
	float				shadowBias = 0.001f;				//	�[�x��r�p�̃I�t�Z�b�g�l
	int                 PCFKernelSize = 1;                  // �\�t�g�V���h�[�̍s��T�C�Y


	//	�|�X�g�v���Z�X
	//std::unique_ptr<PostprocessingRenderer>	postprocessingRenderer;


};
