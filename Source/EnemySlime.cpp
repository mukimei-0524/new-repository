#include "EnemySlime.h"

// �R���X�g���N�^
EnemySlime::EnemySlime()
{
	model = new Model("Data/Model/Slime/Slime.mdl");

	// ���f�����傫���̂ŃX�P�[�����O
	scale.x = scale.y = scale.z = 0.01f;

	// ���A�����ݒ�
	radius = 0.5f;
	height = 1.0f;
	model->PlayAnimation(Animation::Anim_IdleBattle, true);
}

// �f�X�g���N�^
EnemySlime::~EnemySlime()
{
	delete model;
}

void EnemySlime::TrackingMove(float elapsedTime)
{
	// �i�s�x�N�g���擾
	DirectX::XMFLOAT3 moveVec = GetMoveVec();

	// �ړ�����
	Move(moveVec.x, moveVec.z, moveSpeed);

	// ���񏈗�
	Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);


}


// �X�V����
void EnemySlime::Update(float elapsedTime)
{
	TrackingMove(elapsedTime);


	// ���͏����X�V
	UpdateVelocity(elapsedTime);

	if (model->IsPlayAnimation() != Animation::Anim_WalkFWD)
	{
		model->PlayAnimation(Animation::Anim_WalkFWD, true);
	}

	// ���G���ԍX�V
	UpdateInvincibleTimer(elapsedTime);

	// �I�u�W�F�N�g�s����X�V
	UpdateTransform();

	model->UpdateAnimation(elapsedTime);
	// ���f���s��X�V
	model->UpdateTransform(transform);
}

// �`�揈��
void EnemySlime::Render(const RenderContext& rc, ModelShader* shader)
{
	shader->Draw(rc, model);
}

// ���S�������ɌĂ΂��
void EnemySlime::OnDead()
{
	// ���g��j��
	Destroy();
}
