#pragma once

#include "Graphics/Shader.h"
#include "Character.h"

// �G�l�~�[
class Enemy : public Character
{
public:
	Enemy() {}
	~Enemy() override {}

	// �X�V����
	virtual void Update(float elapsedTime) = 0;

	// �`�揈��
	//virtual void Render(ID3D11DeviceContext* dc, ModelShader* shader) = 0;
	virtual void Render(const RenderContext& rc, ModelShader* shader) = 0;


	virtual DirectX::XMFLOAT3 GetMoveVec()const;


	// �f�o�b�O�v���~�e�B�u�`��
	virtual void DrawDebugPrimitive();

	// �f�o�b�O�pGUI�`��
	virtual void DrawDebugGUI();

	// �j��
	void Destroy();
};
