#pragma once

#include "Graphics/Model.h"
#include "Enemy.h"

// �X���C��
class EnemySlime : public Enemy
{
public:
	EnemySlime();
	~EnemySlime() override;

	// �X�V����
	void Update(float elapsedTime) override;

	// �`�揈��
	void Render(const RenderContext& rc, ModelShader* shader) override;
	// �ǐՈړ�
	void TrackingMove(float elapsedTime);

protected:
	// ���S�������ɌĂ΂��
	void OnDead() override;
private:
	// �A�j���[�V����
	enum Animation
	{
		Anim_IdleNormal,
		Anim_IdleBattle,
		Anim_Attack01,
		Anim_Attack02,
		Anim_WalkFWD,
		Anim_WalkBWD,
		Anim_WalkLeft,
		Anim_WalkRight,
		Anim_RunFWD,
		Anim_SenseSomethingST,
		Anim_SenseSomethingRPT,
		Anim_Taunt,
		Anim_Victory,
		Anim_GetHit,
		Anim_Dizzy,
		Anim_Die,

	};


private:
	Model* model = nullptr;
	float	moveSpeed = 1.0f;
	float	turnSpeed = DirectX::XMConvertToRadians(720);

};
