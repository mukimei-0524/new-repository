#pragma once

#include "Graphics/Sprite.h"
#include "Graphics/Texture.h"

#include "Scene.h"


// �^�C�g���V�[��
class SceneTitle : public Scene
{
public:
	SceneTitle() {}
	~SceneTitle() override {}

	// ������
	void Initialize() override;

	// �I����
	void Finalize() override;

	// �X�V����
	void Update(float elapsedTime) override;

	// �`�揈��
	void Render() override;

private:
	//Sprite* sprite = nullptr;
	std::unique_ptr<Sprite> sprite;

	//Texture* texture = nullptr;
	std::unique_ptr<Texture> texture;
	// UV�X�N���[���f�[�^
	UVScrollData			uvScrollData;

	// �}�X�N�摜
	std::unique_ptr<Texture>	maskTexture;
	float					dissolveThreshold;
	float					edgeThreshold; 	// ����臒l
	DirectX::XMFLOAT4			edgeColor;		// ���̐F

};
