#include "ProjectileStraite.h"

// �R���X�g���N�^
ProjectileStraite::ProjectileStraite(ProjectileManager* manager)
	: Projectile(manager)
{
	//model = new Model("Data/Model/SpikeBall/SpikeBall.mdl");
	model = new Model("Data/Model/Sword/Cat.mdl");

	// �\���T�C�Y�𒲐�
	//scale.x = scale.y = scale.z = 0.5f;
	scale.x = scale.y = scale.z = 0.1f;
}

// �f�X�g���N�^
ProjectileStraite::~ProjectileStraite()
{
	delete model;
}

// �X�V����
void ProjectileStraite::Update(float elapsedTime)
{
	// ��������
	lifeTimer -= elapsedTime;
	if (lifeTimer <= 0.0f)
	{
		// �������폜
		Destroy();
	}

	// �ړ�
	float speed = this->speed * elapsedTime;
	position.x += direction.x * speed;
	position.y += direction.y * speed;
	position.z += direction.z * speed;

	// �I�u�W�F�N�g�s����X�V
	UpdateTransform();

	// ���f���s��X�V
	model->UpdateTransform(transform);
}

// �`�揈��
void ProjectileStraite::Render(const RenderContext& rc, ModelShader* shader)
{
	shader->Draw(rc, model);
}

// ����
void ProjectileStraite::Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position)
{
	this->direction = direction;
	this->position = position;
}
