#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Collision.h"

// �X�e�[�W
class Stage
{
public:
	Stage();
	Stage(const char* filename);
	virtual ~Stage();

	// �X�V����
	virtual void Update(float elapsedTime);

	// �`�揈��
	void Render(const RenderContext& rc, ModelShader* shader);

	// ���C�L���X�g 
	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit);

	// �C���X�^���X�擾 
	static Stage& Instance();

private:
protected:
	Model* model = nullptr;
};

class Earth :public Stage
{
public :
	Earth();
	~Earth();
	// �X�V����
	void Update(float elapsedTime) override;


};
